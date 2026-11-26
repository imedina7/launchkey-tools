#ifndef MENU_H
#define MENU_H
typedef int (*op_t)(char);

#define MAX_MENU_ITEMS 16
typedef struct menu_item menu_item_t;

struct menu_item {
    char label[32];
    char midi_note;
    char color;
    // executed function - parameter is velocity
    // must return 0 for success, -1 for error
    // can be NULL as it can point to other menu
    op_t operator;
    menu_item_t *children;
    unsigned int children_count;
};

void init_menu_item(menu_item_t* menu_item, const char *label, char color, char midi_note);

void destroy_menu_item(menu_item_t* menu_item);

void set_menu_item_op(menu_item_t* menu_item, op_t operator);

void push_child_menu_item(menu_item_t* menu_item, menu_item_t *child);

#endif
