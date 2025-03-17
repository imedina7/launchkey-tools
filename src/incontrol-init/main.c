#include "midi.h"
#include "incontrol.h"
#include <stdio.h>
#include <stdlib.h>

void print_usage(char* program_name) {
  printf("Usage: %s <device>\n", program_name);
}

int main(int argc, char** argv) { 
  if(argc < 2) {
	print_usage(argv[0]);
    return -1;
  }
  const char *device = argv[1];

  snd_rawmidi_t* midi_out = device_connect(device, SND_RAWMIDI_STREAM_OUTPUT);
  
  enable_extended_mode(midi_out);
  init_pads(midi_out);
  snd_rawmidi_close(midi_out); 
  return 0;
}
