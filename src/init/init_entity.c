/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** Functions for entity
*/

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <SFML/Graphics.h>
#include "rpg.h"
#include "struct.h"

static entity_t *set_sprite(entity_t *e, char const *texture_path,
    sfIntRect *rect)
{
    sfTexture *texture = NULL;
    sfSprite *sprite = sfSprite_create();

    if (sprite == NULL) {
        dprintf(2, "Error: sfSprite_create failed\n");
        free(e);
        return NULL;
    }
    texture = sfTexture_createFromFile(texture_path, rect);
    if (texture == NULL) {
        dprintf(2, "Error: unable to load %s as a texture\n", texture_path);
        free(e);
        sfSprite_destroy(sprite);
    }
    sfSprite_setTexture(sprite, texture, sfFalse);
    e->sprite = sprite;
    return e;
}

entity_t *set_rectangle(entity_t *e, char const *texture_path,
    sfIntRect *rect)
{
    sfTexture *texture = NULL;
    sfRectangleShape *rectangle = sfRectangleShape_create();

    if (rectangle == NULL) {
        dprintf(2, "Error: sfRectangleShape_create failed\n");
        free(e);
        return NULL;
    }
    texture = sfTexture_createFromFile(texture_path, rect);
    if (texture == NULL) {
        dprintf(2, "Error: unable to load %s as a texture\n", texture_path);
        free(e);
        sfRectangleShape_destroy(rectangle);
    }
    sfRectangleShape_setTexture(rectangle, texture, sfFalse);
    e->rect = rectangle;
    return e;
}

static bool set_texture(entity_t *e, char const *texture_path, sfIntRect *rect)
{
    e->rect = NULL;
    if (texture_path != NULL) {
        e = set_sprite(e, texture_path, rect);
        if (e == NULL) {
            return false;
        }
    }
    return true;
}

void add_click_hover(entity_t *entity, int (*clicked)(parameters_t *,
    system_t *, entity_t *entity, bool clicked),
    int (*hovered)(parameters_t *, system_t *,
        entity_t *entity, bool hovered))
{
    if (!entity) {
        return;
    }
    if (hovered) {
        entity->hovered = hovered;
    }
    if (clicked) {
        entity->clicked = clicked;
    }
}

entity_t *create_entity(system_t *sys, char const *texture_path,
    sfIntRect *rect, int compo)
{
    entity_t *e = malloc(sizeof(entity_t));
    static unsigned int id = 0;

    if (e == NULL) {
        perror("create entity malloc failed");
        return NULL;
    }
    if (!set_texture(e, texture_path, rect)) {
        return NULL;
    }
    if (!push_to_list(&sys->e_list, e)) {
        free_entity(e);
        return NULL;
    }
    e->id = id;
    id++;
    set_entity(e, sys, compo);
    e->clicked = NULL;
    e->hovered = NULL;
    return e;
}
