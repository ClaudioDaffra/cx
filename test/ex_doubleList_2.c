
#include "../lib/doubleList.h"

/*
    cl  lib\doubleList.c lib\gc.c lib\fs.c test\ex_doubleList_2.c /Fex.exe /EHsc
    gcc lib\doubleList.c lib\gc.c lib\fs.c test\ex_doubleList_2.c -o x.exe
    gcc lib/doubleList.c lib/gc.c lib/fs.c test/ex_doubleList_2.c -o x

*/

int main()
{
    gcStart();

    //

    doubleListType(doubleList);
    
 
    doubleListNew(doubleList,gcCompareInt);
    
    
    int a=1,b=3,c=2;


    doubleListPushBack(doubleList,&a) ;
    doubleListPushBack(doubleList,&b) ;
    doubleListPushBack(doubleList,&c) ;

    doubleListDisplay(doubleList, "(%d)",*(int*) );
    
    doubleListSort(doubleList);

    doubleListDisplay(doubleList, "(%d)",*(int*) );
    
    //

    gcStop();
    printf("\n");
    return 0;
}

/*


*/



