#ifndef INCONTROL_H
#define INCONTROL_H
#include <stdbool.h>

#define BIT(n) (0x01 << n)

enum incontrol_status_section {
  INCONTROL_STATUS_SECTION_MUTE_BTN = BIT(0),
  INCONTROL_STATUS_SECTION_FADERS = BIT(1),
  INCONTROL_STATUS_SECTION_KNOBS = BIT(2),
  INCONTROL_STATUS_SECTION_PADS = BIT(3)
};
void enable_extended_mode(snd_rawmidi_t *midi_out);
void init_pads (snd_rawmidi_t *midi_out);
unsigned char get_launchkey_pad_color(int red, int green);
bool query_extended_mode(snd_rawmidi_t *midi_out, snd_rawmidi_t *midi_in, const unsigned char section);
#endif
