#include "common.h"

/* Find the time difference. */
double tdiff(const struct timespec a, const struct timespec b) {
    return (double)( b.tv_sec - a.tv_sec ) + (double)( b.tv_nsec - a.tv_nsec ) / 1E9;
}

/* Return the current time. */
struct timespec now(void) {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t;
}
