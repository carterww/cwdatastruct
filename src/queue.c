#include <stdlib.h>

#include "cwdatastruct/queue.h"
#include "cwdatastruct/singlist.h"

struct queue *queue_init() {
    struct queue *queue = malloc(sizeof(struct queue));
    if (queue == NULL) {
        return NULL;
    }
    queue->head = queue->tail = NULL;
    return queue;
}

struct snode *queue_enqueue(struct queue *queue, void *data) {
    if (queue == NULL || data == NULL)
        return NULL;
    struct snode *new = malloc(sizeof(struct snode));
    if (new == NULL)
        return NULL;
    new->data = data;
    if (queue->head == NULL) {
        queue->head = queue->tail = new;
    } else {
        queue->tail->next = new;
        queue->tail = new;
    }

    return new;
}

void *queue_dequeue(struct queue *queue) {
    if (queue == NULL)
        return NULL;
    void * res = slist_remove(&(queue->head), queue->head->data, NULL);
    if (queue->head == NULL)
        queue->tail = NULL;

    return res;
}

void *queue_peek(struct queue *queue) {
    if (queue == NULL)
        return NULL;
    if (queue->head == NULL)
        return NULL;
    return queue->head->data;
}

void *queue_remove(struct queue *queue, void *data, compare_func cmp) {
    return slist_remove(&(queue->head), data, cmp);
}
