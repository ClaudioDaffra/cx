----------
# c+ 
----------

**c+ alpha version**

simulate standard container of C++ in C.

    gc              ->  Garbage Collector
    stdio           ->  standard stdio ( __mingw_ ... )
    vector          ->  std::vector
    array           ->  std::array
    argParse        ->  parse line argument 
    stack           ->  std::stack  (LIFO)
    queue           ->  std::queue  (FIFO)
    type            ->  typedef format/suffix number/suffix
    string          ->  std::string  = char*
    wstring         ->  std::wstring = wchar_t*  
    tree            ->  std::set        (ordered,unordered)
    :               ->  std::multiset   (ordered,unordered)
    map             ->  std::map        (ordered,unordered)
    :               ->  std::multimap   (ordered,unordered)
    hmap            ->  hash map        (char* / wchar_t*)
    :               ->  dictionary  
    priority_queue  ->  std::priorityQueue
    matrix          ->  matrices
    singleList      ->  std::list_forward
    doubleList      ->  std::list
    deque           ->  std::dequeue
    time            ->  std::chrono ,  date , time , clock.
    bitset          ->  std::bitset
    
    <pthread.h>     ->  VS(Windows) & GCC(Linux) , only.
                        [v] std::thread 
                        [v] std::mutex 
                        [v] std::cond_variabile  
                        [ ] std::atomic ... (sig_atomic_t) 
                        
    future          ->  std::future  std::promise
    timer           ->  setInterval, setTimeout
    <threads.h>     ->  C11
    
    OOP             ->  Try Throw Catch Finally
                    ->  function Overload
                    ->  enum class
                    ->  enumerative exception
                    ->  polymorphism inheritance encapsulation
                    ->  friend function
                    ->  late binding
                    ->  interface
                    ->  property
                    
    exception handler  -> debugWithAdrr2Line
                       -> debugWithStackTrace
                       -> debugPrintStackTrace
                       
    iterator        ->  std::iterator                   
    utility         ->  swap,pair,move
    ratio           ->  std::ratio
    algorithm.      ->  std::algorithm
                        (vector,array,dequeue,valArray)
    mvalarray       ->  std::valarray
    
    console
    
    file system     ->  [v] file    
    : fs.h              [v] dir 
    : fs.c              [v] dirent.h
 

## developer

    vectorType(TYPE,ID) -> define vector    ;   
    vectorNew(ID,N)     -> allocate vector  ;
    
This is the main point of the structure, here the parameters are defined which 
will then be used by the member functions. Note the use of  TYPEOF
this produces a type that will serve to the MACRO, to write the correct code of (data)
in reference to the type. ( __typeof__ GNU GCC , declType (CL) ) :
   
    #define vectorType(TYPE,ID)                         \
    typedef TYPE vectorDataType ## ID;                  \
    typedef struct TYPEOF ( vector_s_ , ID )            \
    {                                                   \
        TYPE*   data ;                                  \
        size_t  size        ;                           \
        size_t  capacity    ;                           \
    }  TYPEOF ( vector_ , ID ) ;                        \
    TYPEOF ( vector_ , ID ) ID

All the library adopts, the garbage collector. Not true, more than anything else it keeps track
of the pointers used, which are deallocated by gcStop (). There are some wrapper functions
in the library, there is no need for the destructor.
    
define typedef data type array :

    typedef TYPE vectorDataType ## ID;      

define struct name  : vector_s(name)

    typedef struct TYPEOF ( vector_s_ , ID )      

define typedef      :   vector_(name)
    
    }  TYPEOF ( vector_ , ID ) ;                    
    TYPEOF ( vector_ , ID ) ID
       
## compatibility

windows 10 

    Microsoft (R) C/C++ Optimizing Compiler versione 19.16.27025.1 per x86
    gcc version 7.3.0 (x86_64-posix-seh-rev0, Built by MinGW-W64 project)
    
Ubuntu

    gcc version 7.4.0 (Ubuntu 7.4.0-1ubuntu1~18.04.1) 

## make

    claudio@ubuntu:~/cx$ gcc lib/string.c lib/gc.c test/ex_string_1.c -o x -Wall -Wextra -pedantic
    claudio@ubuntu:~/cx$ valgrind --leak-check=yes ./x

    ==6603== 
    ==6603== HEAP SUMMARY:
    ==6603==     in use at exit: 0 bytes in 0 blocks
    ==6603==   total heap usage: 25 allocs, 25 frees, 1,793 bytes allocated
    ==6603== 
    ==6603== All heap blocks were freed -- no leaks are possible
    ==6603== 
    ==6603== For counts of detected and suppressed errors, rerun with: -v
    ==6603== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

