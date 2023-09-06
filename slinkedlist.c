#include "cwdatastruct/slinkedlist.h"
#include <stdlib.h>
#include <string.h>

struct slist *slist_init(void) {
    struct slist *list;
    list = malloc(sizeof(struct slist));
    if (list == NULL) return NULL; /* Failed to allocate memory */

    list->head = NULL;
    list->tail = NULL;
    list->_size = 0;

    return list;
}

struct slist *slist_clone(struct slist *list, char is_deep_clone, size_t size_of_data) {
    struct slist *clone;
    clone = malloc(sizeof(struct slist));
    if (clone == NULL) return NULL; /* Failed to allocate memory */

    if (is_deep_clone == 0) {
        clone->head = list->head;
        clone->tail = list->tail;
        clone->_size = list->_size;
        return clone;
    }

    struct snode *node = list->head;
    while (node != NULL) {
        void *data_clone = malloc(size_of_data);
        if (data_clone == NULL) return NULL; /* Failed to allocate memory */

        memcpy(data_clone, node->data, size_of_data);
        if (slist_add(clone, data_clone) != 0) return NULL; /* Failed to add to list */
        node = node->next;
    }
    return clone;
}

int slist_add(struct slist *list, void *data) {
    if (list == NULL) return SLIST_NULL;
    if (data == NULL) return SLIST_NULL_DATA;
    
    struct snode *node = malloc(sizeof(struct snode));
    if (node == NULL) return SLIST_ADD_FAILED_MALLOC_NODE;
    node->data = data; 
    node->next = NULL;
    if (list->head == NULL) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->_size++;
    
    return 0;
}

struct snode *slist_search(struct slist *list, void *data) {
    if (list == NULL ||
            data == NULL)
        return NULL;
    /* Might as well so we don't have to traverse */
    if (list->tail->data == data) return list->tail;

    struct snode *curr;
    curr = list->head;
    while (curr != NULL) {
         if (curr->data == data) return curr;
         curr = curr->next;
    }
    return NULL;
}

/* This function is not defined in the header file because I think it's a bit
 * too specific and messy. I don't see many uses for it outside the use of managing
 * this list.
 */
void slist_get_previous_and_node(struct slist *list, void *data, struct snode **previous, struct snode **node) {
    if (list == NULL ||
            data == NULL)
        return;
    struct snode *prev, *curr;
   
    if (list->head == NULL)
        return;
    prev = curr = list->head;
    while (curr != NULL) {
        if (curr->data == data) {
            if (previous != NULL) *previous = prev;
            if (node != NULL) *node = curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    return;
}

void *slist_remove(struct slist *list, void *data) {
    if (list == NULL ||
            data == NULL)
        return NULL;

    if (list->head == NULL)
        return NULL;

    struct snode *free_me = NULL; /* Node to be freed at the end */
    if (data == list->head->data) {
        free_me = list->head;
        list->head = list->head->next;
        if (list->head == NULL) list->tail = NULL;
    } else { /* General case, somewhere in the middle or tail */
        struct snode *prev;
        slist_get_previous_and_node(list, data, &prev, &free_me);
        if (free_me == NULL) return NULL; /* Not in list */
        prev->next = free_me->next;
        if (free_me == list->tail) list->tail = prev; /* If we're removing the tail */
    }
    /* This should never be NULL, but just in case */
    if (free_me != NULL) free(free_me); /* lol */
    list->_size--;
    return data;
}

void slist_free(struct slist *list, void (*free_data)(void *data), char options) {
    if (list == NULL) return;
    if (options & SLIST_DO_NOT_FREE_NODES) {
        free(list);
        return;
    }
    if (options & SLIST_FREE_DATA &&
            free_data != NULL) {
        struct snode *curr;
        curr = list->head;
        while (curr != NULL) {
            free_data(curr->data);
            curr = curr->next;
        }
    }
    struct snode *tmp, *curr;
    curr = list->head;
    while (curr != NULL) {
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    free(list);
}
