#include <stdlib.h>
#include "doubly_linked_list_beast.h"

struct doubly_linked_list_beast_t* dll_beast_create()
{
    struct doubly_linked_list_beast_t *list = (struct doubly_linked_list_beast_t *) calloc(1, sizeof(struct doubly_linked_list_beast_t));
    if(list == NULL)
    {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}

int dll_beast_push_back(struct doubly_linked_list_beast_t* dll, struct point_t *coords)
{
    if(dll == NULL)
    {
        return 1;
    }

    struct node_beast_t *el = (struct node_beast_t *) calloc(1, sizeof(struct node_beast_t));
    if(el == NULL)
    {
        return 2;
    }

    el->beast_position = *coords;

    if(dll->head == NULL && dll->tail == NULL)
    {
        el->next = NULL;
        el->prev = NULL;

        dll->head = el;
        dll->tail = el;
    }
    else
    {
        el->next = NULL;
        el->prev = dll->tail;

        dll->tail->next = el;
        dll->tail = el;
    }

    return 0;
}

void dll_beast_clear(struct doubly_linked_list_beast_t* dll)
{
    if(dll != NULL && !dll_beast_is_empty(dll))
    {
        struct node_beast_t *ptr = dll->head, *rm;
        do {
            rm = ptr;
            ptr = ptr->next;
            free(rm);
        } while (ptr != NULL);
        dll->head = NULL;
        dll->tail = NULL;
    }
}

int dll_beast_is_empty(const struct doubly_linked_list_beast_t* dll)
{
    if(dll == NULL)
    {
        return -1;
    }

    if(dll->head == NULL && dll->tail == NULL)
    {
        return 1;
    }

    return 0;
}