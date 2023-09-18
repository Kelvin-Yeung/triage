#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "pqueue.h"

// The program accepts the following commands:
// * ENQ <priority:int> <name:string>
//   Enqueues a new patient with name and priority; priotiy must be between 1
//   and 9 (both included), where 1 is the highest and 9 the lowest priority.
// * DEQ
//   Dequeues and prints the patient at the front of the queue.
// * FRONT
//   Prints the patient at the front of the queue.
// * EMPTY
//   Prints if the queue is empty or not.
// * PRINT
//   Prints the queue in priority order, i.e. starting with the highest
//   priority.
// * PRINT_REV
//   Prints the queue in reverse order, i.e. starting with the lowest
//   priority.
int main(void) {
    const char CMD_ENQ[] = "ENQ";
    const char CMD_DEQ[] = "DEQ";
    const char CMD_FRONT[] = "FRONT";
    const char CMD_EMPTY[] = "EMPTY"; 
    const char CMD_PRINT[] = "PRINT";
    const char CMD_PRINT_REV[] = "PRINT_REV";

    struct pqueue *pq = pqueue_create();

    char cmd[10] = {};
    while (scanf("%s", cmd) > 0) {
        if (strcmp(cmd, CMD_ENQ) == 0) {
            pqueue_enqueue(pq, patient_read());
        } else if (strcmp(cmd, CMD_DEQ) == 0) {
            struct patient *p = pqueue_dequeue(pq);
            patient_print(p);
            printf("\n");
            patient_destroy(p);
        } else if (strcmp(cmd, CMD_FRONT) == 0) {
            struct patient *p = pqueue_front(pq);
            patient_print(p);
            printf("\n");
            patient_destroy(p);
        } else if (strcmp(cmd, CMD_EMPTY) == 0) {
            printf("The patient queue is%sempty.\n", pqueue_empty(pq) ? " " : " not ");
        } else if (strcmp(cmd, CMD_PRINT) == 0) {
            pqueue_print(pq);
        } else if (strcmp(cmd, CMD_PRINT_REV) == 0) {
            pqueue_print_reverse(pq);
        } else {
            printf("ERROR: unknown command\n");
            break;
        }
    }
    pqueue_destroy(pq);
}