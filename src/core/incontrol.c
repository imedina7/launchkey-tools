#include "midi.h"
#include "config.h"
#include "menu.h"
#include "layout_preset.h"
#include "incontrol.h"

#include <alsa/asoundlib.h>
#include <stdio.h>
#include <stdlib.h>

#define LAUNCHKEY_NUM_PADS 16


void enable_extended_mode(snd_rawmidi_t *midi_out) {
  unsigned char extended_mode[] = {0x90, 0x00, 0x00, 0x9f, 0x0c, 0x7f};
  send_midi_message(midi_out, extended_mode);
}

void init_pads(snd_rawmidi_t *midi_out, snd_rawmidi_t *midi_in) {
  preset_t default_preset;

  set_preset_name(&default_preset, "default");

  load_preset(&default_preset);
  print_preset(&default_preset);


  bool extended_enabled = query_extended_mode(midi_out, midi_in);
  if(!extended_enabled) {
    enable_extended_mode(midi_out);
    printf("Extended mode is disabled, enabling...\n");
  }

  printf("Extended mode enabled\n");

  menu_item_t *current_item = default_preset.menus;
  for(int i = 0; i < default_preset.menu_count; i++) {
    printf("Sending color for \"%s\" menu\n", current_item->label);
    printf("Color = %x\nMidi note = %d\n", current_item->color, current_item->midi_note);
    set_pad_color(midi_out, current_item->midi_note, current_item->color);
    current_item++;
  }

  destroy_preset(&default_preset);
}

unsigned char get_launchkey_pad_color(int red, int green) {
  return (unsigned char)(red + (green << 4));
}

bool query_extended_mode(snd_rawmidi_t *midi_out, snd_rawmidi_t *midi_in) {
  unsigned char query_message[] = {0x9F, 0x0B, 0x00};
  unsigned char response[] = {};
  send_midi_message(midi_out, query_message);
  rcv_midi_message(midi_in, response);

  return response[2] | 0x10;
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
