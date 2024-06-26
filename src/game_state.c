/*
** EPITECH PROJECT, 2023
** B-MUL-200-PAR-2-1-myrpg-nicolas.nunney
** File description:
** game_state.c
*/

#include "rpg.h"
#include "struct.h"

int set_to_play(parameters_t *param, entity_t *entity, bool clicked)
{
    if (clicked) {
        param->game_state = PLAY;
    }
    (void)entity;
    return SUCCESS;
}

int set_to_pause(parameters_t *param, entity_t *entity, bool clicked)
{
    if (clicked) {
        param->game_state = PAUSE;
    }
    (void)entity;
    return SUCCESS;
}

int set_to_quit(parameters_t *param, entity_t *entity, bool clicked)
{
    if (clicked) {
        param->game_state = QUIT;
    }
    (void)entity;
    return SUCCESS;
}
