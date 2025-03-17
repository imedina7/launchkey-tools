#include "midi.h"
#include "incontrol.h"

#include <alsa/asoundlib.h>
#include <stdio.h> 
#include <stdlib.h>

#define LAUNCHKEY_NUM_PADS 16


void enable_extended_mode(snd_rawmidi_t *midi_out) {
  unsigned char extended_mode[] = {0x90, 0x00, 0x00, 0x9f, 0x0c, 0x7f}; 
  send_midi_message(midi_out, extended_mode, sizeof(extended_mode)); 
}

void init_pads(snd_rawmidi_t *midi_out) {
  unsigned char pad_colors[LAUNCHKEY_NUM_PADS] = {};
  unsigned char pad_numbers[LAUNCHKEY_NUM_PADS] = {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77};
  for(int i = 0; i < LAUNCHKEY_NUM_PADS; i++) {
    pad_colors[i] = get_launchkey_pad_color(0,2);
  }
  for(int i = 0; i < LAUNCHKEY_NUM_PADS; i++) {
    unsigned char turn_on_message[] = {0xBF, pad_numbers[i], pad_colors[i]};
    send_midi_message(midi_out, turn_on_message, sizeof(turn_on_message));
  }
}

unsigned char get_launchkey_pad_color(int red, int green) {
  return (unsigned char)(red + (green << 4));
}

bool query_extended_mode(snd_rawmidi_t *midi_out, snd_rawmidi_t *midi_in, const unsigned char section) {
  unsigned char query_message[] = {0x9F, 0x0B, 0x00};
  unsigned char response[] = {};
  send_midi_message(midi_out, query_message, sizeof(query_message));
  rcv_midi_message(midi_in, response, sizeof(char) * 3);

  return response[2] & section;
}
