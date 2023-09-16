/* Singly linked list implementation.
 * PROBABLY NOT THREAD SAFE.
 */
#ifndef SLINKEDLIST_H
#define SLINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

/* A node in the list.
 * It is a singly linked list so only holds next.
 */
struct snode {
    struct snode *next;
    void *data;
};

/* Function type for comparing data pointers. Returns
 * 0 when they are equal
 */
typedef int compare_func(void*, void*);

/* Adds a node to the beginning of the list.
 * @param head: Pointer to the head of the list. Is a pointer to 
 * a pointer because add will change head. Must not be NULL.
 * @param data: A pointer to the data. Must not be NULL.
 * @return: Pointer to the inserted node.
 */
struct snode *slist_add(struct snode **head, void *data);

/* Adds a node to the index of the list.
 * @param head: Pointer to the head of the list. Is a pointer to
 * a pointer because add will change head. Must not be NULL.
 * @param data: A pointer to the data. Must not be NULL.
 * @param index: The index to add the node to. Must be less than or equal to the length of the list.
 * @return: Poiner to the inserted node
 */
struct snode *slist_insert(struct snode **head, void *data, unsigned int index);

/* Searches through the list for the node with the given data.
 * @param head: Pointer to the head node. Must not be NULL.
 * @param data: A pointer to the data to search for. Must not be NULL.
 * @param cmp: A compare function that compares the underlying data. If NULL,
 * a default comapare function is used that just compares the pointers.
 * @return: A pointer to the node with the given data, NULL if not found.
 */
struct snode *slist_search(struct snode *head, void *data, compare_func *cmp);

/* Removes a node from the list. The node is freed, but the data is not.
 * The data will still be valid after this function, so free it, use it, who cares!
 * @param head: Pointer to head. Must not be NULL.
 * @param data: A pointer to the data to remove. Must not be NULL.
 * @param cmp: A compare function that compares the underlying data. If NULL,
 * a default comapare function is used that just compares the pointers.
 * @return: A pointer to the data on success, NULL otherwise.
 */
void *slist_remove(struct snode **head, void *data, compare_func *cmp);

#ifdef __cplusplus
}
#endif
#endif /* SLINKEDLIST_H */
