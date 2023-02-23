#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *new = malloc(sizeof(struct list_head));
    if (new) {
        INIT_LIST_HEAD(new);
        return new;
    }
    return NULL;
}

/* Free all storage used by queue */
void q_free(struct list_head *l) {}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    element_t *new = malloc(sizeof(element_t));
    if (!new)
        return false;
    int sl = strlen(s);
    new->value = malloc(
        (sl + 1) *
        sizeof(char));  // notice there are (strlen(s)+1) size need to allocate.
    if (!new->value) {
        free(new);
        return false;
    }
    strncpy(new->value, s, sl);
    *(new->value + sl) = '\0';  // add '\0' after string.
    list_add(&new->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    element_t *new = malloc(sizeof(element_t));
    if (!new)
        return false;
    int sl = strlen(s);
    new->value = malloc(
        (sl + 1) *
        sizeof(char));  // notice there are (strlen(s)+1) size need to allocate.
    if (!new->value) {
        free(new);
        return false;
    }
    strncpy(new->value, s, sl);
    *(new->value + sl) = '\0';  // add '\0' after string.
    list_add_tail(&new->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *removed = list_entry(head->next, element_t, list);
    if (!removed)
        return NULL;
    list_del(&removed->list);

    if (bufsize) {
        strncpy(sp, removed->value, bufsize - 1);
    }
    *(removed->value + bufsize - 1) = '\0';
    return removed;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *removed = list_entry(head->prev, element_t, list);
    if (!removed)
        return NULL;
    list_del(&removed->list);

    if (bufsize) {
        strncpy(sp, removed->value, bufsize - 1);
    }
    *(removed->value + bufsize - 1) = '\0';
    return removed;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;
    struct list_head *node;
    int size = 0;
    list_for_each (node, head)
        size++;
    return size;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/de lete-the-middle-node-of-a-linked-list/
    if (!head->next)
        return false;
    struct list_head *rabbit = head->next, *turtle = head->next;

    while (rabbit->next != head && rabbit->next->next != head) {
        rabbit = rabbit->next->next;
        turtle = turtle->next;
    }
    turtle = turtle->next;
    list_del(turtle);

    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head)
        return;

    struct list_head *prev = head->prev, *curr = head, *next = NULL;

    while (next != head) {
        next = curr->next;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head)
{
    struct list_head list_less, list_greater;
    element_t *pivot;
    element_t *item = NULL, *is = NULL;

    if (list_empty(head) || list_is_singular(head))
        return;

    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    pivot = list_first_entry(head, element_t, list);
    list_del(&pivot->list);

    list_for_each_entry_safe (item, is, head, list) {
        if (strcmp(item->value, pivot->value) < 0)
            list_move_tail(&item->list, &list_less);
        else
            list_move_tail(&item->list, &list_greater);
    }

    q_sort(&list_less);
    q_sort(&list_greater);

    list_add(&pivot->list, head);
    list_splice(&list_less, head);
    list_splice_tail(&list_greater, head);
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/

    return 0;
}
