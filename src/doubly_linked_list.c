#include "doubly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

struct doubly_linked_list_t* dll_create()
{
    struct doubly_linked_list_t *list = (struct doubly_linked_list_t *) calloc(1, sizeof(struct doubly_linked_list_t));
    if(list == NULL)
    {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}

int dll_push_back(struct doubly_linked_list_t* dll, unsigned int value, struct point_t *coords)
{
    if(dll == NULL)
    {
        return 1;
    }

    struct node_t *el = (struct node_t *) calloc(1, sizeof(struct node_t));
    if(el == NULL)
    {
        return 2;
    }
    el->coins_value = value;
    el->position = *coords;

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

int dll_push_front(struct doubly_linked_list_t* dll, unsigned int value, struct point_t *coords)
{
    if(dll == NULL)
    {
        return 1;
    }

    struct node_t *el = (struct node_t *) calloc(1, sizeof(struct node_t));
    if(el == NULL)
    {
        return 2;
    }
    el->coins_value = value;
    el->position = *coords;

    if(dll->head == NULL && dll->tail == NULL)
    {
        el->next = NULL;
        el->prev = NULL;

        dll->head = el;
        dll->tail = el;
    }
    else
    {
        el->prev = NULL;
        el->next = dll->head;

        dll->head->prev = el;
        dll->head = el;
    }

    return 0;
}

unsigned int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code)
{
    if(dll == NULL)
    {
        if(err_code != NULL)
        {
            *err_code = 1;
        }
        return 1;
    }

    if(dll->head == NULL && dll->tail == NULL)
    {
        if(err_code != NULL)
        {
            *err_code = 1;
        }
        return 0;
    }

    struct node_t *ptr;
    ptr = dll->head;

    dll->head = dll->head->next;
    if(dll->head == NULL)
    {
        dll->tail = NULL;
    }
    else
    {
        dll->head->prev = NULL;
    }


    unsigned int value = ptr->coins_value;

    free(ptr);

    if(err_code != NULL)
    {
        *err_code = 0;
    }

    return value;
}

unsigned int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code)
{
    if(dll == NULL)
    {
        if(err_code != NULL)
        {
            *err_code = 1;
        }
        return 1;
    }

    if(dll->head == NULL && dll->tail == NULL)
    {
        if(err_code != NULL)
        {
            *err_code = 1;
        }
        return 0;
    }

    if(dll->head == dll->tail)
    {
        return dll_pop_front(dll, err_code);
    }

    struct node_t *ptr;
    ptr = dll->tail;

    dll->tail = dll->tail->prev;
    dll->tail->next = NULL;

    unsigned int value = ptr->coins_value;

    free(ptr);

    if(err_code != NULL)
    {
        *err_code = 0;
    }

    return value;
}


int dll_size(const struct doubly_linked_list_t* dll)
{
    if(dll == NULL)
    {
        return -1;
    }

    if(dll->head == NULL && dll->tail == NULL)
    {
        return 0;
    }

    int i = 1;
    struct node_t *ptr = dll->head;
    while(ptr != dll->tail)
    {
        ptr=ptr->next;
        ++i;
    }

    return i;
}

int dll_is_empty(const struct doubly_linked_list_t* dll)
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

unsigned int dll_remove(struct doubly_linked_list_t* dll, struct point_t *coords, int *err_code)
{
    if(dll == NULL)
    {
        if(err_code != NULL)
        {
            *err_code = 1;
        }
        return 1;
    }

    struct node_t *ptr = dll->head, *remove;
    int size = dll_size(dll);

    int index = 0;

    for(int i = 0; i < size; ++i)
    {
        if(ptr->position.x == coords->x && ptr->position.y == coords->y)
        {
            break;
        }
        ptr = ptr->next;
        index++;
    }

    if(index == 0)
    {
        return dll_pop_front(dll, NULL);
    }
    else if(index == size-1)
    {
        return dll_pop_back(dll, NULL);
    }


    remove = ptr;

    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;

    unsigned int value = remove->coins_value;

    free(remove);

    if(err_code != NULL)
    {
        *err_code = 0;
    }

    return value;
}

void dll_clear(struct doubly_linked_list_t* dll)
{
    if(dll != NULL && !dll_is_empty(dll))
    {
        struct node_t *ptr = dll->head, *rm;
        do {
            rm = ptr;
            ptr = ptr->next;
            free(rm);
        } while (ptr != NULL);
        dll->head = NULL;
        dll->tail = NULL;
    }
}