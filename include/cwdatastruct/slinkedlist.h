#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/* Singly linked list
 * NOT THREAD SAFE
 */

struct snode {
    void *data;
    struct snode *next;
};

struct slist {
    struct snode *head;
    struct snode *tail;
    size_t size;
};

/* General error codes. DO NOT USE 1 OR 2 FOR FUNCTION SPECIFIC ERROR CODES! */
#define SLIST_NULL 1
#define SLIST_NULL_DATA 2

/* Inits a list. If NULL is returned, the list could not be allocated */
struct slist *slist_init(void);

/* Clones a list.
 * @param is_deep_clone: If ~0, the data will be copied to the new list. If 0, the data will be copied by reference.
 * @param size_of_data: The size of the data in bytes. Only used if is_deep_clone is ~0
 * @return: NULL if the list could not be allocated or deep copying fails, otherwise a pointer to the new list
 */
struct slist *slist_clone(struct slist *list, char is_deep_clone, size_t size_of_data);

#define SLIST_ADD_FAILED_MALLOC_NODE 3

/* Adds a node to the list. Returns 0 on success, something else otherwise */
int slist_add(struct slist *list, void *data);

#define SLIST_REMOVE_NOT_FOUND 3
#define SLIST_REMOVE_FAILED_FREE_NODE 4

struct snode *slist_search(struct slist *list, void *data);

/* Removes a node from the list. Returns a pointer to the data on success, NULL otherwise */
void *slist_remove(struct slist *list, void *data);

#define SLIST_FREE_DATA 1
#define SLIST_DO_NOT_FREE_NODES 2
void slist_free(struct slist *list, char options);

#ifdef __cplusplus
}
#endif
#endif /* SLINKEDLIST_H */