## benchmark
 
you can look at source code in demo dir :

    Description:	Ubuntu 18.04.1 LTS
    Release:	18.04
    Codename:	bionic

gcc version 7.4.0 (Ubuntu 7.4.0-1ubuntu1~18.04.1)

    gcc lib/gc.c demo/d_vector_1.c -o x     -Wall -Wextra -pedantic -O3
    g++ demo/d_vector_1.cpp -o xpp          -Wall -Wextra -pedantic -O3
   
    052 054 055 std::vector
    022 021 021 mvector
    
**42% faster**

    gcc lib/gc.c demo/d_deque_1.c -o x  -Wall -Wextra -pedantic -O3
    g++ demo/d_deque_1.cpp -o xpp       -Wall -Wextra -pedantic -O3
    
    029 029 029 std::deque
    025 023 024 mdeque
    
**20% faster**

## string, wstring !

They're not exactly like std :: string and std :: wstring instead
they are exactly like: char * and wchar_t *, can be used with functions
of the C library, memory management is automatic . Typdef def for sttring is :

    string_t ;
    wstring_t ;

## stringFromNumber 

Here the problem is threefold:

1) visual studio manages long double like double ;
2) to compensate for this MINGW32 wrote its own routines ;
3) snwprintf / snprintf, swprintf / snprintf non-standard implementation ;

## iterator

These are the management commands of the iterator.

    itVector            algorithm
    itString
    itWstring
    itArray             algorithm
    itTree
    itMap
    itHmap
    itWHmap
    itSingleList
    itDoubleList
    itDeque             algorithm
    itValArray          algorithm
    
## vector of vector / array of void* ...

you can define a normal vector with macro C in this way : ( test/ex_vector_1.c )

    vectorType(int,v1) ;
    
this istruction define a typdef vector_v1 ;

    vectorType(vector_v1,v2);
    
every vector need to be allocated and push as a variabile, macro C implement an easy acce sto 
element of vector of vector, instruction below :

    vectorNew( v2 , 64 );  
    vectorPushBack( v2 ,v1 ) ;    
    vectorXY(v2,0,0) ;
 
so with this second instruction, we can use a vector of vector

    vectorType(int,v3)[10];  
    
you can define, also an array of vector;

another improvement is relative to array ( test/ex_array_1.c )

    typedef void* pvoid ;

    arrayType( pvoid ,av )[2];

    arrayNew( av[0] , 2 ) ;
    arrayNew( av[1] , 2 ) ;

    arrayData(av[0])[0] = &a1 ; // --> arrayType(double,a1);
    arrayData(av[0])[1] = &a2 ; // --> arrayType(double,a2);

    printf ( "\n # a1/%d ",  (int)arrayPointerVoidAt(av,0,0).size     ) ;
    printf ( "\n # a2/%d ",  (int)arrayPointerVoidAt(av,0,1).size     ) ;

    
## garbage collector

The use is quite simple, the 'garbage collector' starts with gcStart () and ends with gcStop (); 
The most common functions used are gcMalloc (), gcFree () and gcRealloc (). There are also wrapper functions.
Essentially it does not manage memory through its own manager, but keeps track of allocated and deallocated pointers. 
If free () is omitted the gcStop () handler will perform automatic deallocation.

## thread

this library is based on [winpthreads.h](https://locklessinc.com/articles/pthreads_on_windows/), work
with : Visual Studio & gcc (linux) not with gcc(windows) because not all function is implementated about 
windows thread.
yet included <threads.h> C11 [c11threads](https://github.com/jtsiomb/c11threads)

## debug

the exception handler, initializes the signal handler to make them point to our routine
in order to catch the error and tell us where it is. The two management systems differ for :

1) debugWithAdrr2Line   : use Addr2Line (separate program) to keep track of functions.
2) debugWithStackTrace  : uses a manual manager to keep track on the stack.
3) debugPrintStackTrace : show stack frame directly without external manager.

## Object Oriented Programming

this is an attempt to simulate some C++ features. Here you can see implemented features,
work with two addictional indirection easy way (not vtable), as shown  in ex_oop_5.c :

    Try Throw Catch Finally
    function Overload
    enum class
    enumerative exception
    polymorphism inheritance encapsulation
    friend function
    late binding
    interface
    property
  
## file temporary

Temporary files are created with the fileTemp function,
this takes care of creating a folder of temporary files and 
managing the allocation with the respective names.
At the end of the program the garbage collector 
will take care of deleting all the temporary files created


# The End.


