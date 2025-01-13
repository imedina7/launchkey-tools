#include "midi.h"
#include <stdio.h>
#include <stdlib.h>

void send_midi_message(snd_rawmidi_t *midi_out, unsigned char *message, int length) 
{
  if (snd_rawmidi_write(midi_out, message, length) < 0) { 
    fprintf(stderr, "Error writing MIDI message\n"); 
    exit(1); 
  } 
  snd_rawmidi_drain(midi_out); 
}

void rcv_midi_message(snd_rawmidi_t *midi_in, unsigned char *message, int length) 
{
  if (snd_rawmidi_read(midi_in, message, length) < 0) { 
    fprintf(stderr, "Error reading MIDI message\n"); 
    exit(1); 
  } 
  snd_rawmidi_drain(midi_in); 
}

snd_rawmidi_t* device_connect(const char* device, snd_rawmidi_stream_t stream_direction) {
  snd_rawmidi_t *midi_port = NULL;
  int result;
  int retries = 1;

  // Open MIDI device 
  do
  {
    if (stream_direction == SND_RAWMIDI_STREAM_OUTPUT) {
      result = snd_rawmidi_open(NULL, &midi_port, device, 0);
    }

    if(stream_direction == SND_RAWMIDI_STREAM_INPUT) {
      result = snd_rawmidi_open(&midi_port, NULL, device, 0);
    }
    printf("Device not found, retrying (%d of %d)...\n", retries++, MAX_RETRIES);
    sleep(DELAY_SECONDS);
  } while (result < 0 && retries < MAX_RETRIES);

  if(result < 0) {
    fprintf(stderr, "Failed to connect to device.\n");
    exit(1);
  }
  const char* device_id = snd_rawmidi_name(midi_port);

  printf("Connected successfully to device \"%s\"\n", device_id);
  
  return midi_port;
}

