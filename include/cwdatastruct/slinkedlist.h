/* Singly linked list implementation.
 * PROBABLY NOT THREAD SAFE.
 */
#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/* A node in the list.
 * It is a singly linked list so only holds next.
 */
struct snode {
    void *data;
    struct snode *next;
};

/* The list itself. Keeping the tail and size is a design choice just to make life easier.
 * An alternative implementation is just to hold a reference to the head node and use that.
 */
struct slist {
    struct snode *head;
    struct snode *tail;
    size_t _size;
};


/* General error codes. DO NOT USE 1 OR 2 FOR FUNCTION SPECIFIC ERROR CODES. */
#define SLIST_NULL 1
#define SLIST_NULL_DATA 2


/* Inits a singly linked list. 
 * @return: NULL if the list could not be allocated, otherwise a pointer to the list.
 */
struct slist *slist_init(void);

/* Clones a list.
 * @param list: The list to clone. Must not be NULL.
 * @param is_deep_clone: If !0, the data will be copied to the new list. If 0, the
 * data will be copied by reference.
 * @param size_of_data: The size of the data pointer's value. Only used if is_deep_clone
 * is !0.
 * @return: NULL if the list could not be allocated or deep copying fails, otherwise a pointer
 * to the new list.
 * @note: A shallow copy in this case uses the same nodes and data pointers as the original list.
 * Use the SLIST_DO_NOT_FREE_NODES option in slist_free if you want to keep the nodes once
 * a shallow copy needs to be freed.
 */
struct slist *slist_clone(struct slist *list, char is_deep_clone, size_t size_of_data);

#define SLIST_ADD_FAILED_MALLOC_NODE 3
/* Adds a node to the end of the list.
 * @param list: The list to add to. Must not be NULL.
 * @param data: A pointer to the data. Must not be NULL.
 * @return: 0 on success, an error code otherwise.
 */
int slist_add(struct slist *list, void *data);

/* Searches through the list for the node with the given data.
 * @param list: The list to be searched. Must not be NULL.
 * @param data: A pointer to the data to search for. Must not be NULL.
 * @return: A pointer to the node with the given data, NULL if not found.
 */
struct snode *slist_search(struct slist *list, void *data);

#define SLIST_REMOVE_NOT_FOUND 3
#define SLIST_REMOVE_FAILED_FREE_NODE 4
/* Removes a node from the list. The node is freed, but the data is not.
 * The data will still be valid after this function, so free it, use it, who cares!
 * @param list: The list to remove from. Must not be NULL.
 * @param data: A pointer to the data to remove. Must not be NULL.
 * @return: A pointer to the data on success, NULL otherwise.
 */
void *slist_remove(struct slist *list, void *data);

#define SLIST_FREE_DATA 0x1
#define SLIST_DO_NOT_FREE_NODES 0x2
/* Frees the list and nodes by default, but this can be changed with options.
 * @param list: The list to free. Must not be NULL.
 * @param free_data: A function that frees the data pointer. Can be NULL.
 * @param options: A bitfield of options. SLIST_FREE_DATA will free the data pointers,
 * SLIST_DO_NOT_FREE_NODES will not free the nodes.
 * @return: void
 * @note: The SLIST_DO_NOT_FREE_NODES option was added for scenarios where there is a shallow
 * copy of the list somewhere and you don't want to free the nodes.
 * @note: If options has SLIST_FREE_DATA, free_data must not be NULL.
 */
void slist_free(struct slist *list, void (*free_data)(void *data), char options);

#ifdef __cplusplus
}
#endif
#endif /* SLINKEDLIST_H */
