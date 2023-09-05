#include "cwdatastruct/slinkedlist.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void slist_init_test();
void slist_add_test();
void slist_remove_test();
void slist_search_test();
void slist_clone_test();


/* Look, this may be really gross and incomprehensible, but it took no time to write and it works. 
 * Now I can be 90% sure the linked list works
 */
int main(void) {
    slist_init_test();
    slist_add_test();
    slist_remove_test();
    slist_search_test();
    slist_clone_test();
    return 0;
}

void slist_init_test() {
    struct slist *list = slist_init();
    assert(list != NULL);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);

    slist_free(list, 0);
}

void slist_add_test() {
    struct slist *list = slist_init();
    assert(list != NULL);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;

    assert(slist_add(NULL, NULL) != 0);
    assert(slist_add(list, NULL) == SLIST_NULL_DATA);
    assert(slist_add(NULL, &a) == SLIST_NULL);

    slist_add(list, &a);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 1);
    assert(list->head->data == &a);
    assert(list->tail->data == &a);

    slist_add(list, &b);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 2);
    assert(list->head->data == &a);
    assert(list->tail->data == &b);

    slist_add(list, &c);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 3);
    assert(list->head->data == &a);
    assert(list->tail->data == &c);

    slist_add(list, &d);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 4);
    assert(list->head->data == &a);
    assert(list->tail->data == &d);

    struct snode *curr = list->head;
    assert(curr->data == &a);
    assert(curr->next->data == &b);

    curr = curr->next;
    assert(curr->data == &b);
    assert(curr->next->data == &c);

    curr = curr->next;
    assert(curr->data == &c);
    assert(curr->next->data == &d);

    curr = curr->next;
    assert(curr->data == &d);
    assert(curr->next == NULL);

    slist_free(list, 0);
}

void slist_remove_size_1() {
    struct slist *list = slist_init();
    int a = 5;
    slist_add(list, &a);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 1);
    assert(list->head->data == &a);
    assert(list->tail->data == &a);

    slist_remove(list, &a);
    assert(list->head == NULL);
    assert(list->tail == NULL);
    assert(list->size == 0);

    slist_free(list, 0);
}

void slist_remove_size_2() {
    struct slist *list = slist_init();
    int a = 5;
    int b = 6;
    slist_add(list, &a);
    slist_add(list, &b);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 2);
    assert(list->head->data == &a);
    assert(list->tail->data == &b);

    slist_remove(list, &a);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 1);
    assert(list->head->data == &b);
    assert(list->tail->data == &b);

    slist_add(list, &a);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 2);
    assert(list->head->data == &b);
    assert(list->tail->data == &a);

    slist_remove(list, &a);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 1);
    assert(list->head->data == &b);
    assert(list->tail->data == &b);

    slist_free(list, 0);
}

void slist_remove_general() {
    struct slist *list = slist_init();
    int a = 5;
    int b = 6;
    int c = 7;
    int d = 8;
    slist_add(list, &a);
    slist_add(list, &b);
    slist_add(list, &c);
    slist_add(list, &d);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 4);
    assert(list->head->data == &a);
    assert(list->tail->data == &d);

    assert(slist_remove(NULL, NULL) == NULL);
    assert(slist_remove(list, NULL) == NULL);
    assert(slist_remove(NULL, &a) == NULL);
    
    slist_remove(list, &a);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 3);
    assert(list->head->data == &b);
    assert(list->tail->data == &d);

    slist_add(list, &a);
    slist_remove(list, &a);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 3);
    assert(list->head->data == &b);
    assert(list->tail->data == &d);

    slist_remove(list, &c);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 2);
    assert(list->head->data == &b);
    assert(list->tail->data == &d);

    slist_free(list, 0);
}

void slist_remove_test() {
    slist_remove_size_1();
    slist_remove_size_2();
    slist_remove_general();
}

void slist_search_test() {
    struct slist *list = slist_init();
    int a = 5;
    int b = 6;
    int c = 7;
    int d = 8;
    slist_add(list, &a);
    slist_add(list, &b);
    slist_add(list, &c);
    slist_add(list, &d);
    assert(list->head != NULL);
    assert(list->tail != NULL);
    assert(list->size == 4);
    assert(list->head->data == &a);
    assert(list->tail->data == &d);

    assert(slist_search(NULL, NULL) == NULL);
    assert(slist_search(list, NULL) == NULL);
    assert(slist_search(NULL, &a) == NULL);

    struct snode *found = slist_search(list, &a);
    assert(found != NULL);
    assert(found->data == &a);

    found = slist_search(list, &b);
    assert(found != NULL);
    assert(found->data == &b);

    found = slist_search(list, &c);
    assert(found != NULL);
    assert(found->data == &c);

    found = slist_search(list, &d);
    assert(found != NULL);
    assert(found->data == &d);

    found = slist_search(list, &a);
    assert(found != NULL);
    assert(found->data == &a);

    found = slist_search(list, &b);
    assert(found != NULL);
    assert(found->data == &b);

    found = slist_search(list, &c);
    assert(found != NULL);
    assert(found->data == &c);

    found = slist_search(list, &d);
    assert(found != NULL);
    assert(found->data == &d);

    int e = 9;
    found = slist_search(list, &e);
    assert(found == NULL);

    slist_free(list, 0);
}


void slist_clone_test() {
    struct slist *list_original = slist_init();
    int a = 5;
    int b = 6;
    int c = 7;

    slist_add(list_original, &a);
    slist_add(list_original, &b);
    slist_add(list_original, &c);

    struct slist *list_clone = slist_clone(list_original, 0, sizeof(int));
    assert(list_clone != NULL);
    assert(list_clone->head != NULL);
    assert(list_clone->tail != NULL);
    assert(list_clone->size == 3);
    assert(list_clone->head->data == &a);
    assert(list_clone->tail->data == &c);

    printf("%p list clone\n", list_clone);
    printf("%p list original\n", list_original);

    printf("%p list clone head\n", list_clone->head);
    printf("%p list original head\n", list_original->head);

    struct slist *list_clone_deep = slist_clone(list_original, 1, sizeof(int));
    assert(list_clone_deep != NULL);
    assert(list_clone_deep->head != NULL);
    assert(list_clone_deep->tail != NULL);
    assert(list_clone_deep->size == 3);
    assert(*((int *)list_clone_deep->head->data) == a);
    assert(*((int *)list_clone_deep->tail->data) == c);
    assert(list_clone_deep->head->data != list_original->head->data);
    assert(list_clone_deep->tail->data != list_original->tail->data);

    slist_free(list_original, 0);
    slist_free(list_clone, 2);
}
