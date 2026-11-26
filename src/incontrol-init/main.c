#include "config.h"
#include "midi.h"
#include "incontrol.h"
#include "menu.h"
  #include <stdio.h>
#include <stdlib.h>

app_config_t *global_config;

void print_usage(char* program_name) {
  printf("Usage: %s <config>\n", program_name);
}

int main(int argc, char** argv) {
  if(argc < 2) {
	  print_usage(argv[0]);
    return -1;
  }
  global_config = malloc(sizeof(app_config_t));
  load_config(global_config, argc, argv, "launchkey.conf");

  char basic_device[64];
  strncpy(basic_device, global_config->midi_device, strlen(global_config->midi_device));

  char incontrol_device[64];
  strncpy(incontrol_device, global_config->midi_device, strlen(global_config->midi_device));

  strcat(basic_device, ",0");
  strcat(incontrol_device, ",1");
  
  snd_rawmidi_t* midi_out = device_connect(incontrol_device, SND_RAWMIDI_STREAM_OUTPUT);
  snd_rawmidi_t* midi_in = device_connect(incontrol_device, SND_RAWMIDI_STREAM_INPUT);
  
  enable_extended_mode(midi_out);
  init_pads(midi_out);
  snd_rawmidi_close(midi_out);
  snd_rawmidi_close(midi_in);
  return 0;
}
