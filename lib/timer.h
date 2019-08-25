
#ifndef cdTimer
#define cdTimer

#include <assert.h>
#include <stdlib.h>
#include "pthread.h"
#include "gc.h"

typedef struct timeTimerCB_s
{
    int    sec          ;
    void (*cb)(void*)   ;
    int    fInterval    ;
    void*  arg          ;
} timeTimerCB_t ;

void*       timeTimer   (void *_t ) ;
pthread_t  timer       ( int flag , void *cb,int sec,void* arg) ;

#define setInterval(CB,SEC,ARG)   timer( 1 , CB , SEC , ARG )
#define setTimeOut(CB,SEC,ARG)    timer( 0 , CB , SEC , ARG )

#endif

/**/