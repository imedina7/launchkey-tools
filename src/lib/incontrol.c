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
  send_midi_message(midi_out, extended_mode, sizeof(extended_mode)); 
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

bool query_extended_mode(snd_rawmidi_t *midi_out, snd_rawmidi_t *midi_in, const unsigned char section) {
  unsigned char query_message[] = {0x9F, 0x0B, 0x00};
  unsigned char response[] = {};
  send_midi_message(midi_out, query_message, sizeof(query_message));
  rcv_midi_message(midi_in, response, sizeof(char) * 3);

  return response[2] & section;
}
