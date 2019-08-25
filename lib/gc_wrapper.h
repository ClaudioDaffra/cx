#ifndef gc_wrapper
#define gc_wrapper

#ifdef __linux__
#define _GNU_SOURCE 
#endif

#define free    gcFree
#define malloc  gcMalloc
#define realloc gcRealloc

#endif

