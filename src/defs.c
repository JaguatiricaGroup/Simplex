#include "defs.h"

/*for reallocing
 */
ptr
ra(ptr pt, const unsigned int i)
{
    ptr f = NULL;
    f = realloc(pt,i);
    if(!f && i > 0)
    {
        printf("Insufficient Memory! Aborting...\n");
        exit(1);
    }
    return f;
}

/*for allocing
 */
ptr
ma(const unsigned int i)
{
    ptr f = NULL;
    f = malloc(i);
    if(!f)
    {
        printf("Insufficient Memory! Aborting...\n");
        exit(1);
    }
    return f;
}
