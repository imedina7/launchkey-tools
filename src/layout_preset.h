#ifndef MENU_LAYOUT_PRESET_H
#define MENU_LAYOUT_PRESET_H
#include "menu.h"
#include "iniparser.h"
#include <stdio.h>

typedef struct preset preset_t;

struct preset {
    char name[32];
    menu_item_t menus[16];
    dictionary *dict;
    int menu_count;
};

void load_preset(preset_t *preset);
void set_preset_name(preset_t *preset, const char *name);
void store_preset(preset_t *preset);
void print_preset(const preset_t *preset);

void destroy_preset(preset_t* preset);

#endif
