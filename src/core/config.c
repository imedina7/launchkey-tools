#include "config.h"
#include "iniparser.h"
#include <string.h>

void load_config(app_config_t* config, int argc, char *argv[], char *default_conf) {
    dictionary *ini;
    char *ini_name;

    if (argc < 2) {
        ini_name = default_conf;
    } else {
        ini_name = argv[1];
    }

    ini = iniparser_load(ini_name);
    const char *device = iniparser_getstring(ini, "general:device", NULL);
    const char *bank_path = iniparser_getstring(ini, "general:bank_path", NULL);
    const int retries = iniparser_getint(ini, "general:midi_poll_retries", MIDI_DEFAULT_RETRIES);
    strncpy(config->midi_device, device, strlen(device));
    strncpy(config->preset_bank_directory, bank_path, strlen(bank_path));
    config->midi_retries = retries;
    iniparser_freedict(ini);
}
