
#include "../lib/gc.h"
#include "../lib/mdeque.h" 

/*

   cl        lib\gc.c  lib\fs.c test\ex_deque_1.c /Fex.exe /WX /EHsc
   gcc       lib\gc.c  lib\fs.c test\ex_deque_1.c -o x.exe -Wall -Wextra -pedantic
   gcc       lib/gc.c  lib/fs.c test/ex_deque_1.c -o x     -Wall -Wextra -pedantic
   
*/ 
int main ( void )
{
    gcStart();
    
    // ..................................................... deque type
    dequeType(int,d) ;
    
    // ..................................................... deque new
    dequeNew(d,2);
  
    // ..................................................... deque push , size , capacity , empty
    printf ( "\n ... pushBack" ) ;
    
    printf ( "\n size %d capacity %d empty %d.",(int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d) ) ;
    dequePushBack(d,123);
    printf ( "\n size %d capacity %d empty %d.",(int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d) ) ;
    dequePushBack(d,456);
    printf ( "\n size %d capacity %d empty %d.",(int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d) ) ;
    dequePushBack(d,789);
    printf ( "\n size %d capacity %d empty %d.",(int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d) ) ; 
 
/*        
    printf ( "\n ### DEBUG :: " ) ;
    for(int i=0;      i<=(int)dequeCapacity(d);i++) printf  ("[%d/%d]",i,d.data[i]) ;
*/    
    printf ( "\n" ) ;
    for(int i=(int)d.start;i<(int)d.stop             ;i++) printf  ("[%d/%d]",i-(int)d.start,d.data[i]) ;

    // ..................................................... deque pop back

    printf ( "\n ... popBack" ) ;
    
    dequePopBack(d);   
    printf ( "\n" ) ;
    for(int i=(int)d.start;i<(int)d.stop             ;i++) printf  ("[%d/%d]",i,d.data[i]) ;


    printf ( "\n size %d capacity %d empty %d start %d stop %d",
        (int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d),(int)d.start,(int)d.stop ) ;

    // ..................................................... deque push front

    printf ( "\n ... pushFront" ) ;
    
    dequePushFront(d,12);
    
    printf ( "\n size %d capacity %d empty %d start %d stop %d",
        (int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d),(int)d.start,(int)d.stop ) ;

/*
    printf ( "\n ### DEBUG :: " ) ;
    for(int i=0;      i<=(int)dequeCapacity(d);i++) printf  ("[%d/%d]",i,d.data[i]) ;
*/
    printf ( "\n" ) ;
    for(int i=(int)d.start;i<(int)d.stop             ;i++) printf  ("[%d/%d]",i,d.data[i]) ;


    dequePushFront(d,34);
    
    printf ( "\n size %d capacity %d empty %d start %d stop %d",
        (int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d),(int)d.start,(int)d.stop ) ;
        
    dequePushFront(d,56);
    
    printf ( "\n size %d capacity %d empty %d start %d stop %d",
        (int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d),(int)d.start,(int)d.stop ) ;

    dequePushFront(d,78);
    
    printf ( "\n size %d capacity %d empty %d start %d stop %d",
        (int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d),(int)d.start,(int)d.stop ) ;

    dequePushFront(d,90);
    dequePushFront(d,91);
    dequePushFront(d,92);
    
    printf ( "\n size %d capacity %d empty %d start %d stop %d",
        (int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d),(int)d.start,(int)d.stop ) ;

/*        
    printf ( "\n ### DEBUG :: " ) ;
    for(int i=0;      i<=(int)dequeCapacity(d);i++) printf  ("[%d/%d]",i,d.data[i]) ;
*/
    printf ( "\n" ) ;
    for(int i=(int)d.start;i<(int)d.stop             ;i++) printf  ("[%d/%d]",i-(int)d.start,d.data[i]) ;

    // ..................................................... deque erase at
    printf ( "\n ... eraseAt" ) ;
    
    dequeEraseAt(d,2) ; // 90
    
/*
    printf ( "\n ### DEBUG :: " ) ;
    for(int i=0;      i<=(int)dequeCapacity(d);i++) printf  ("[%d/%d]",i,d.data[i]) ;
*/
    printf ( "\n" ) ;
    for(int i=(int)d.start;i<(int)d.stop             ;i++) printf  ("[%d/%d]",i-(int)d.start,d.data[i]) ;

    // ..................................................... deque erase N
    
    dequeEraseAtN(d,2,2) ; // 78 56
    
/*
    printf ( "\n ### DEBUG :: " ) ;
    for(int i=0;      i<=(int)dequeCapacity(d);i++) printf  ("[%d/%d]",i,d.data[i]) ;
*/
    printf ( "\n" ) ;
    for(int i=(int)d.start;i<(int)d.stop             ;i++) printf  ("[%d/%d]",i-(int)d.start,d.data[i]) ;

    // ..................................................... iterator

    printf ( "\n ... iterator" ) ;
    
    itDeque(d) it ;

    printf ( "\n" ) ;
    for(it=dequeBegin(d);it<dequeEnd(d);it++ ) printf  ("{%d}",*it) ;    
    printf ( "\n" ) ;
    for(it=dequeRBegin(d);it>dequeREnd(d);it-- ) printf  ("{%d}",*it) ; 

    // ..................................................... at
    printf ( "\n" ) ;
    for(int i=0;i<(int)dequeSize(d) ;i++) printf  ("[%d/%d]",i,dequeAt(d,i) ) ;

    // ..................................................... front back  
    printf ( "\n front %d , back %d. , middle %d ",dequeFront(d), dequeBack(d),dequeMiddle(d) );


    // ..................................................... sort

    printf ( "\n ... sort" ) ;
    
    dequeSort(d,gcCompareInt);
    
    printf ( "\n" ) ;
    for(int i=0;i<(int)dequeSize(d) ;i++) printf  ("[%d/%d]",i,dequeAt(d,i) ) ;

    // ..................................................... insert

    printf ( "\n ... insert" ) ;
    
    dequeInsertAtVal(d,2,100);
    
    printf ( "\n" ) ;
    for(int i=0;i<(int)dequeSize(d) ;i++) printf  ("[%d/%d]",i,dequeAt(d,i) ) ;
    printf ( "\n size %d capacity %d empty %d start %d stop %d",
        (int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d),(int)d.start,(int)d.stop ) ;    
    
    // ..................................................... clear 
    
    printf ( "\n ... clear" ) ;
    
    dequeClear(d);

    printf ( "\n" ) ;
    for(int i=0;i<(int)dequeSize(d) ;i++) printf  ("[%d/%d]",i,dequeAt(d,i) ) ;  
    printf ( "\n size %d capacity %d empty %d start %d stop %d",
        (int)dequeSize(d),(int)dequeCapacity(d),dequeEmpty(d),(int)d.start,(int)d.stop ) ;
        
    /**/
 
    dequeFree(d);
    
    /**/
    
    gcStop();
    
 printf ("\n");
 return 0 ;
}
