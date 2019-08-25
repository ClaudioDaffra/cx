#ifndef cdFUTURE
#define cdFUTURE

#ifdef __linux__
#define _GNU_SOURCE 
#endif

#include "../lib/pthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

// Geoffroy Couprie  
// https://gist.github.com/Geal
// https://gist.github.com/Geal/8f85e02561d101decf9a

#include <stdbool.h>

typedef struct _future 
{
  pthread_t      thread;
  pthread_attr_t attr;
  void *(*func) (void *); 
} future;

typedef struct _future_arg 
{
  void *(*func) (void *); 
  void * arg;
} future_arg;

typedef struct _promise 
{
  int result;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  bool done;
  int id; 
} promise;

future* future_create(void *(*start_routine) (void *));
void future_start(future* f, void* arg);
void future_stop(future* f); 
void future_close(future* f); 

promise* promise_create();
int promise_get(promise* p); 
void promise_set(promise *p, int res);
bool promise_done(promise* p); 
void promise_close(promise *p);

#endif


/**/


