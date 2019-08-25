
#include "../lib/ratio.h"
#include "../lib/type.h"
#include <stdio.h>

/*

    cl  test\ex_ratio_1.c   lib\ratio.c     lib\mutility.c  /Fex.exe
    gcc test\ex_ratio_1.c   lib\ratio.c     lib\mutility.c  -o x.exe
    gcc test/ex_ratio_1.c   lib/ratio.c     lib/mutility.c  -o x
    
*/


int main(void)
{
    ratio_t a = { 1,2 } ;
    ratio_t b = { 1,3 } ;
    
    printf ( "\n   equal %d",ratioEQ(a,b) ) ;
    printf ( "\n ! equal %d",ratioNE(a,b) ) ;
    printf ( "\n <       %d",ratioLT(a,b) ) ;
        
    printf ( "\n ratio   %g",ratio(a) ) ;

    ratio_t result;
 
    ratioAdd(&result,a,b) ;
    printf ( "\n add "$i80()"/"$i80()".",result.num,result.den );
   
    ratioSub(&result,a,b) ;    
    printf ( "\n sub "$i80()"/"$i80()".",result.num,result.den );
    
    ratioMul(&result,a,b);
    printf ( "\n mul "$i80()"/"$i80()".",result.num,result.den );
    
    ratioDiv(&result,a,b);
    printf ( "\n Div "$i80()"/"$i80()".",result.num,result.den );
    
    printf ( "\n EXA : %e \n",ratio(exa) );
    
    return 0;
}

