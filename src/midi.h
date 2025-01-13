#ifndef MIDI_H
#define MIDI_H

#include <alsa/asoundlib.h>

#define MAX_RETRIES 100
#define DELAY_SECONDS 2

void send_midi_message(snd_rawmidi_t *midi_out, unsigned char *message, int length);
void rcv_midi_message(snd_rawmidi_t *midi_in, unsigned char *message, int length);
snd_rawmidi_t* device_connect(const char* device, snd_rawmidi_stream_t stream_direction);

#endif
