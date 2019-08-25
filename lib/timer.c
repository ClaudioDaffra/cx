
#include "timer.h"

// .......................................................... timer

void* timeTimer(void *_t )
{
    timeTimerCB_t* t = (timeTimerCB_t*) _t ;

    int     sec             = t->sec ;
    void    (*cb)(void*)    = t->cb ;
    int     fInterval       = t->fInterval ;
    void*   arg             = t->arg ;
   
    do {

        sleep(sec);

        (*cb)((void*)arg);

    } while(fInterval) ;

    pthread_exit(NULL);
    
    return NULL;
}

pthread_t timer( int flag , void *cb,int sec,void* arg)
{
    timeTimerCB_t*   timer = (timeTimerCB_t*) malloc(sizeof(timeTimerCB_t));

    timer->sec       = sec;
    timer->cb        = cb ;
    timer->fInterval = flag ;
    timer->arg       = arg ;
 
    gcPush(timer);
 
    pthread_t pt ;
    
    int err = pthread_create( &pt, NULL, &timeTimer , (void *) timer );

    assert ( err==0 ) ;
 
    return pt ;
}



/**/
