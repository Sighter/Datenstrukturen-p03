
#include "intList.h"


int main ()
{
    intList iL;

    int i;
    for (i = 2; i <= 50; i++)
        iL.insert(i);

    iL.print();
    
    
    /* remove all even numbers */
    for (i = 2; i <= 50; i++)
    {
        if (i % 2 == 0)
            iL.remove(i);
    }
    
    iL.print();

    /* remove all numbers which are divisible through 3 */
    for (i = 2; i <= 50; i++)
    {
        if (i % 3 == 0)
            iL.remove(i);
    }
    
    iL.print();

    /* remove all numbers which are divisible through 5 */
    for (i = 2; i <= 50; i++)
    {
        if (i % 5 == 0)
            iL.remove(i);
    }
    
    iL.print();
    iL.printMemMap();

}
    
