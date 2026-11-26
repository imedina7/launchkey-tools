#include "midi.h"
#include "incontrol.h"

#include <alsa/asoundlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void enable_extended_mode(snd_rawmidi_t *midi_out) {
  unsigned char extended_mode[] = {0x90, 0x00, 0x00, 0x9f, 0x0c, 0x7f};
  send_midi_message(midi_out, extended_mode);
}

char mix_rg_color_code(char red, char green) {
  // we make sure values are within range
  assert(red >= 0 && red <= 3 && green >= 0 && green <= 3);

  char result = (green << 4) + red;
  return result;
}

int set_pad_color(snd_rawmidi_t *midi_out, enum InControlPad pad, char colormix) {
  unsigned char message[] = { (unsigned char)INCONTROL_MESSAGE_LED, (unsigned char)pad, colormix };
  send_midi_message(midi_out, message);
  return 0;
}

int set_pad_flash(snd_rawmidi_t *midi_out, enum InControlPad pad, char colormix) {
  unsigned char message[] = { (unsigned char)INCONTROL_MESSAGE_LED_FLASH, (unsigned char)pad, colormix };
  send_midi_message(midi_out, message);
  return 0;
}

bool query_extended_mode(snd_rawmidi_t *midi_out, snd_rawmidi_t *midi_in) {
  unsigned char message[] = {(unsigned char)INCONTROL_MESSAGE_STATUS, 0x0b, 0x00};
  send_midi_message(midi_out, message);
  unsigned char response;
  rcv_midi_message(midi_in, &response);

  return response | 0x10;
}
