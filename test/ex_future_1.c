
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lib/future.h"

/*

    cl          lib\future.c test\ex_future_1.c  /Fex.exe /EHsc /WX
    __MINGW32__ NO
    gcc
*/


void* func(void * arg) 
{
  promise* p = (promise*) arg;
  
  printf("\tstarted thread\n");
  
  sleep(3);
  
  printf("\tthread will set promise\n");
  
  promise_set(p, 42);
  
  printf("\tstopping thread\n");
  
  return NULL;
}

int main(void) 
{
  long t;
  
  printf("main thread\n");
  
  future* f = future_create(func);
  
  promise* p = promise_create();
  
  future_start(f, p); 

  printf("got result from future: %d\n", promise_get(p));
  
  future_close(f);
  
  promise_close(p);

  pthread_exit(NULL);
  
  return EXIT_SUCCESS ;
}