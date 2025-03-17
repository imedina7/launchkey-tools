#ifndef MIDI_H
#define MIDI_H

#include <alsa/asoundlib.h>

#define MAX_RETRIES 100
#define DELAY_SECONDS 2

#define CHK(stmt, msg) if((stmt) < 0) {puts("ERROR: "#msg); exit(1);}

snd_seq_t* seq_connect(const char* client_name);

void send_midi_message(snd_rawmidi_t *midi_out, unsigned char *message, int length);
void rcv_midi_message(snd_rawmidi_t *midi_in, unsigned char *message, int length);
snd_rawmidi_t* device_connect(const char* device, snd_rawmidi_stream_t stream_direction);
void device_disconnect(snd_rawmidi_t* port);
#endif
