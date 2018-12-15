#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <stdio.h>
#include <float.h>

typedef void* ptr;

/*for reallocing
 */
ptr ra(ptr pt, const unsigned int i);

/*for allocing
 */
ptr ma(const unsigned int i);

#endif /*DEFS_H*/
