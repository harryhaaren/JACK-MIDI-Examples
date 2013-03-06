
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


#include <iostream>
#include <unistd.h>
#include "jack.hpp"

int main(int argc,char *argv[])
{
  
  std::cout << "\
  \t\t\t Midi Record Play\n\
  \tThis program creates JACK MIDI input & output ports and will\n\
  \tprint in the console all input it recieves, and print\n\
  \tevents as they're played back" << std::endl;
  
  // Create Jack object, the constructor registers the MIDI port, etc
  Jack jack;
  
  jack.activate();
  
  for(;;)
  {
    sleep(1);
  }
  
  return 0;
}
