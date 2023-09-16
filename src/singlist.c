#include "cwdatastruct/singlist.h"
#include <stdlib.h>

struct snode *slist_add(struct snode **head, void *data) {
    if (head == NULL || data == NULL)
        return NULL;

    struct snode *new;
    new = malloc(sizeof(struct snode));
    if (new == NULL)
        return NULL;

    new->data = data;
    new->next = NULL;
    if (*head != NULL) {
        new->next = *head;
    }
    *head = new;
    return new;
}

struct snode *slist_insert(struct snode **head, void *data, unsigned int index) {
    if (head == NULL || data == NULL)
        return NULL;
    if (index == 0) return slist_add(head, data);

    struct snode *current, *previous, *new;
    current = *head;
    new = NULL;

    while (current != NULL && index != 0) {
        previous = current;
        current = current->next;
        index--;
    }

    /* If index is out of range, we just add to end of list */
    new = malloc(sizeof(struct snode));
    if (new == NULL) 
        return NULL;
    new->data = data;
    previous->next = new;
    new->next = current;

    return new;
}

int default_cmp(void *x, void * y) {
    return !(x == y);
}

struct snode *slist_search(struct snode *head, void *data, compare_func *cmp) {
    if (head == NULL || data == NULL)
        return NULL;

    if (cmp == NULL)
        cmp = &default_cmp;

    struct snode *current;
    current = head;

    while (current != NULL) {
        if ((cmp(data, current->data)) == 0)
            return current;
        current = current->next;
    }
    return NULL;

}

void *slist_remove(struct snode **head, void *data, compare_func *cmp) {
    if (head == NULL || data == NULL)
        return NULL;
    if (cmp == NULL)
        cmp = &default_cmp;
    
    struct snode *current, *previous;
    current = *head;
    while (current != NULL) {
        if ((cmp(data, current->data)) != 0) {
            previous = current;
            current = current->next;
            continue;
        }

        if (current == *head) {
            *head = current->next;
        } else {
            previous->next = current->next;
        }
        void *ret = current->data;
        free(current);
        return ret;
    }
    return NULL;
}
