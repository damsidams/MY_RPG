/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** get_item
*/

#include <stdio.h>
#include "rpg.h"

double get_sprites_dist(sfSprite *a, sfSprite *b)
{
    sfVector2f pa = sfSprite_getPosition(a);
    sfVector2f pb = sfSprite_getPosition(b);

    return get_distance_bewteen_pos(&pa, &pb);
}

void drop_selected_item(system_t *sys)
{
    e_list_t *list = get_entities(sys, SELECTED);
    sfVector2f dz = sfSprite_getPosition(get_player(sys));

    if (list == NULL) {
        return;
    }
    unset_entity(sys, list->entity, SELECTED);
    set_entity(list->entity, sys, ON_MAP);
    refresh_inventory_pos(sys);
    sfSprite_setPosition(list->entity->sprite, dz);
    clean_list(list);
}

static bool remove_inv_last_element(system_t *sys)
{
    e_list_t *inv = get_entities(sys, INVENTORY | ITEM | VISIBLE);
    sfVector2f dz = sfSprite_getPosition(get_player(sys));
    e_list_t *temp = inv;

    if (inv == NULL)
        return false;
    while (temp && temp->next)
        temp = temp->next;
    unset_entity(sys, temp->entity, INVENTORY);
    set_entity(temp->entity, sys, ON_MAP);
    sfSprite_setPosition(temp->entity->sprite, dz);
    clean_list(inv);
    return true;
}

static void grab_item(system_t *sys, entity_t *e)
{
    e_list_t *inventory = NULL;

    unset_entity(sys, e, ON_MAP);
    set_entity(e, sys, INVENTORY);
    inventory = get_entities(sys, INVENTORY | ITEM | VISIBLE);
    if (get_list_size(inventory) > INVENTORY_CAPACITY) {
        remove_inv_last_element(sys);
    }
    refresh_inventory_pos(sys);
    clean_list(inventory);
}

void get_item(parameters_t *param)
{
    e_list_t *item_list = get_entities(param->sys, ON_MAP);
    e_list_t *head = item_list;
    sfSprite *player = get_player(param->sys);

    if (player == NULL || item_list == NULL)
        return;
    while (item_list) {
        if (get_sprites_dist(item_list->entity->sprite, player) < GRAB_RANGE) {
            grab_item(param->sys, item_list->entity);
        }
        item_list = item_list->next;
    }
    clean_list(head);
}
