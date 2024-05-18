/*
** EPITECH PROJECT, 2024
** MY_RPG
** File description:
** Functions related to player movements
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include "rpg.h"
#include "struct.h"

void swap_struct(sokospot_t **current, sokospot_t **target)
{
    sokospot_t *tmp = *current;

    if (((*target)->moved_in_frame || (*current)->moved_in_frame)
        && (*current)->type != PLAYER_CHAR) {
        return;
    }
    (*current)->moved_in_frame = true;
    (*target)->moved_in_frame = true;
    *current = *target;
    *target = tmp;
}

static void move_not_possible(void)
{
    printf("** bump sound **\n");
}

static bool spot_available(sokospot_t *spot)
{
    char type = '\0';

    if (spot == NULL) {
        return false;
    }
    type = spot->type;
    if (type == EMPTY || type == NPC_LIMIT) {
        return true;
    }
    return false;
}

void set_prev_pos(parameters_t *param, sfSprite *player,
    sokospot_t *player_spot)
{
    sfSprite_setPosition(player, player_spot->last_pos);
    sfView_setCenter(param->view, get_center(player));
}

static void move_in_array(parameters_t *param, sokospot_t ***map,
    sfSprite *player)
{
    sfVector2f pos = get_center(player);
    sokospot_t *player_spot = get_player_spot(map);
    sfVector2u w_size = sfRenderWindow_getSize(param->window);
    int x = (int)(MAP_WIDTH * pos.x / w_size.x);
    int y = (int)(MAP_HEIGHT * pos.y / w_size.y);

    if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) {
        dprintf(2, "Error: player pos can't be at this sokomap index\n");
        return;
    }
    if (map[y][x]->type == PLAYER_CHAR)
        return;
    if (spot_available(map[y][x]) || map[y][x]->type == PLAYER_CHAR) {
        if (map[y][x]->type != PLAYER_CHAR)
            swap_struct(&player_spot, &map[y][x]);
        return;
    }
    if (map[y][x]->type == OBSTACLE)
        move_not_possible();
    set_prev_pos(param, player, player_spot);
}

sfSprite *get_player(system_t *sys)
{
    e_list_t *p_list = get_entities(sys, PLAYER);
    sfSprite *s = NULL;

    if (p_list == NULL)
        return NULL;
    s = p_list->entity->sprite;
    clean_list(p_list);
    return s;
}

void move_player(parameters_t *param)
{
    sfVector2f move = {0};
    sfSprite *player = get_player(param->sys);

    if (param->map_array == NULL || player == NULL)
        return;
    move = get_p_move_event(player);
    if (move.x != 0.0 || move.y != 0.0) {
        get_player_spot(param->map_array)->last_pos =
            sfSprite_getPosition(player);
        set_player_new_pos(param, move);
        move_in_array(param, param->map_array, player);
        sfRenderWindow_setView(param->window, param->view);
        set_inventory_pos(param->sys);
    }
}
