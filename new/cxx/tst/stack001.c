
#include "../src/cxx.h"

/*
    1)  clear   ; gcc src/gc.c tst/stack001.c   -o   bin/x      -Wall -Wextra -pedantic 

    2)  cls     & cl src\gc.c tst\stack001.c    /Febin\x.exe    /WX /utf-8
*/

int main ( void )
{
    gcStart() ;

    // .................................... stack typedef 
 
    printf ( "--- stackType(int,s1); \n" );

    // stack_ID_d            :    TYPE
    // stack_ID_s            :    struct stack_ID_s
    // stack_ID_t            :    stack_ID_s
    // stack_ID_p            :    stack_ID_t*
     
    stackTypeDef(int,s1);
    
    printf ( "stack : data size %zu , struct size %zu , struct size %zu,  struct * size %zu\n"
        ,sizeof(stack_s1_d),sizeof(struct stack_s1_s),sizeof(stack_s1_t),sizeof(stack_s1_p) );

    // .................................... stack new
    
    stack_s1_t    s1 ;
    
    stackAlloc(s1,8) ;
 
    // .................................... stack push 
    
    printf ( "--- stackPush ( s1 , 1,2,3 ) ; \n" );
    
    stackPush( s1 ,1 ) ;
    stackPush( s1 ,2 ) ;
    stackPush( s1 ,3 ) ;

    // .................................... stack top 
    
    printf ( "--- stackTop( s1 ) ; \n" );

    printf ("%d\n",stackTop(s1));

    // .................................... stack pop
    
    printf ( "--- stackPop( s1 ) ; \n" );

    stackPop(s1);
    
    printf ("%d\n",stackTop(s1));
    
    // .................................... dealloc
    
    printf ( "--- dealloc s1\n" ) ; 
       
    stackDealloc(s1);    
    
    // ...................................... stop
    
    gcStop() ;

    printf ("\n");
    
    return 0 ;
}
