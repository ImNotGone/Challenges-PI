#include "set.h"
#include <stdlib.h>

typedef struct node {
    elemType elem;
    struct node * tail;
} TNode;

typedef TNode * TList;

typedef struct setCDT {
    elemTypeComparator compare;
    size_t size;
    TList first;
} setCDT;

static void freeList(TList first);
static TList findElem(TList first, elemType elem, elemTypeComparator compare);
static TList addRec(TList first, elemType elem, elemTypeComparator compare, int * added);
static TList delRec(TList first, elemType elem, elemTypeComparator compare, int * deleted);
static TList addInsersecRec(TList l1, TList l2, elemTypeComparator compare, size_t * size);
static TList addDiffRec(TList l1, TList l2, elemTypeComparator compare, size_t * size);

/* Retorna un nuevo conjunto vacío */
setADT newSet(int (*compare)(elemType, elemType)) {
    setADT new = malloc(sizeof(setCDT));

    new->compare = compare;
    new->size = 0;
    new->first = NULL;

    return new;
}

void freeSet(setADT set) {
    freeList(set->first);
    free(set);
}

int isEmptySet(setADT set) {
    return set->size == 0;
}

int setContains(const setADT set, elemType element) {
    return findElem(set->first, element, set->compare) != NULL;
}

int addElement(setADT set, elemType element) {
    int added = 0;
    set->first = addRec(set->first, element, set->compare, &added);
    if(added) {
        set->size++;
    }
    return added;
}

int deleteElement(setADT set, elemType element) {
    int deleted = 0;
    set->first = delRec(set->first, element, set->compare, &deleted);
    if(deleted) {
        set->size--;
    }
    return deleted;
}

int sizeSet(const setADT set) {
    return set->size;
}

setADT unionSet(setADT set1, setADT set2) {
    setADT new = newSet(set1->compare);

    TList aux = set1->first;

    while (aux != NULL) {
        addElement(new, aux->elem);
        aux = aux->tail;
    }

    aux = set2->first;

    while (aux != NULL) {
        addElement(new, aux->elem);
        aux = aux->tail;
    }

    return new;
}

setADT intersectionSet(setADT set1, setADT set2) {
    setADT new = newSet(set1->compare);

    new->first = addInsersecRec(set1->first, set2->first, new->compare, &new->size);

    return new;
}

setADT diffSet(setADT set1, setADT set2) {
    setADT new = newSet(set1->compare);

    new->first = addDiffRec(set1->first, set2->first, new->compare, &new->size);

    return new;
}

static void freeList(TList first) {
    if(first == NULL) return;
    freeList(first->tail);
    free(first);
}
static TList findElem(TList first, elemType elem, elemTypeComparator compare) {
    int c;
    if(first == NULL || (c = compare(first->elem, elem)) > 0) {
        return NULL;
    }
    if(c == 0) {
        return first;
    }
    return findElem(first->tail, elem, compare);
}
static TList addRec(TList first, elemType elem, elemTypeComparator compare, int * added) {
    int c;
    if(first == NULL || (c = compare(first->elem, elem)) > 0) {
        TList new = malloc(sizeof(TNode));
        new->elem = elem;
        new->tail = first;
        *added = 1;
        return new;
    }
    if(c == 0) {
        *added = 0;
        return first;
    }
    first->tail = addRec(first->tail, elem, compare, added);
    return first;
}
static TList delRec(TList first, elemType elem, elemTypeComparator compare, int * deleted) {
    int c;
    if(first == NULL || (c = compare(first->elem, elem)) > 0) {
        *deleted = 0;
        return first;
    }
    if(c == 0) {
        TList aux = first->tail;
        free(first);
        *deleted = 1;
        return aux;
    }
    first->tail = delRec(first->tail, elem, compare, deleted);
    return first;
}

static TList addInsersecRec(TList l1, TList l2, elemTypeComparator compare, size_t * size) {
    if(l1 == NULL || l2 == NULL) {
        return NULL;
    }
    int c = compare(l1->elem, l2->elem);
    if(c > 0) {
        return addInsersecRec(l1, l2->tail, compare, size);
    }

    if(c < 0) {
        return addInsersecRec(l1->tail, l2, compare, size);
    }

    TList new = malloc(sizeof(TNode));
    new->elem = l1->elem;
    new->tail = addInsersecRec(l1->tail, l2->tail, compare, size);
    (*size)++;
    return new;
}

static TList addDiffRec(TList l1, TList l2, elemTypeComparator compare, size_t * size) {
    if(l1 == NULL && l2 == NULL) {
        return NULL;
    }
    if(l2 == NULL) {
        return addDiffRec(l2, l1, compare, size);
    }

    int c;
    if(l1 == NULL || (c = compare(l1->elem, l2->elem)) > 0) {
        TList new = malloc(sizeof(TNode));
        new->elem = l2->elem;
        new->tail = addDiffRec(l1, l2->tail, compare, size);
        (*size)++;
        return new;
    }
    if(c == 0) {
        return addDiffRec(l1->tail, l2->tail, compare, size);
    }

    TList new = malloc(sizeof(TNode));
    new->elem = l1->elem;
    new->tail = addDiffRec(l1->tail, l2, compare, size);
    (*size)++;
    return new;

}
