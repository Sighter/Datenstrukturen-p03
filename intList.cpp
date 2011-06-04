
#include "intList.h"

/* constructor */
intList::intList()
:   m_pHead(NULL)
{
    int i = 0;
    for (i = 0; i < MEMSIZE; i++)
        m_aMemoryMap[i] = 0;
}


/* destructor */
intList::~intList()
{
    int i = 0;
    for (i = 0; i < MEMSIZE; i++)
        m_aMemoryMap[i] = 0;
}


/* Exercise A:
 * request space from our "virtual" memory
 * since the program holds a memory map, the reuest method
 * writes a 1 in the memory map array, to show that this field is
 * in use.
 * At this point, it is very important to reinitialize space which 
 * was free'd in the past */
intElem* intList::request()
{
    int i = 0;
    for (i = 0; i < MEMSIZE; i++)
    {
        if (m_aMemoryMap[i] == 0)
        {
            m_aMemoryMap[i] = 1;
            m_aMemory[i].initElem();
            return &(m_aMemory[i]);
        }
    }

    return NULL;
}


/* Exercise B:
 * free space in our virtual memory
 * this method simply writes a 0 in the memory map */
bool intList::free(intElem* pElem)
{
    int i = 0;
    for (i = 0; i < MEMSIZE; i++)
    {
        if (&(m_aMemory[i]) == pElem)
        {
            m_aMemoryMap[i] = 0;
            return true;
        }
    }

    return false;
}
    

/* helper : print memory map */
void intList::printMemMap()
{
#ifdef VERBOSE
    printf("MEMMAP: [ ");
    int i = 0;
    for (i = 0; i < MEMSIZE; i++)
        printf("%d ", m_aMemoryMap[i]);
    printf("]\n");
#endif
} 


/* helper : print int list */
void intList::print()
{
#ifdef VERBOSE
    intElem* pWalker = m_pHead;
    
    while (pWalker != NULL)
    {
        printf("| %d ",pWalker->iData);
        pWalker = pWalker->pNext;
    }

    printf("|\n");
#endif
}

/* Exercise C:
 * insert a element sorted
 *
 * We have to be aware of 3 cases:
 * - insert at head (then the head changes)
 * - insert in the body with a loop 
 * - insert at the tail
 *
 * Since we use the <= operator here, where can be duplicates
 * in the list */
intElem* intList::insert(int iValue)
{

    /* list is empty */
    if (m_pHead == NULL)
    {
        m_pHead = request();
        if (m_pHead == NULL)
            return NULL;

        m_pHead->pNext = NULL;
        m_pHead->pPrev = NULL;
        m_pHead->iData = iValue;

        return m_pHead;
    }

    /* case where value is smaller than th first one */
    if (iValue <= m_pHead->iData)
    {
        m_pHead->pPrev = request();
        if (m_pHead->pPrev == NULL)
            return NULL;

        m_pHead->pPrev->pNext = m_pHead;
        m_pHead = m_pHead->pPrev;
        m_pHead->iData = iValue;

        return m_pHead;
    }

    intElem* pWalker = m_pHead;

    while (pWalker->pNext != NULL)
    {
        if (iValue <= pWalker->pNext->iData)
        {
            intElem* pNew = request();
            if (pNew == NULL)
                return NULL;

            pNew->iData = iValue;
            pNew->pNext = pWalker->pNext;
            pNew->pPrev = pWalker;
            
            pWalker->pNext = pNew;
            pNew->pNext->pPrev = pNew;

            return pNew;
        }
        pWalker = pWalker->pNext;
    }

    /* case where item has to be inserted at the end */
    pWalker->pNext = request();
    if (pWalker->pNext == NULL)
        return NULL;
    
    pWalker->pNext->iData = iValue;
    pWalker->pNext->pPrev = pWalker;

    return pWalker->pNext;
}


/* Exercise D:
 * very simple test if list is empty.
 * The function can be used to search for
 * an element */
intElem* intList::exists(int iValue)
{
    intElem* pWalker = m_pHead;
    
    while (pWalker != NULL)
    {
        if (pWalker->iData == iValue)
            return pWalker;
        else
            pWalker = pWalker->pNext;
    }
    
    return NULL;
}


/* Exercise E:
 * remove an element from list
 *
 * function uses the exists method to search an
 * element, then it will be deleted and pointers
 * are placed correctly */
bool intList::remove(int iValue)
{
    intElem* pTarget = exists(iValue);

    if (pTarget == NULL)
        return false;

    if (pTarget->pPrev == NULL)
    {
        m_pHead = pTarget->pNext;
        pTarget->pNext->pPrev = NULL;
    }
    else if (pTarget->pNext == NULL)
    {
        pTarget->pPrev->pNext = NULL;
    }
    else
    {
        pTarget->pPrev->pNext = pTarget->pNext;
        pTarget->pNext->pPrev = pTarget->pPrev;
    }
    
    free(pTarget);

    return true;
}
