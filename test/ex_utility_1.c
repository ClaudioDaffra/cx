
#include "../lib/mutility.h"

/*

    cl  test\ex_utility_1.c lib\mutility.c /Fex.exe 
    gcc test\ex_utility_1.c lib\mutility.c -o x.exe
    gcc test/ex_utility_1.c lib/mutility.c -o x 
    
*/

int main ( void )
{
    // ............................................... pair
        
    pairType(int,float,p);
    
    pairNew(p,1,2.3);  

    printf ( "%d %f",p.first,p.second );
    
    // ............................................... swap
    
    float x = 12.3 ;
    float y = 45.6 ;

    std_swap(float,x,y);
    
    printf ("\n%f %f",x,y);

        
    // ............................................... move
    
    float* p1 = &x;
    float* p2 ;
    
    std_move( p2,p1 ) ;

    printf ( "\n[%g]",*p2 );    

    std_move( x,y ) ;
    printf ( "\n[%g]",x );      

    // ............................................... compare float double long double
    printf ("\n\n");
    
    puts("# float");
    float  x1 = 0.1f; 
    if (  FEQ(x1,0.1)  ) puts(".uguale");       //r32EQ
    if (  FLT(0.0,0.1) ) puts(".minore");  
    if (  FGT(0.1,0.0) ) puts(".maggiore"); 
    puts("");

    puts("# double");    
    double x2 = 0.001; 

    if (  DEQ(x2,0.001)    ) puts(".uguale");  // r64EQ
    if (  DLT(0.000,0.001) ) puts(".minore");  
    if (  DGT(0.001,0.000) ) puts(".maggiore"); 
    puts("");

    puts("# long double");    
    long double x3 = 0.0000001L;  

    if (  LDEQ(x3,0.0000001L)   ) puts(".uguale");  // r80EQ
    if (  LDLT(0.00000,0.00001) ) puts(".minore");  
    if (  LDGT(0.00001,0.00000) ) puts(".maggiore");
    puts("");

    /* SWAP */

    int a1=12;
    int b1=34;
    printf ( "\n %d %d",a1,b1 ) ;
    swap(a1,b1);
    printf ( "\n %d %d",a1,b1 ) ;

    double a2=12.1;
    double b2=34.5;
    printf ( "\n %f %f",a2,b2 ) ;
    swap(a2,b2);   
    printf ( "\n %f %f",a2,b2 ) ;


    char* a3="claudio";
    char* b3="daffra";
    printf ( "\n %s %s",a3,b3 ) ;
    swap(a3,b3);     
    printf ( "\n %s %s",a3,b3 ) ;

    /* END SWAP */

    printf ( "\n min %f",MIN(a2,b2) );
    printf ( "\n max %f",MAX(a2,b2) );    
    
  printf ( "\n" );
  return 0 ;
}


/**/


