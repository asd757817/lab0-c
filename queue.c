/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
        return q;
    }
    return NULL;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q) {
        if (q->head) {
            /* How about freeing the list elements and the strings? */
            /* Free queue structure */
            list_ele_t *to_be_free = q->head;
            while (to_be_free) {
                q->head = q->head->next;
                free(to_be_free->value);
                free(to_be_free);
                to_be_free = q->head;
            }
        }
        free(q);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q || !s) {
        return false;
    } else {
        list_ele_t *newh;
        newh = malloc(sizeof(list_ele_t));
        char *s_cpy = malloc(strlen(s) + 1);
        // int s_size = sizeof(s);
        /* What should you do if the q is NULL? */
        /* Don't forget to allocate space for the string and copy it */
        /* What if either call to malloc returns NULL? */
        if (newh && s_cpy) {
            strcpy(s_cpy, s);
            newh->value = s_cpy;
            newh->next = q->head;
            if (q->head) {
                q->head->prev = newh;
            }
            q->head = newh;
            if (!q->tail)
                q->tail = newh;
            q->size += 1;
            return true;
        } else {
            if (newh)
                free(newh);
            if (s_cpy)
                free(s_cpy);
            return false;
        }
    }
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q || !s) {
        return false;
    } else {
        list_ele_t *newh;
        newh = malloc(sizeof(list_ele_t));
        char *s_cpy = malloc(strlen(s) + 1);
        // int s_size = sizeof(s);
        if (newh && s_cpy) {
            // strncpy(s_cpy, s, s_size);
            s_cpy = strcpy(s_cpy, s);
            newh->next = NULL;
            newh->value = s_cpy;
            newh->prev = q->tail;
            if (q->head == NULL)
                q->head = newh;
            if (q->tail != NULL)
                q->tail->next = newh;
            q->tail = newh;
            q->size += 1;
            return true;
        } else {
            if (s_cpy)
                free(s_cpy);
            if (newh)
                free(newh);
            return false;
        }
    }
}


/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (!q) {
        return false;
    } else if (!q->head) {
        return false;
    } else {
        /* You need to fix up this code. */
        /* How about freeing the list elements and the strings? */
        /* Free queue structure */
        if (sp) {
            memset(sp, '\0', bufsize);
            strncpy(sp, q->head->value + '\0', bufsize - 1);
            printf("%s\n", sp);
        }
        list_ele_t *to_be_free = q->head;
        q->head = q->head->next;
        if (q->size == 1 && !q->head) {
            q->tail = NULL;
        }
        free(to_be_free->value);
        free(to_be_free);
        q->size -= 1;
        return true;
    }
}


/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q)
        return q->size;
    else
        return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q && q->size > 1) {
        q->tail = q->head;
        list_ele_t *pre_node = NULL;
        list_ele_t *next_node = q->head->next;
        while (next_node) {
            q->head->next = pre_node;
            pre_node = q->head;
            q->head = next_node;
            next_node = q->head->next;
        }
        q->head->next = pre_node;
    }
}
