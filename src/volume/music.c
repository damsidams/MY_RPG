/*
** EPITECH PROJECT, 2023
** B-MUL-200-PAR-2-1-myrpg-nicolas.nunney
** File description:
** sound.c
*/

#include "rpg.h"
#include "struct.h"
#include "associative.h"

int set_music_volume_down(parameters_t *param, entity_t *entity, bool state)
{
    float actual_volume;

    if (!param->music)
        return ERROR;
    actual_volume = sfMusic_getVolume(param->music);
    if (actual_volume - 10 > MIN_VOLUME)
        sfMusic_setVolume(param->music, actual_volume - 10.0);
    else
        sfMusic_setVolume(param->music, 0.0);
    (void)entity;
    (void)state;
    return SUCCESS;
}

int set_music_volume_up(parameters_t *param, entity_t *entity, bool state)
{
    float actual_volume;

    if (!param->music)
        return ERROR;
    actual_volume = sfMusic_getVolume(param->music);
    if (actual_volume + 10 < MAX_VOLUME)
        sfMusic_setVolume(param->music, actual_volume + 10.0);
    else
        sfMusic_setVolume(param->music, 100.0);
    (void)entity;
    (void)state;
    return SUCCESS;
}

int reset_music_volume(parameters_t *param, entity_t *entity, bool state)
{
    if (!param->music)
        return ERROR;
    sfMusic_setVolume(param->music, DEFAULT_VOLUME);
    (void)entity;
    (void)state;
    return SUCCESS;
}
