/* Queue implementation using linked list
 * NOT THREAD SAFE.
 */
#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "singlist.h"

/* A queue is just a singly linked list alias in this case.
 * The functions are just wrappers around the singly linked list functions
 * that make it easier to manage a queue. Some functions may require a
 * special implementation that does not simply wrap the singly linked list
 * function(s).
 */
struct queue {
    struct snode *head;
    struct snode *tail;
};


/* Initializes a queue.
 * @return: NULL if the queue could not be allocated, otherwise a pointer to the queue.
 */
struct queue *queue_init();

/* Adds a node to the end of the queue.
 * @param queue: The queue to add to. Must not be NULL.
 * @param data: A pointer to the data. Must not be NULL.
 * @return: 0 on success, an error code otherwise.
 */
struct snode *queue_enqueue(struct queue *queue, void *data);

/* Removes a node from the front of the queue.
 * @param queue: The queue to remove from. Must not be NULL.
 * @return: The data pointer of the removed data, or NULL if it is empty.
 */
void *queue_dequeue(struct queue *queue);

/* Peeks at the front of the queue.
 * @param queue: The queue to peek at. Must not be NULL.
 * @return: The data pointer of the data in the front of the queue, or NULL if it is empty.
 */
void *queue_peek(struct queue *queue);

/* Remove all nodes in a queue based on a compare function.
 * @param queue: The queue to get the size of. Must not be NULL.
 * @param data: The data to compare against. Must not be NULL.
 * @param cmp: The compare function to use. Returns 0 if the data matches, non-zero otherwise.
 * If NULL, the default compare function is used where pointers are compared.
 * @return: Pointer to the freed data.
 */
void *queue_remove(struct queue *queue, void *data, compare_func cmp);

#ifdef __cplusplus
}
#endif

#endif /* QUEUE_H */
