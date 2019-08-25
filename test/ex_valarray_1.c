#include "../lib/mvalarray.h"

/*
    cl  test\ex_valarray_1.c lib\gc.c lib\fs.c /Fex.exe
    gcc test\ex_valarray_1.c lib\gc.c lib\fs.c -o x.exe
    gcc test/ex_valarray_1.c lib/gc.c lib/fs.c -o x     -lm    
*/

int main(void)
{
    gcStart() ;
    
    /**/
    valArrayType( int , va );
    valArrayNew(va,16);
    
    int val=0;
    
    // ................................................................. for each
    
    puts("\nfor each");
    
    valArrayForEach(va,val++);
    
    puts("");for(int it=0;it<va.size;it++) printf ( "(%d)",va.data[it] );

    puts("\nvalArrayIndex");

    // ................................................................. for each index
    
    valArrayIndex(va,(index%2)==0,100);

    puts("\nvalArrayIterator");

    // ................................................................. for each *it
    
    valArrayIterator(va,(*it%2)==1,-1);

    puts("");for(int it=0;it<va.size;it++) printf ( "(%d)",va.data[it] );

    // ................................................................. resize
    
    valArrayResize(va,20,99);

    puts("");for(int it=0;it<va.size;it++) printf ( "(%d)",va.data[it] );    

    puts("\nunary val");

    // ................................................................. operator unary
    
    valArrayUnaryOp(-,va);

    puts("");for(int it=0;it<va.size;it++) printf ( "(%d)",va.data[it] );  

    puts("\nresize");
    
    valArrayResize(va,5,0) ;
    valArrayType( int , va2 );
    valArrayNew(va2,5);    
    valArrayIndex(va,1,index);
    valArrayIndex(va2,1,index*10);  
    
    puts("");for(int it=0;it<va.size;it++) printf ( "(%d)",va.data[it] );  
    puts("");for(int it=0;it<va2.size;it++) printf ( "(%d)",va2.data[it] );  

    // ................................................................. binary  array
    
    puts("\nBinaryArray");
    
    valArrayBinOpArray(va2,-,va);
    puts("");for(int it=0;it<va2.size;it++) printf ( "(%d)",va2.data[it] );      

    // ................................................................. binary  val
    
    puts("\nBinaryVal");
    
    valArrayBinOpVal(va2,-,6);
    puts("");for(int it=0;it<va2.size;it++) printf ( "(%d)",va2.data[it] );      

    // ................................................................. swap
    
    puts("\nSWAP");
    
    puts("");for(int it=0;it<va.size;it++) printf ( "(%d)",va.data[it] );      
    puts("");for(int it=0;it<va2.size;it++) printf ( "(%d)",va2.data[it] );      
    valArraySwap(va,va2);
    puts("");for(int it=0;it<va.size;it++) printf ( "(%d)",va.data[it] );      
    puts("");for(int it=0;it<va2.size;it++) printf ( "(%d)",va2.data[it] );         

    // ................................................................. sum
    // ................................................................. min
    // ................................................................. max
    
    puts("\nSWAP");
    int sum,min,max;
    
    valArraySum(va2,sum);
    valArrayMin(va2,min);
    valArrayMax(va2,max);
         
    printf( "\n sum %d min %d max %d.",sum,min,max );
    
    // ................................................................. copy =

    valArrayType( float , va3 );
    valArrayNew(va3,5);  
    
    valArrayBinOpArray( va3, = ,va2 );
    puts("\n va3 :: ");for(int it=0;it<va3.size;it++) printf ( "(%f)",va3.data[it] );  
 
    // ................................................................. apply

    valArrayApply( va3, sin(*it) );
    puts("\n va3 :: ");for(int it=0;it<va3.size;it++) printf ( "(%f)",va3.data[it] ); 

    // ................................................................. left shift <<

    valArrayLeftShift( va3, 2, 0.0 );
    puts("\n va3 left :: ");for(int it=0;it<va3.size;it++) printf ( "(%f)",va3.data[it] ); 

    // ................................................................. right shift >>
 
    valArrayRightShift( va3, 2, 0.0 );
    puts("\n va3 right :: ");for(int it=0;it<va3.size;it++) printf ( "(%f)",va3.data[it] ); 

    // ................................................................. Circular Left shift <<
 
    valArrayCLeftShift( va3, 2 );
    puts("\n va3 C Left :: ");for(int it=0;it<va3.size;it++) printf ( "(%f)",va3.data[it] ); 
  
    // ................................................................. Circular Right shift >>
 
    valArrayCRightShift( va3, 2 );
    puts("\n va3 C Right :: ");for(int it=0;it<va3.size;it++) printf ( "(%f)",va3.data[it] ); 
  

    // ................................................................. slice

    sliceType(s1,2,2,2,2);

    valArrayResize(va,27,0) ;    
    val=0;
    valArrayForEach(va,val++);
    puts("\nva2 :: \n");for(int it=0;it<va.size;it++) printf ( "(%d)",va.data[it] );    
    

    
    puts("\n slice va ::");
    for (int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++)  
                for(int w=0;w<2;w++)                  
                {
                    printf ( "(%d)",valArrayAt( va,sliceXYZW(s1,i,j,k,w) ) );
                }

    puts("\n gslice va ::");
    for (int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            for(int k=0;k<2;k++)  
                for(int w=0;w<2;w++)                  
                {
                    printf ( "(%d)", gsliceXYZW( va,s1,valArrayBegin(va)+2,i,j,k,w)  );
                }
                
            
    /**/
    
    

    valArrayFree(va );
    valArrayFree(va2);
    valArrayFree(va3);    

    gcStop();
    
    return 0 ;
}
