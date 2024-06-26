/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** Function to revert a linked_list
*/

#include "struct.h"

void reverse_list(e_list_t **head)
{
    e_list_t *prev = NULL;
    e_list_t *current = *head;
    e_list_t *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

unsigned int get_list_size(e_list_t *list)
{
    unsigned int size = 0;

    while (list) {
        size++;
        list = list->next;
    }
    return size;
}
