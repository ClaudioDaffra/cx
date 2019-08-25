
#include "../lib/oop.h"

/*

    cl test\ex_oop_2.c /Fex.exe
    gcc test\ex_oop_2.c -o x.exe

*/


#define FOO0()          printf ( "\n0:[]"                           );
#define FOO1(x)         printf ( "\n1:[%d]"             ,x          );
#define FOO2(x,y)       printf ( "\n2:[%d,%d]"          ,x,y        );
#define FOO3(x,y,z)     printf ( "\n3:[%d,%d,%d]"       ,x,y,z      );
#define FOO4(x,y,z,w)   printf ( "\n4:[%d,%d,%d,%d]"    ,x,y,z,w    );

#define FOO(...)  OVERLOAD ( FOO  , ARG(__VA_ARGS__) ) ( __VA_ARGS__ )


#include <stdio.h>


int main(void)
{

    FOO();
    FOO(1);
    
    
    return 0 ;
}