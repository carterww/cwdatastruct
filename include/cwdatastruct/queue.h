/* Queue implementation using linked list
 * NOT THREAD SAFE.
 */
#ifndef QUEUE_H
#define QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "slinkedlist.h"

/* A queue is just a singly linked list alias in this case.
 * The functions are just wrappers around the singly linked list functions
 * that make it easier to manage a queue. Some functions may require a
 * special implementation that does not simply wrap the singly linked list
 * function(s).
 */
struct queue {
    struct slist *list;
};


/* General error codes. DO NOT USE 1 OR 2 FOR FUNCTION SPECIFIC ERROR CODES. */
#define QUEUE_NULL 1
#define QUEUE_NULL_DATA 2

/* Initializes a queue.
 * @return: NULL if the queue could not be allocated, otherwise a pointer to the queue.
 */
struct queue *queue_init();

/* Adds a node to the end of the queue.
 * @param queue: The queue to add to. Must not be NULL.
 * @param data: A pointer to the data. Must not be NULL.
 * @return: 0 on success, an error code otherwise.
 */
int queue_enqueue(struct queue *queue, void *data);

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

/* Gets the size of the queue.
 * @param queue: The queue to get the size of. Must not be NULL.
 * @return: The size of the queue.
 * @note: This can also be accessed through the slist struct that the queue wraps.
 */
size_t queue_get_size(struct queue *queue);

/* Clones a queue. It can either be a shallow copy where the nodes are just copied, or
 * a deep copy where the nodes and data are allocated and copied.
 * @param queue: The queue to clone. Must not be NULL.
 * @param is_deep_clone: If !0, the data will be copied to the new queue. If 0, the
 * data will be copied by reference.
 * @param size_of_data: The size of the data pointer's value. Only used if is_deep_clone
 * is !0.
 * @return: NULL if the queue could not be allocated or deep copying fails, otherwise a pointer
 * to the new queue.
 */
struct queue *queue_clone(struct queue *queue, char is_deep_clone, size_t size_of_data);

/* Removes items from a queue based on a function passed in.
 * @param queue: The queue to remove from. Must not be NULL.
 * @param should_remove: A function that takes in a data pointer. If it returns
 * something other than 0, the node will be removed.
 * @param free_data: A function that is responsible for freeing the data in a node.
 * @param options: A bitfield of options. QUEUE_FREE_DATA will free the data pointers,
 * QUEUE_DO_NOT_FREE_NODES will not free the nodes or data.
 * @returns: void
 * @note: For more information on freeing the queue, nodes, and data, check the notes
 * of queue_free in cwdatastruct/queue.h.
 */
void queue_remove(struct queue *queue, int (*should_remove)(void *), void (*free_data)(void *), char options);

#define QUEUE_FREE_DATA 0x1
#define QUEUE_DO_NOT_FREE_NODES 0x2
/* Frees the queue and nodes by default, but this can be changed with options.
 * @param queue: The queue to free. Must not be NULL.
 * @param free_data: A function that frees the data pointer. Can be NULL.
 * @param options: A bitfield of options. QUEUE_FREE_DATA will free the data pointers,
 * QUEUE_DO_NOT_FREE_NODES will not free the nodes.
 * @return: void
 * @note: The QUEUE_DO_NOT_FREE_NODES option was added for scenarios where there is a shallow
 * copy of the list somewhere and you don't want to free the nodes.
 * @note: If options has QUEUE_FREE_DATA, free_data must not be NULL.
 */
void queue_free(struct queue *queue, void (*free_data)(void *), char options);

#ifdef __cplusplus
}
#endif

#endif /* QUEUE_H */
