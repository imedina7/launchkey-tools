#include "layout_preset.h"
#include "iniparser.h"
#include <string.h>
#include <assert.h>
#include "incontrol.h"
#include "config.h"

void set_preset_name(preset_t *preset, const char *name){
    strncpy(preset->name, name, strlen(name));
}

void load_preset(preset_t *preset){
    assert(preset->name != NULL && "Preset should have name, use set_preset_name() before calling load_preset()");
    char path[1024];
    memset(path, 0, 1024);
    strncpy(path, global_config->preset_bank_directory, strlen(global_config->preset_bank_directory));
    strcat(path, "/");
    strcat(path, preset->name);
    strcat(path, ".preset");

    preset->dict = iniparser_load(path);
    int menu_count = iniparser_getnsec(preset->dict);

    int saved_count = 0;

    for (int i = 0; i < menu_count || i >= MAX_MENU_ITEMS; i++) {
        char label[32];
        memset(label, 0, 32);

        strncpy(label, iniparser_getsecname(preset->dict, i), 32);

        char color_path_r[32], color_path_g[32], midi_note_path[32];
        memset(color_path_r, 0, 32);
        memset(color_path_g, 0, 32);
        memset(midi_note_path, 0, 32);

        strncpy(color_path_r, label, strlen(label));
        strncpy(color_path_g, label, strlen(label));
        strncpy(midi_note_path, label, strlen(label));
        strcat(color_path_r, ":color_r");
        strcat(color_path_g, ":color_g");
        strcat(midi_note_path, ":midi_note");

        const int colorR = iniparser_getint(preset->dict, color_path_r, 0);
        const int colorG = iniparser_getint(preset->dict, color_path_g, 0);
        const int midi_note = iniparser_getint(preset->dict, midi_note_path, 0);
        init_menu_item(&preset->menus[i], label, mix_rg_color_code(colorR, colorG), midi_note);
        saved_count = i;
    }
    preset->menu_count = saved_count + 1;
}

void print_preset(const preset_t *preset) {
    printf("Preset Label: %s\n", preset->name);
    printf("Preset menu count: %d\n", preset->menu_count);

    printf("Menus:\n");

    for (int i = 0; i < preset->menu_count; i++) {
        menu_item_t menu = preset->menus[i];
        printf("Menu label: %s\n", menu.label);
        printf("Menu midi note: %d\n", menu.midi_note);
        printf("Menu color: %d\n", menu.color);
    }
}

void store_preset(preset_t *preset){
    assert(preset->name != NULL && "Preset should have name, use set_preset_name() before calling store_preset()");

}

void destroy_preset(preset_t* preset){
    for(int i = 0; i < preset->menu_count; i++){
        destroy_menu_item(&preset->menus[i]);
    }
    iniparser_freedict(preset->dict);
}
