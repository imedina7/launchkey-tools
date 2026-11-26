#include "menu.h"
#include <string.h>
#include <stdlib.h>

void set_menu_item_op(menu_item_t* menu_item, op_t operator){
    menu_item->operator = operator;
}

void push_child_menu_item(menu_item_t* menu_item, menu_item_t *child) {
    menu_item->children[menu_item->children_count++] = *child;
}

void init_menu_item(menu_item_t* menu_item, const char *label, char color, char midi_note){
    memset(menu_item->label, 0, 32);
    strncpy(menu_item->label, label, strlen(label));
    menu_item->children = malloc(sizeof(menu_item_t *) * MAX_MENU_ITEMS);
    menu_item->children_count = 0;
    menu_item->color = color;
    menu_item->midi_note = midi_note;
}

void destroy_menu_item(menu_item_t* menu_item) {
    free(menu_item->children);
}
