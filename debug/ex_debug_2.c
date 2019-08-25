
/* compile with:

    on linux:   
    
        gcc  debug/ex_debug_2.c  -g -o x    -Wall -Wextra -pedantic
                
    on OS X:   
    
        gcc  debug/ex_debug_2.c  -g -o x  -fno-pie    -Wall -Wextra -pedantic

    on windows: 

        gcc     debug\ex_debug_2.c -o x.exe  -g    -limagehlp           -Wall -Wextra -pedantic
        cl      debug\ex_debug_2.c /Fex.exe  /Z7   /link dbghelp.lib    
               
*/

#include "debugWithAddr2Line.h"

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
    (void)argc;

    // store off program path so we can use it later 
    
    global_program_name = argv[0];

    set_signal_handler();

    cause_calamity();

    puts("OMG! Nothing bad happend!");

    //

    return EXIT_SUCCESS;
}

//********* 
// calamity
//********* 

void cause_calamity()
{
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
    int a = 1;
    int b = 0; 
    return a / b;
}

void cause_segfault()
{
    int * p = (int*)0x12345678;
    *p = 0;
}

void stack_overflow();
void stack_overflow()
{
    int foo[1000];
    (void)foo;
    stack_overflow();
}

/* break out with ctrl+c to test SIGINT handling */
void infinite_loop()
{
    while(1) {};
}

void illegal_instruction()
{
    /* I couldn't find an easy way to cause this one, so I'm cheating */
    raise(SIGILL);
}


/**/
