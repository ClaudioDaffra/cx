
#ifndef cdUtility
#define cdUtility

    #include <stdio.h>
    #include <stdio.h> 
    #include <float.h>
    #include <math.h>

    //
    
    #ifndef CONCATENATE
    #define CONCATENATE(x,y)   x##y
    #endif

    #ifndef TYPEOF
    #define TYPEOF(x,y)    CONCATENATE(x,y)
    #endif

    #ifndef MERGE
    #define MERGE    TYPEOF
    #endif

    // ........................................................... [] make_pair 

    #define pairType(_TYPE1,_TYPE2,ID)                      \
        typedef _TYPE1 pair_##ID##_type1;                   \
        typedef _TYPE2 pair_##ID##_type2;                   \
        typedef struct TYPEOF ( pair_s_ , ID )              \
        {                                                   \
            _TYPE1  first ;                                 \
            _TYPE2  second ;                                \
            size_t  size        ;                           \
        }  TYPEOF ( pair_ , ID ) ;                          \
        TYPEOF ( pair_ , ID ) ID

    // ........................................................... [] pairNew 
     
    #define pairNew(ID,_first,_second)          \
        (ID).first  = _first;                   \
        (ID).second = _second;

    // ........................................................... [] std_swap 
  
    #define std_swap(TYPE,first,second)         \
        do{                                     \
            TYPE temp;                          \
            temp = first;                       \
            first = second;                     \
            second = temp;                      \
        }while(0);   
     

    // ........................................................... [] std_move
       
    #define std_move(dest,source)\
        do{\
            dest=source;\
            source=0;\
        } while(0);
     
    // ........................................................... [] MIN MAX

    #ifndef MIN
    #define MIN(a,b) (((a)<(b))?(a):(b))
    #endif

    #ifndef MAX    
    #define MAX(a,b) (((a)>(b))?(a):(b))
    #endif

    // ........................................................... [] compare float,double,long double
    
    // 
    //  https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
    // 
 
    int float_approximatelyEqual(float a, float b );
    int float_essentiallyEqual(float a, float b );
    int float_definitelyGreaterThan(float a, float b );
    int float_definitelyLessThan(float a, float b );
    int float_equal(float a,float b);
    int float_ge(float a,float b);
    int float_le(float a,float b);

    #define FEQ(a,b)    float_equal(a,b)
    #define FNE(a,b)    (!float_equal(a,b))     
    #define FGT(a,b)    float_definitelyGreaterThan(a,b)
    #define FLT(a,b)    float_definitelyLessThan(a,b)
    #define FGE(a,b)    float_ge(a,b)
    #define FLE(a,b)    float_le(a,b)

    #define r32EQ(a,b)  float_equal(a,b)
    #define r32GT(a,b)  float_definitelyGreaterThan(a,b)
    #define r32LT(a,b)  float_definitelyLessThan(a,b)
    #define r32GE(a,b)  float_ge(a,b)
    #define r32LE(a,b)  float_le(a,b)
    
    int double_approximatelyEqual(double a, double b );
    int double_essentiallyEqual(double a, double b );
    int double_definitelyGreaterThan(double a, double b );
    int double_definitelyLessThan(double a, double b );
    int double_equal(double a,double b);
    int double_ge(double a,double b);
    int double_le(double a,double b);

    #define DEQ(a,b)    double_equal(a,b)
    #define DNE(a,b)    (!double_equal(a,b))     
    #define DGT(a,b)    double_definitelyGreaterThan(a,b)
    #define DLT(a,b)    double_definitelyLessThan(a,b)
    #define DGE(a,b)    double_ge(a,b)
    #define DLE(a,b)    double_le(a,b)

    #define r64EQ(a,b)  double_equal(a,b)
    #define r64GT(a,b)  double_definitelyGreaterThan(a,b)
    #define r64LT(a,b)  double_definitelyLessThan(a,b)
    #define r64GE(a,b)  double_ge(a,b)
    #define r64LE(a,b)  double_le(a,b)
    
    int longdouble_approximatelyEqual(long double a, long double b );
    int longdouble_essentiallyEqual(long double a, long double b );
    int longdouble_definitelyGreaterThan(long double a, long double b );
    int longdouble_definitelyLessThan(long double a, long double b );
    int longdouble_equal(long double a,long double b);
    int longdouble_ge(long double a,long double b);
    int longdouble_le(long double a,long double b);

    #define LDEQ(a,b)    longdouble_equal(a,b)
    #define LDNE(a,b)    (!longdouble_equal(a,b))    
    #define LDGT(a,b)    longdouble_definitelyGreaterThan(a,b)
    #define LDLT(a,b)    longdouble_definitelyLessThan(a,b)
    #define LDGE(a,b)    longdouble_ge(a,b)
    #define LDLE(a,b)    longdouble_le(a,b)

    #define r80EQ(a,b)   longdouble_equal(a,b)
    #define r80GT(a,b)   longdouble_definitelyGreaterThan(a,b)
    #define r80LT(a,b)   longdouble_definitelyLessThan(a,b)
    #define r80GE(a,b)   longdouble_ge(a,b)
    #define r80LE(a,b)   longdouble_le(a,b)

    void cdSwapObjects(void *pa, void *pb, size_t size);
    #define swap(a,b)   cdSwapObjects(&a,&b,sizeof(a))

    /**/
    
#endif



/**/


