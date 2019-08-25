
#include "../lib/pthread.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
    stack overflow :
    
    C Threads to print sequence of numbers, 
    with even and odd number printing threads running parallely
    
*/

/*
    cl test\ex_pthread_4.c /Fex.exe            /EHsc /WX   
    

*/

pthread_mutex_t mainMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t oddMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t evenMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mainCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t oddCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t evenCond = PTHREAD_COND_INITIALIZER;

void *printOdd( void *arg )
{
    pthread_mutex_lock( &oddMutex );        // grab the odd mutex

    pthread_mutex_lock( &mainMutex );       // signal main that the odd thread
    pthread_cond_signal( &mainCond );       // is locked and ready for action
    pthread_mutex_unlock( &mainMutex );

    for ( int counter = 1; counter < 50; counter += 2 )
    {
        pthread_cond_wait( &oddCond, &oddMutex );   // wait for the odd signal
        printf( "%d\n", counter );

        pthread_mutex_lock( &evenMutex );   // signal the even thread
        pthread_cond_signal( &evenCond );
        pthread_mutex_unlock( &evenMutex );

        sleep( 1000 );
    }

    pthread_mutex_unlock( &oddMutex );
    return NULL;
}

void *printEven( void *arg )
{
    pthread_mutex_lock( &evenMutex );       // grab the even mutex

    pthread_mutex_lock( &mainMutex );       // signal main that the even thread
    pthread_cond_signal( &mainCond );       // is locked and ready for action
    pthread_mutex_unlock( &mainMutex );

    for ( int counter = 2; counter < 50; counter += 2 )
    {
        pthread_cond_wait( &evenCond, &evenMutex ); // wait for the even signal
        printf( "%d\n", counter );

        pthread_mutex_lock( &oddMutex );    // signal the odd thread
        pthread_cond_signal( &oddCond );
        pthread_mutex_unlock( &oddMutex );

        sleep( 1000 );
    }

    pthread_mutex_unlock( &evenMutex );
    return NULL;
}

int main( void )
{
    pthread_t id1, id2;

    pthread_mutex_lock( &mainMutex );                           // grab the main mutex

    if ( pthread_create( &id1, NULL, printOdd, NULL ) != 0 )    // create the odd thread
        exit( 1 );
    pthread_cond_wait( &mainCond, &mainMutex ); // wait for the signal from the odd thread

    if ( pthread_create( &id2, NULL, printEven, NULL ) != 0 )   // create the even thread
        exit( 1 );
    pthread_cond_wait( &mainCond, &mainMutex ); // wait for the signal from the even thread

    pthread_mutex_unlock( &mainMutex );     // startup has completed, release the main mutex

    pthread_mutex_lock( &oddMutex );        // signal the odd thread to get things rolling
    pthread_cond_signal( &oddCond );
    pthread_mutex_unlock( &oddMutex );

    pthread_join( id1, NULL );              // wait for the threads to finish
    pthread_join( id2, NULL );

    exit( 0 );
}

