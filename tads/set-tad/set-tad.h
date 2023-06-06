#ifndef __SETADTH_
#define __SETADTH_

typedef char * elemType;

typedef struct setCDT * setADT;
typedef int(*elemTypeComparator)(elemType, elemType);

/* Retorna un nuevo conjunto vacío */
setADT newSet(elemTypeComparator compare);

void freeSet(setADT set);

int isEmptySet(setADT set);

int setContains(const setADT set, elemType element);

int addElement(setADT set, elemType element);

int deleteElement(setADT set, elemType element);

int sizeSet(const setADT set);

setADT unionSet(setADT set1, setADT set2);

setADT intersectionSet(setADT set1, setADT set2);

setADT diffSet(setADT set1, setADT set2);

#endif
