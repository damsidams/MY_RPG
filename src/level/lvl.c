/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** lvl
*/

#include "rpg.h"

void set_lvl_pos(system_t *sys)
{
    sfVector2f pos = {0};
    e_list_t *xp = get_entities(sys, XP | VISIBLE);
    e_list_t *player = get_entities(sys, PLAYER | VISIBLE);
    sfVector2f player_center_pos = {0};

    if (xp == NULL || player == NULL)
        return;
    player_center_pos = get_center(player->entity->sprite);
    pos.x = player_center_pos.x - sfSprite_getGlobalBounds
        (xp->entity->sprite).width * XP_WIDTH;
    pos.y = player_center_pos.y - DEFAULT_VIEW_SIZE_Y * XP_HEIGHT / 2
    - sfSprite_getGlobalBounds(xp->entity->sprite).height / 2;
    sfSprite_setPosition(xp->entity->sprite, pos);
    clean_list(xp);
    clean_list(player);
    printf("Lvl pos: {%f, %f}\n", pos.x, pos.y);
    printf("Player pos: {%f, %f}\n", player_center_pos.x, player_center_pos.y);
}

void move_lvl_rect(system_t *sys)
{
    e_list_t *xp = get_entities(sys, XP);
    sfIntRect rect = {0};

    if (xp == NULL || xp->entity->sprite != NULL)
        return;
    rect = sfSprite_getTextureRect(xp->entity->sprite);
    rect.height += rect.height;
    if (rect.height >= XP_MAP_RECT_HEIGHT)
        rect.height = 0;
    sfSprite_setTextureRect(xp->entity->sprite, rect);
    clean_list(xp);
}