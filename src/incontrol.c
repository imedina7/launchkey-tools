#include "midi.h"

#include <alsa/asoundlib.h>
#include <stdio.h> 
#include <stdlib.h>


void enable_extended_mode(snd_rawmidi_t *midi_out) {
  unsigned char extended_mode[] = {0x90, 0x00, 0x00, 0x9f, 0x0c, 0x7f}; 
  send_midi_message(midi_out, extended_mode, sizeof(extended_mode)); 
}
