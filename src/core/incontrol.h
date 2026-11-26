#ifndef INCONTROL_H
#define INCONTROL_H
#include <stdbool.h>
#include "midi.h"

#define BIT(n) (0x01 << n)

char mix_rg_color_code(char red, char green);

enum InControlPad {
    /* TOP HALF */
    PAD_C6_T1 = 96,   // Top 1st pad
    PAD_Db6_T2 = 97,  // Top 2nd pad
    PAD_D6_T3 = 98,   // Top 3rd pad
    PAD_Eb6_T4 = 99,  // Top 4th pad
    PAD_E6_T5 = 100,  // Top 5th pad
    PAD_F6_T6 = 101,  // Top 6th pad
    PAD_Gb6_T7 = 102, // Top 7th pad
    PAD_G6_T8 = 103,  // Top 8th pad

    /* BOTTOM HALF */
    PAD_E7_B1 = 112,  // Bottom 1st pad
    PAD_F7_B2 = 113,  // Bottom 2nd pad
    PAD_Gb7_B3 = 114, // Bottom 3rd pad
    PAD_G7_B4 = 115,  // Bottom 4th pad
    PAD_Ab7_B5 = 116, // Bottom 5th pad
    PAD_A7_B6 = 117,  // Bottom 6th pad
    PAD_Bb7_B7 = 118, // Bottom 7th pad
    PAD_B7_B8 = 119,  // Bottom 8th pad

    /* ROUND PADS*/
    PAD_Ab6_TR = 104, // Top round pad
    PAD_C8_BR = 120   // Bottom round pad
};

enum InControlMessage {
    INCONTROL_MESSAGE_LED = 0xBF,
    INCONTROL_MESSAGE_LED_FLASH = 0x91,
    INCONTROL_MESSAGE_STATUS = 0x9f,
};

enum incontrol_status_section {
  INCONTROL_STATUS_SECTION_MUTE_BTN = BIT(0),
  INCONTROL_STATUS_SECTION_FADERS = BIT(1),
  INCONTROL_STATUS_SECTION_KNOBS = BIT(2),
  INCONTROL_STATUS_SECTION_PADS = BIT(3)
};

void enable_extended_mode(snd_rawmidi_t *midi_out);
void init_pads (snd_rawmidi_t *midi_out, snd_rawmidi_t *midi_in);
unsigned char get_launchkey_pad_color(int red, int green);
bool query_extended_mode(snd_rawmidi_t *midi_out, snd_rawmidi_t *midi_in);
int set_pad_color(snd_rawmidi_t *midi_out, enum InControlPad pad, char colormix);
int set_pad_flash(snd_rawmidi_t *midi_out, enum InControlPad pad, char colormix);

#endif
