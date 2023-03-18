#ifndef _TIMEIT_H
#define _TIMEIT_H
#include <time.h>

// Get the elapsed time from two `now()` calls.
double tdiff(const struct timespec a, const struct timespec b);

// Get the current time
struct timespec now(void);

#endif
