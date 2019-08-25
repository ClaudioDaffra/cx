
#include "../lib/bitset.h" 
#include <stdio.h>

/*
    cl  test\ex_bitset_2.c /Fex.exe /WX
    gcc test\ex_bitset_2.c -o x.exe -Wall -Wextra -pedantic
    gcc test/ex_bitset_2.c -o x     -Wall -Wextra -pedantic
*/


// cl  4 8 8
// gcc 4 8 16

int main()
{
    // ............................................................. sizeof
    
    printf ( "\n typeof %d %d %d",(int)sizeof(float),(int)sizeof(double),(int)sizeof(long double) ) ;  
    
    // ............................................................. float    
    
    real32_t x  ; 
    x.real = -1.2f ;  

    printf ( "\n" );
    printf ( "\n negative   : %d ", real32s(x) ); 
    printf ( "\n exponent   : %x ", real32e(x) ); 
    printf ( "\n mantissa0  : %x ", real32m(x) ); 

    // ............................................................. double
        
    printf ( "\n" );
    
    real64_t y  ;

    y.real = -1.2L ;  

    printf ( "\n negative   : %d ", real64s(y)  );
    printf ( "\n exponent   : %x ", real64e(y)  );  
    printf ( "\n mantissa0  : %x ", real64m0(y) );   
    printf ( "\n mantissa1  : %x ", real64m1(y) );   

    // ............................................................. long double
    
    printf ( "\n" );
    
    real80_t z;

    z.real = -1.2L ;  

    printf ( "\n negative   : %d ", real80s(z)  );
    printf ( "\n exponent   : %x ", real80e(z)  );  
    printf ( "\n mantissa0  : %x ", real80m0(z) );   
    printf ( "\n mantissa1  : %x ", real80m1(z) );  

}

