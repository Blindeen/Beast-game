#ifndef GAME_BEAST_DOUBLY_LINKED_LIST_H
#define GAME_BEAST_DOUBLY_LINKED_LIST_H

#include "point.h"

struct doubly_linked_list_t
{
    struct node_t *head;
    struct node_t *tail;
};

struct node_t
{
    unsigned int coins_value;
    struct point_t position;

    struct node_t *next;
    struct node_t *prev;
};

struct doubly_linked_list_t* dll_create();

int dll_push_back(struct doubly_linked_list_t* dll, unsigned int value, struct point_t *coords);
int dll_push_front(struct doubly_linked_list_t* dll, unsigned int value, struct point_t *coords);
unsigned int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code);
unsigned int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code);

int dll_size(const struct doubly_linked_list_t* dll);
int dll_is_empty(const struct doubly_linked_list_t* dll);

unsigned int dll_remove(struct doubly_linked_list_t* dll, struct point_t *coords, int *err_code);

void dll_clear(struct doubly_linked_list_t* dll);

#endif
