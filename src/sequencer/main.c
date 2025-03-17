#include "midi.h"
#include "incontrol.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_INSTRUMENTS 8

typedef struct {
  snd_rawmidi_t* extended_in;
  snd_rawmidi_t* extended_out;
  snd_rawmidi_t* basic_in;
  snd_rawmidi_t* basic_out;
} IncontrolPort;

typedef struct {
  char *label;
  char note;
  char length;
} instrument_track;

typedef struct {
 float instrument_velocity[MAX_INSTRUMENTS];
 float step_velocity[MAX_INSTRUMENTS][];
 unsigned char current_step = 0;
 instrument_track tracks[MAX_INSTRUMENTS];
} sequencer_state;

void midi_open(const char* device_basic, const char* device_extended, IncontrolPort* port) {
  port->basic_in = device_connect(device_basic, SND_RAWMIDI_STREAM_INPUT);
  port->basic_out = device_connect(device_basic, SND_RAWMIDI_STREAM_OUTPUT);
  port->extended_in = device_connect(device_extended, SND_RAWMIDI_STREAM_INPUT);
  port->extended_out = device_connect(device_extended, SND_RAWMIDI_STREAM_OUTPUT);
}

void midi_close(IncontrolPort* port) {
  device_disconnect(port->extended_in);
  device_disconnect(port->extended_out);
  device_disconnect(port->basic_in);
  device_disconnect(port->basic_out);
}

int main (int argc, char** argv) {
  IncontrolPort* port = malloc(sizeof(IncontrolPort));

  printf("Opening ports...\n");
  midi_open(argv[1], argv[2], port);
  printf("Querying extended mode...\n");
  do{
    bool pads_ext = query_extended_mode(port->extended_out, port->extended_in, INCONTROL_STATUS_SECTION_PADS);
    bool faders_ext = query_extended_mode(port->extended_out, port->extended_in, INCONTROL_STATUS_SECTION_FADERS);
    bool knobs_ext = query_extended_mode(port->extended_out, port->extended_in, INCONTROL_STATUS_SECTION_KNOBS);
    printf("Extended mode:\n");

    printf("    Pads: ");
    if(pads_ext) {
      printf("Enabled\n");
    } else {
      printf("Disabled\n");
    }

    printf("    Knobs: ");
    if(knobs_ext) {   
      printf("Enabled\n");                         
    } else {
      printf("Disabled\n");
    }

    printf("    Faders: ");
    if(faders_ext) {
      printf("Enabled\n");
    } else {
      printf("Disabled\n");
    }

    printf("\n");

  } while (true);

  midi_close(port);

  free(port);
  return 0;
}

