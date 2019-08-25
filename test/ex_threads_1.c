#include "../lib/threads.h"
#include <stdio.h>

/*
    
    cl  test/ex_threads_1.c     /EHsc       /Fex.exe
    gcc test/ex_threads_1.c     -lpthread    -o x.exe

*/


int run(void *arg)
{
    printf("Hello world of C11 threads.");

    return 0;
}

int main(int argc, const char *argv[])
{
    thrd_t thread;
    int result;

    thrd_create(&thread, run, NULL);

    thrd_join( thread, &result);

    printf("Thread return %d at the end\n", result);
    
    return 0 ;
}