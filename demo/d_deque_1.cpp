
/*

    g++ demo\d_deque_1.cpp -o xpp.exe      -Wall -Wextra -pedantic -O3
    g++ demo/d_deque_1.cpp -o xpp          -Wall -Wextra -pedantic -O3

*/

#include <deque>
#include <stdio.h>

/*
    029 029 029 std::deque
    025 023 024 mdeque
    20% faster
*/

int main ( void )
{
    std::deque<int> v ;
    

    int ITERATION_MAX       = 10 * 1000 * 1000;
    int countErase          = 0 ;

    int i ;
    for (  i=0; i<ITERATION_MAX; i++ )
    {

        v.push_back(i);
 
        if ( ++countErase>10 )  v.push_front (i);
 
        if ( ++countErase>20 )  v.insert(v.begin()+0,i);

        if ( ++countErase>30 )  v.pop_back();

        if ( ++countErase>40 )  v.pop_front();

        if ( ITERATION_MAX > 50 )   countErase = 0 ; 
 
    }

     printf ( "\n %d ",i ) ;   
    return 0 ;
}
