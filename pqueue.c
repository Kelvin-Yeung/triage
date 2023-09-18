#include "pqueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// === struct pqnode =========================================================

struct pqnode {
    struct patient *patient; // data
    struct pqnode *next;     // next node
    struct pqnode *prev;     // previous node
};

// === struct pqueue =========================================================

struct pqueue {
    struct pqnode *front;       // pointer to the first patient in the pqueue
    struct pqnode *back;        // pointer to the last patient in the pqueue
    struct pqnode **priorities; // array that holds pointers to the frist
                                //   patient with a certain priority
};

const int NUM_PRIO_LVLS = 9;

// See pqueue.h for documentation.
struct pqueue *pqueue_create() {
    struct pqueue *pq = malloc(sizeof(struct pqueue));
    assert(pq);
    pq->front = NULL;
    pq->back = NULL;
    pq->priorities = malloc(NUM_PRIO_LVLS * sizeof(struct pqnode *)); // MAGIC #
    assert(pq->priorities);
    for (int i = 0; i < NUM_PRIO_LVLS; ++i) {
        pq->priorities[i] = NULL;   
    }
    return pq;
}

// See pqueue.h for documentation.
void pqueue_destroy(struct pqueue *pq) {
    assert(pq);
    struct pqnode *temp = pq->front;
    struct pqnode *tempnext = NULL;
    while (temp) {
        tempnext = temp->next;
        patient_destroy(temp->patient);
        free(temp);
        temp = tempnext;
    }
    free(pq->priorities);
    free(pq);
}

// See pqueue.h for documentation.
void pqueue_enqueue(struct pqueue *pq, struct patient *p) {
    assert(pq);
    assert(p);
    struct pqnode *node = malloc(sizeof(struct pqnode));
    assert(node);
    node->patient = p;
    int lowest_prio = 0;
    int highest_prio = 0;
    int curr_prio = patient_priority(p);
    for (int i = 0; i < NUM_PRIO_LVLS; ++i) {
        if (pq->priorities[i]) {
            lowest_prio = i + 1;
            break;
        }
    }
    for (int i = NUM_PRIO_LVLS - 1; i >= 0; --i) {
        if (pq->priorities[i]) {
            highest_prio = i + 1;
            break;
        }
    }
    if (!pq->front) { // Case: Empty pq
        node->next = NULL;
        node->prev = NULL;
        pq->front = node;
        pq->back = node;
    } else if (curr_prio < lowest_prio) { // Case: Front insertion
        node->prev = NULL;
        node->next = pq->front;
        pq->front->prev = node;
        pq->front = node;
    } else if (curr_prio >= highest_prio) { // Case: Back insertion
        node->next = NULL;
        node->prev = pq->back;
        pq->back->next = node;
        pq->back = node;
    } else { // Case: Middle insertion
        int smallest_greater_prio = 0; // Smallest priority level that exists and is greater than curr_prio - doesn't hold the index of the corresponding priorities array - holds the actual value instead
        for (int i = 0; i < NUM_PRIO_LVLS; ++i) {
            if (pq->priorities[i] && i + 1 > curr_prio) {
                smallest_greater_prio = i + 1;
                break;
            }
        }
        node->prev = pq->priorities[smallest_greater_prio - 1]->prev;
        node->next = pq->priorities[smallest_greater_prio - 1];
        pq->priorities[smallest_greater_prio - 1]->prev->next = node;
        pq->priorities[smallest_greater_prio - 1]->prev = node;
    }
    if (!pq->priorities[curr_prio - 1]) {
        pq->priorities[curr_prio - 1] = node;
    }
}

// See pqueue.h for documentation.
struct patient *pqueue_dequeue(struct pqueue *pq) {
    assert(pq);
    assert(!pqueue_empty(pq));
    
    if (!pq->front->next) {
        struct patient *p = pq->front->patient;
        struct pqnode *old_front = pq->front;
        int curr_prio = patient_priority(pq->front->patient);
        free(old_front);
        pq->front = NULL;
        pq->back = NULL;
        pq->priorities[curr_prio - 1] = NULL;
        return p;
    } else {
        struct patient *p = pq->front->patient;
        struct pqnode *old_front = pq->front;
        int curr_prio = patient_priority(pq->front->patient);
        int next_prio = patient_priority(pq->front->next->patient);
        if (curr_prio == next_prio) {
            pq->priorities[curr_prio - 1] = pq->front->next;
        } else {
            pq->priorities[curr_prio - 1] = NULL;
        }
        pq->front = pq->front->next;
        pq->front->prev = NULL;
        free(old_front);
        return p;
    }
}

// See pqueue.h for documentation.
struct patient *pqueue_front(const struct pqueue *pq) {
    assert(pq);
    assert(!pqueue_empty(pq));
    struct patient *copy = patient_clone(pq->front->patient);
    return copy;
}

// See pqueue.h for documentation.
bool pqueue_empty(const struct pqueue *pq) {
    assert(pq);
    return !pq->front;
}

// See pqueue.h for documentation.
void pqueue_print(const struct pqueue *pq) {
    assert(pq);
    printf("Patient queue");
    struct pqnode *cur = pq->front;
    while (cur != NULL) {
        printf(" -> ");
        patient_print(cur->patient);
        cur = cur->next;
    }
    printf("\n");
}

// See pqueue.h for documentation.
void pqueue_print_reverse(const struct pqueue *pq) {
    assert(pq);
    struct pqnode *cur = pq->back;
    while (cur != NULL) {
        patient_print(cur->patient);
        printf(" <- ");
        cur = cur->prev;
    }
    printf("Patient queue\n");
}