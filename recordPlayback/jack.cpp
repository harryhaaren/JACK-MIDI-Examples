
/*
  Program PrintJackMidi: A MIDI tool
  Author: Harry van Haaren
  E-mail: harryhaaren@gmail.com
  Copyright (C) 2010 Harry van Haaren
  
  PrintJackMidi is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  PrintJackMidi is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with PrintJackMidi.  If not, see <http://www.gnu.org/licenses/>. */


#include "jack.hpp"

using namespace std;

Jack::Jack()
{
  bpm = 120.0;
  
  record = true;
  
  previousFrame = 0;
  playbackIndex = 0;
  
  std::cout << "Jack()" << std::flush;
  
  if ((client = jack_client_open("PrintMidi", JackNullOption, NULL)) == 0)
  {
    std::cout << "jack server not running?" << std::endl;
  }
  
  inputPort  = jack_port_register (client, "midi_in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
  
  jack_set_process_callback (client, staticProcess, static_cast<void*>(this));
  
  std::cout << "\t\t\tDone!" << std::endl;
  
}

Jack::~Jack()
{
  std::cout << "~Jack()" << std::endl;
}

void Jack::activate()
{
  std::cout << "activate()" << std::flush;
  
  if (jack_activate(client) != 0)
  {
    std::cout<<  "cannot activate client" << std::endl;
    return;
  }
  std::cout << "\t\tDone!" << std::endl;
}

int Jack::staticProcess(jack_nframes_t nframes, void *arg)
{
  return static_cast<Jack*>(arg)->process(nframes);
}

int Jack::process(jack_nframes_t nframes)
{
  jack_midi_event_t in_event;
  jack_nframes_t event_index = 0;
  jack_position_t         position;
  jack_transport_state_t  transport;
  
  // get the port data
  void* port_buf = jack_port_get_buffer( inputPort, nframes);
  
  
  // get the transport state of the JACK server
  transport = jack_transport_query( client, &position );
  
  
  // input: get number of events, and process them.
  jack_nframes_t event_count = jack_midi_get_event_count(port_buf);
  if(event_count > 0)
  {
    for(int i=0; i<event_count; i++)
    {
      jack_midi_event_get(&in_event, port_buf, i);
      
      // Using "cout" in the JACK process() callback is NOT realtime, this is
      // used here for simplicity.
      std::cout << "Frame " << position.frame << "  Event: " << i << " SubFrame#: " << in_event.time << " \tMessage:\t"
                << (long)in_event.buffer[0] << "\t" << (long)in_event.buffer[1]
                << "\t" << (long)in_event.buffer[2] << std::endl;
      
      eventVector.push_back( MidiEvent( position.frame + (long)in_event.time, (unsigned char*)&in_event.buffer ) );
      
      cout << "event.back() frame = " << eventVector.back().frame << endl;
    }
  }
  
  for( int i = 0; i < nframes; i++ )
  {
    if ( playbackIndex < eventVector.size() &&
         position.frame > eventVector.at(playbackIndex).frame )
    {
      cout << "Playback event! Frame = " << eventVector.at(playbackIndex).frame << "  Data  "
           << (long)in_event.buffer[0] << "\t" << (long)in_event.buffer[1]
           << "\t" << (long)in_event.buffer[2] << endl;
      
      playbackIndex++;
    }
  }
  
  // reset to start of eventVector when we "rewind" jack's transport
  if ( position.frame == 0 )
  {
    playbackIndex = 0;
  }
  
  
  return 0;
}
