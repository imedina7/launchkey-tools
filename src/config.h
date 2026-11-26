#ifndef CONFIG_H
#define CONFIG_H

typedef struct app_config app_config_t;

extern app_config_t *global_config;

struct app_config {
    char midi_device[32];
    char preset_bank_directory[1024];
    int midi_retries;
};

#define MIDI_DEFAULT_RETRIES 3

void load_config(app_config_t* config, int argc, char *argv[], char* default_conf);

#endif
