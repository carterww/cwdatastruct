#include "cwdatastruct/slinkedlist.h"
#include <stdlib.h>
#include <string.h>

struct slist *slist_init(void) {
    struct slist *list;
    list = malloc(sizeof(struct slist));
    if (list == NULL) return NULL; /* Failed to allocate memory */

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

struct slist *slist_clone(struct slist *list, char is_deep_clone, size_t size_of_data) {
    struct slist *clone;
    clone = malloc(sizeof(struct slist));
    if (clone == NULL) return NULL; /* Failed to allocate memory */

    if (is_deep_clone == 0) {
        clone->head = list->head;
        clone->tail = list->tail;
        clone->size = list->size;
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
    if (list->size == 0) {
        list->head = list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
    
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

    struct snode *free_me = NULL;
    if (data == list->head->data) {
        free_me = list->head;
        list->head = list->head->next;
        free_me->next = NULL;
        if (list->head == NULL) list->tail = NULL;
    } else if (data == list->tail->data) {
        struct snode *before_tail;
        slist_get_previous_and_node(list, list->tail->data, &before_tail, NULL);
        if (before_tail == NULL) return NULL;
        free_me = list->tail;
        before_tail->next = NULL;
        list->tail = before_tail;
    } else {
        struct snode *prev;
        slist_get_previous_and_node(list, data, &prev, &free_me);
        if (!free_me) return NULL;
        prev->next = free_me->next;
        free_me->next = NULL;
    }
    free(free_me); /* lol */
    list->size--;
    return data;
}

void slist_free(struct slist *list, char options) {
    if (list == NULL) return;
    struct snode *curr = list->head;
    struct snode *tmp;
    if (options & SLIST_DO_NOT_FREE_NODES) {
        free(list);
        return;
    }
    while (curr != NULL) {
        tmp = curr;
        if (options & SLIST_FREE_DATA &&
                curr->data != NULL) 
            free(curr->data);
        curr = curr->next;
        free(tmp);
    }
    free(list);
}
