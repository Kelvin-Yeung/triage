#include "patient.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

const int MAX_NAME_LEN = 30;

struct patient {
    int prio;
    char name[31]; 
};

struct patient *patient_read(void) {
    int prio = 0;
    int prio_retval = scanf("%d", &prio);
    assert(prio_retval == 1);
    assert(prio > 0);
    char name[31] = {0};
    int name_retval = scanf(" %s", name);
    assert(name_retval >= 1);
    struct patient *p = malloc(sizeof(struct patient));
    assert(p);
    p->prio = prio;
    strcpy(p->name, name);
    return p;
}

struct patient *patient_clone(const struct patient *p) {
    assert(p);
    struct patient *dup = malloc(sizeof(struct patient));
    assert(dup);
    dup->prio = p->prio;
    strcpy(dup->name, p->name);
    return dup;
}

void patient_destroy(struct patient *p) {
    assert(p);
    free(p);
    p = NULL;
}

int patient_priority(const struct patient *p) {
    return p->prio;
}

void patient_print(const struct patient *p) {
    assert(p);
    printf("(%d) %s", p->prio, p->name);
}