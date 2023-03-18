#ifndef _DBG_H
#define _DBG_H

// Useful debugging macros
#ifdef DEBUG
    // Only compile this if `#define DEBUG`
    #define DBG(x) x
    // Wrapper for printf that shows the file and line number.
    #define DP(...) (printf("[%s:%d] ", __FILE__, __LINE__), printf(__VA_ARGS__))
#else
    // Remove these from compilation by replacing them with nothing.
    #define DBG(x)
    #define DP(x, ...)
#endif

#ifdef RELEASE_
    #define RELEASE(x) x
#else
    #define RELEASE(x) 
#endif

#endif
