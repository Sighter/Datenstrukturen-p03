
#ifndef INTLIST_H
#define INTLIST_H


#ifndef NULL
#define NULL 0
#endif

//define VERBOSE

#define MEMSIZE 1000

#ifdef VERBOSE
#include <stdio.h>
#endif

/* Exercise:
 * *********
 * This is the structure for intList class with all needed
 * pointers for the both-way-linked list
 * 
 * constructors an manual callable init function are also
 * defined here */
struct intElem
{
    int iData;
    intElem* pPrev;
    intElem* pNext;
    
    intElem()
    :   iData(0),
        pPrev(NULL),
        pNext(NULL)
    {
    }

    void initElem()
    {
        iData = 0;
        pPrev = NULL;
        pNext = NULL;
    }
};


/* Exercise:
 * class to manage the intList
 * Here we hold a big array of structures of type intElem 
 * Also a simple memory map is declared here. It has type bool.
 * So its possible to mark empty space with 0 and a used structure
 * with 1.
 * The define MEMSIZE defines the memory size */
class intList
{
    intElem* m_pHead;

    intElem m_aMemory[MEMSIZE];
    bool m_aMemoryMap[MEMSIZE];

    public:
    intList();
    ~intList();
    intElem* request();
    bool free(intElem* pElem);
    void printMemMap();
    void print();
    intElem* insert(int iValue);
    intElem* exists(int iValue);
    bool remove(int iValue);
};

#endif
