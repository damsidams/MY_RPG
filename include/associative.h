/*
** EPITECH PROJECT, 2023
** B-MUL-200-PAR-2-1-myrpg-nicolas.nunney
** File description:
** associative.h
*/

#ifndef ASSOCIATIVE_H
    #define ASSOCIATIVE_H
    #include "struct.h"
    #include "rpg.h"

typedef struct conf_function_s {
    char *func_name;
    int (*function)(parameters_t *, entity_t *, bool state);
} conf_function_t;

typedef struct conf_param_s {
    char *param;
    void (*exec)(entity_t *entity, char *value, sfIntRect *rect);
} conf_param_t;

typedef struct conf_compo_s {
    char *component;
    int associate;
} conf_compo_t;

static const conf_function_t func_list[] = {
    {"set_to_quit", &set_to_quit},
    {"set_to_play", &set_to_play},
    {"set_to_pause", &set_to_pause},
    {"hovered", &hovered},
    {NULL, NULL},
};

static const conf_compo_t compo_list[] = {
    {"PLAYER", PLAYER},
    {"NPC", NPC},
    {"VISIBLE", VISIBLE},
    {"MENU", MENU},
    {"MOB", MOB},
    {"CLICKABLE", CLICKABLE},
    {"SETTINGS", SETTINGS},
    {NULL, 0},
};

static const conf_param_t param_list[] = {
    {"TEXTURE", &set_texture},
    {"SPRITE", &create_sprite},
    {"RECT", &create_rectangle},
    {"SCALE", &set_scale},
    {"POS", &set_pos},
    {"CLICK", &set_click},
    {"HOVER", &set_hover},
    {NULL, NULL},
};

#endif
