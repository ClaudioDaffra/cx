
/* compile with:

    on linux:  
    
        gcc lib/gc.c debug/ex_debug_1.c  -o x -g             -Wall -Wextra -pedantic
                
    on OS X:  
    
        gcc lib/gc.c debug/ex_debug_1.c  -o x -g -fno-pie    -Wall -Wextra -pedantic

    on windows: 

        gcc    lib\gc.c debug\ex_debug_1.c -o x.exe  -g    -limagehlp           -Wall -Wextra -pedantic
        cl     lib\gc.c debug\ex_debug_1.c /Fex.exe  /Z7   /link dbghelp.lib    
               
*/

#include "debugWithStackTrace.h"

int  divide_by_zero();
void cause_segfault();
void stack_overflow();
void infinite_loop();
void illegal_instruction();
void cause_calamity();

//***** 
// MAIN
//***** 

int main(int argc, char * argv[])
{
    gcStart();
    stStart();
    
    stPushFunction();

    //

    (void)argc;

    // store off program path so we can use it later 
    
    global_program_name = argv[0];

    set_signal_handler();

    cause_calamity();

    puts("OMG! Nothing bad happend!");

    //

    stStop();
    gcStop();

 return EXIT_SUCCESS;
}

//********* 
// calamity
//********* 

void cause_calamity()
{
    stPushFunction(); 
        
    /* uncomment one of the following error conditions 
    to cause a calamity of your choosing! */

    (void)divide_by_zero();
    // cause_segfault();
    // assert(false);
    // infinite_loop();
    // illegal_instruction();
    // stack_overflow();
}

int divide_by_zero()
{
    stPushFunction(); 

    int a = 1;
    int b = 0; 
    return a / b;
}

void cause_segfault()
{
    stPushFunction(); 
        
    int * p = (int*)0x12345678;
    *p = 0;
}

void stack_overflow();
void stack_overflow()
{
    stPushFunction();
    
    int foo[1000];
    (void)foo;
    stack_overflow();
}

/* break out with ctrl+c to test SIGINT handling */
void infinite_loop()
{
    stPushFunction();

    while(1) {};
}

void illegal_instruction()
{
    stPushFunction();
    
    /* I couldn't find an easy way to cause this one, so I'm cheating */
    raise(SIGILL);
}



/**/


