
/*
  Program RecordPlayback: A MIDI tool
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


#ifndef MIDI
#define MIDI

#include <iostream>
#include <cstring>

class MidiEvent
{
  public:
    MidiEvent(){}
    MidiEvent(long inFrame, unsigned char* inData)
    {
      frame = inFrame;
      memcpy( data, inData, sizeof(unsigned char) *3 );
    }
    long frame;
    unsigned char data[3];
};

#endif 
