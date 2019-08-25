
#include "../lib/doubleList.h"

/*
    cl  lib\doubleList.c lib\gc.c  lib/fs.c test\ex_doubleList_1.c /Fex.exe /EHsc
    gcc lib\doubleList.c lib\gc.c  lib/fs.c test\ex_doubleList_1.c -o x.exe
    gcc lib/doubleList.c lib/gc.c  lib/fs.c test/ex_doubleList_1.c -o x
*/

int main()
{
    gcStart();

    //

    doubleListType(doubleList);
 
    //  ................................................. empty
    printf ("\n ... empty ");   
      
    printf ( "\n ? %d\n", doubleListEmpty(doubleList) );
    
    doubleListNew(doubleList,gcCompareStrC);
 
    //  ................................................. push back

    printf ("\n ... pushBack ");  
    
    doubleListPushBack(doubleList, gcStrDup ("a") );
    doubleListPushBack(doubleList, gcStrDup ("e") );
    doubleListPushBack(doubleList, gcStrDup ("f") );

    doubleListDisplay(doubleList, "(%s)",(char*) );

    printf ( "\nsize::[%d]\n",(int)doubleListSize(doubleList) );
 
    //  ................................................. push front

    printf ("\n ... pushFront ");
    
    doubleListPushFront(doubleList, gcStrDup ("b") );
    doubleListPushFront(doubleList, gcStrDup ("c") );
  
    doubleListDisplay(doubleList, "(%s)",(char*) );  

    //  ................................................. insert 

    printf ("\n ... InsertAfter ");  
    
    doubleListInsertAfter (doubleList, gcStrDup ("e"), gcStrDup ("e_") ); 
    
    printf ("\n ... InsertBefore ");  
    
    doubleListInsertBefore(doubleList, gcStrDup ("e"), gcStrDup ("_e") );
    
    doubleListDisplay(doubleList, "(%s)",(char*) ); 

    //  ................................................. remove 

    printf ("\n ... remove ");  
    
    doubleListRemove(doubleList, gcStrDup("b") );
    
    doubleListDisplay(doubleList, "(%s)",(char*) ); 

    //  ................................................. remove after

    printf ("\n ... remove after ");
    
    doubleListRemoveAfter(doubleList, gcStrDup("e") );

    //  ................................................. remove before

    printf ("\n ... remove before ");  
    
    doubleList = doubleListRemoveBefore(doubleList, gcStrDup("e") );
    
    doubleListDisplay(doubleList, "(%s)",(char*) ); 

    //  ................................................. reverse

    printf ("\n ... reverse ");    
    
    doubleListReverse(doubleList);
    
    doubleListDisplay(doubleList, "(%s)",(char*) ); 
    
    //  ................................................. front back
    
    
    printf ("\n ... front back ");  
    
    printf ( "\nfront %s",(char*) (doubleListFront(doubleList))->data );
    printf ( "\nback  %s",(char*) (doubleListBack (doubleList))->data );
    printf ( "\nempty %d", doubleListEmpty(doubleList) );
 
    //  ................................................. iterator
   
    itDoubleList(it);
    
    printf ("\n ... iterator ");
    for ( it=doubleListBegin(doubleList) ; it != doubleListEnd(); it = doubleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    }
    printf ("\n ... iterator reverse");    
    for ( it=doubleListRBegin(doubleList) ; it != doubleListEnd(); it = doubleListRNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    }

    //  ................................................. sort
 
    printf ("\n ... sort "); ;  
    
    doubleListSort(doubleList);
    
    printf ( ""); ;    
    for ( doubleList_t it=doubleListBegin(doubleList) ; it != doubleListEnd(); it = doubleListNext(it)  )
    {
        printf ( " {%s}",(char*)it->data) ;
    }  

    //  ................................................. front back

    printf ("\n ... pop Front Back");  
    
    doubleListPopFront(doubleList);

    doubleListPopBack(doubleList);
    
    printf ("\n ... front back "); ; 
    
    for ( doubleList_t it=doubleListBegin(doubleList) ; it != doubleListEnd(); it = doubleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    }    
 
    //  ................................................. doubleList splice

    printf ("\n ... splice "); ;
    
    doubleList_t splice = NULL ;
    
    doubleListPushBack(doubleList , gcStrDup("1") ) ;
    doubleListPushBack(doubleList , gcStrDup("2") ) ;

    printf ("\n ... SPLICE before : doubleList .") ;
    for ( doubleList_t it=doubleListBegin(doubleList) ; it != doubleListEnd(); it = doubleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    } 
    
    splice = doubleListSplice ( doubleList,1,2 ); 
    
    printf ("\n ... SPLICE after  : splice     .") ;
    for ( doubleList_t it=doubleListBegin(splice) ; it != doubleListEnd(); it = doubleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    } 

    //  ................................................. doubleList copy

    printf ("\n ... copy ");  
    
    doubleList_t copy = NULL ;
    
    copy = doubleListCopy ( doubleList ); 
    
    for ( doubleList_t it=doubleListBegin(copy) ; it != doubleListEnd(); it = doubleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    } 

    //  ................................................. doubleList append
    printf ("\n ... append ");  

    doubleListAppend(copy,doubleList );
    
    for ( doubleList_t it=doubleListBegin(copy) ; it != doubleListEnd(); it = doubleListNext(it)  )
    {
        printf ( "{%s}",(char*)it->data) ;
    }        

    //  ................................................. find
    printf ("\n ... find "); 

    printf ("\n ... e  ? [%p]. ",doubleListFind(copy,gcStrDup("e") ) ); 
    
    //  ................................................. free
   
    doubleListFree(doubleList);

    //

    gcStop();
    printf("");
    return 0;
}



/**/

