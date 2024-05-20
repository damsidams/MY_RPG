/*
** EPITECH PROJECT, 2023
** B-MUL-200-PAR-2-1-myrpg-nicolas.nunney
** File description:
** main_page.c
*/

#include <stdio.h>
#include <stdbool.h>
#include "rpg.h"
#include "struct.h"

int start_menu(parameters_t *param, entity_t *entity, bool state)
{
    sfSound *backsound = sfSound_create();
    sfSoundBuffer *sound_buffer = sfSoundBuffer_createFromFile(MUSIC_PATH);

    (void)entity;
    (void)state;
    if (backsound == NULL || sound_buffer == NULL)
        return ERROR;
    sfSound_setBuffer(backsound, sound_buffer);
    sfSound_setVolume(backsound, 100);
    sfSound_play(backsound);
    reset_view(param->window, param->view);
    while (sfRenderWindow_isOpen(param->window) &&
        param->game_state == PAUSE) {
        display_entities(param, MENU);
        sfRenderWindow_display(param->window);
        mouse_events(param, CLICKABLE);
        sfRenderWindow_clear(param->window, sfBlack);
    }
    if (!sfRenderWindow_isOpen(param->window))
        return ERROR;
    return SUCCESS;
}