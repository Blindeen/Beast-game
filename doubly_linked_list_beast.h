#ifndef GAME_BEAST_DOUBLY_LINKED_LIST_BEAST_H
#define GAME_BEAST_DOUBLY_LINKED_LIST_BEAST_H

#include "point.h"

struct doubly_linked_list_beast_t
{
    struct node_beast_t *head;
    struct node_beast_t *tail;
};

struct node_beast_t
{
    struct point_t beast_position;

    struct node_beast_t *next;
    struct node_beast_t *prev;
};

struct doubly_linked_list_beast_t* dll_beast_create();
int dll_beast_push_back(struct doubly_linked_list_beast_t* dll, struct point_t *coords);
void dll_beast_clear(struct doubly_linked_list_beast_t* dll);
int dll_beast_is_empty(const struct doubly_linked_list_beast_t* dll);

#endif
