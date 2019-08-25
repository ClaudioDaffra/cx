#ifndef cdType
#define cdType

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h> 
#include <stddef.h>
#include <stdint.h>
#include <wchar.h>
#include <inttypes.h>

//  signed      / integer
//  unsigned 

typedef     unsigned char       u8_t ;
typedef     unsigned char*      pu8_t ;
#define u8MIN   0
#define u8MAX   UCHAR_MAX
typedef     signed char         i8_t ;
typedef     signed char*        pi8_t ;
#define i8MIN   SCHAR_MIN
#define i8MAX   SCHAR_MAX
typedef     signed char         s8_t ;
typedef     signed char*        ps8_t ;
#define s8MIN   SCHAR_MIN
#define s8MAX   SCHAR_MAX

typedef     uint16_t            u16_t ;
typedef     uint16_t*           pu16_t ;
#define u16MIN   0
#define u16MAX   USHRT_MAX
typedef     int16_t             i16_t ;
typedef     int16_t*            pi16_t ;
#define i16MIN   SHRT_MIN
#define i16MAX   SHRT_MAX
typedef     int16_t             s16_t ;
typedef     int16_t*            ps16_t ;
#define s16MIN   SHRT_MIN
#define s16MAX   SHRT_MAX

typedef     uint32_t            u32_t ;
typedef     uint32_t*           pu32_t ;
#define u32MIN   0
#define u32MAX   UINT_MAX
typedef     int32_t             i32_t ;
typedef     int32_t*            pi32_t ;
#define i32MIN   INT_MIN
#define i32MAX   INT_MAX
typedef     int32_t             s32_t ;
typedef     int32_t*            ps32_t ;
#define s32MIN   INT_MIN
#define s32MAX   INT_MAX

typedef     uint64_t            u64_t ;
typedef     uint64_t*           pu64_t ;
#define u64MIN   0
#define u64MAX   ULONG_MAX
typedef     int64_t             i64_t ;
typedef     int64_t*            pi64_t ;
#define i64MIN   LONG_MIN
#define i64MAX   LONG_MAX
typedef     int64_t             s64_t ;
typedef     int64_t*            ps64_t ;
#define s64MIN   LONG_MIN
#define s64MAX   LONG_MAX

typedef     unsigned long long  u80_t ;
typedef     unsigned long long* pu80_t ;
#define u80MIN   0
#define u80MAX   ULLONG_MAX
typedef     signed long long    i80_t ;
typedef     signed long long*   pi80_t ;
#define i80MIN   LLONG_MIN
#define i80MAX   LLONG_MAX
typedef     signed long long    s80_t ;
typedef     signed long long*   ps80_t ;
#define s80MIN   LLONG_MIN
#define s80MAX   LLONG_MAX

typedef     float               r32_t ;
typedef     float*              pr32_t ;
#define r32MIN  FLT_MIN
#define r32MAX  FLT_MAX
typedef     double              r64_t ;
typedef     double*             pr64_t ;
#define r64MIN  DBL_MIN
#define r64MAX  DBL_MAX
typedef     long double         r80_t ;
typedef     long double*        pr80_t ;
#define r80MIN  LDBL_MIN
#define r80MAX  LDBL_MAX

#define sizeMAX SIZE_MAX

typedef     intmax_t            iMax_t ;
#define     iMaxMIN             INTMAX_MIN
#define     iMaxMAX             INTMAX_MAX

//  
  
typedef unsigned char           c8_t ;
typedef unsigned char*          pc8_t ;

typedef wchar_t                 cw_t ;
typedef wchar_t*                pcw_t ;

typedef size_t                  z_t ;
typedef size_t*                 pz_t ;

typedef char*                   stringc_t ;
typedef const char*             cstringc_t ;

typedef wchar_t*                wstringc_t ;
typedef const wchar_t*          cwstringc_t ;

typedef void*                   pvoid_t;
typedef const void*             cpvoid_t;



/**/



#ifndef CONCATENATE0
#define CONCATENATE0(x,y)   x##y
#endif

#ifndef CONCATENATE
#define CONCATENATE(x,y)    CONCATENATE0(x,y)
#endif

#ifndef STRINGIFY0
#define STRINGIFY0(s) #s
#endif

#ifndef STRINGIFY
#define STRINGIFY(s) STRINGIFY0(s)
#endif

#define SUFFIX %

//#define ___u8(...)  CONCATENATE( __VA_ARGS__ ,hhu )
//#define __u8(...) STRINGIFY(___u8(...))
//#define _u8(...)  STRINGIFY(SUFFIX)  __u8(...)   

#define $nl     "\n"
#define $L      L""
#define $l      ""


/**/


// ... nelle macro si rende necessario a causa del compilatore CL, emette
// un messaggio di avvertimento se non si forniscono parametri alla macro

#define $u8(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,hhu ) )  
#define $i8(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,hhd ) ) 
#define $s8(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,hhd ) ) 

#define $u16(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,hu ) )  
#define $i16(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,hd ) ) 
#define $s16(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,hd ) ) 

#define $u32(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,u ) ) 
#define $i32(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,d ) ) 
#define $s32(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,d ) ) 

#ifdef _MSC_VER
    #define $u64(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,I64u ) ) 
    #define $i64(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,I64d ) )
    #define $s64(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,I64d ) )    
#else 
    #define $u64(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,lu ) ) 
    #define $i64(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,ld ) ) 
    #define $s64(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,ld ) )     
#endif

#define $u80(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,llu ) ) 
#define $i80(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,lld ) )
#define $s80(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,lld ) )
#define $iMax(...) STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,lld ) )

#define $z(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,zu ) ) 

/**/

#define $e32(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,e ) ) 
#define $e64(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,e ) ) 
#define $e80(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,Le ) ) 

#define $r32(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,f ) ) 
#define $r64(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,lf ) ) 
#define $r80(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,Lf ) ) 

/**/

#define $z(...)       STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,zu ) ) 
#define $size(...)    STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,zu ) ) 

#define $c8(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,c ) ) 
#define $cw(...)  STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ ,lc ) ) 

/**/

#ifdef _MSC_VER 
    #define $x64(...)       STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ , I64x ) ) 
    #define $x32(...)       STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ , Ix   ) ) 
    #define $x16(...)       STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ , x    ) ) 
#endif

#if defined(__MINGW32__) || defined(__MINGW64__)
    #define $x64(...)       STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ , llx ) ) 
    #define $x32(...)       STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ , lx  ) ) 
    #define $x16(...)       STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ , x  ) ) 
#endif 

#if defined(__linux__) 
    #define $x64(...)       STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ , llx ) ) 
    #define $x32(...)       STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ , lx  ) ) 
    #define $x16(...)       STRINGIFY(SUFFIX) STRINGIFY( CONCATENATE( __VA_ARGS__ , x  ) ) 
#endif 

/**/

#define _u8(...)  CONCATENATE(__VA_ARGS__,u)
#define _i8(...)  __VA_ARGS__
#define _s8(...)  __VA_ARGS__

#define _u16(...)  CONCATENATE(__VA_ARGS__,u)
#define _i16(...)  __VA_ARGS__
#define _s16(...)  __VA_ARGS__

#define _u32(...)  CONCATENATE(__VA_ARGS__,u)
#define _i32(...)  __VA_ARGS__
#define _s32(...)  __VA_ARGS__

#ifdef __linux__
    #define _u64(...)  CONCATENATE(__VA_ARGS__,lu)
    #define _i64(...)  CONCATENATE(__VA_ARGS__,l)
    #define _s64(...)  CONCATENATE(__VA_ARGS__,l)    
#endif

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
    #define _u64(...)  CONCATENATE(__VA_ARGS__,llu)
    #define _i64(...)  CONCATENATE(__VA_ARGS__,ll)
    #define _s64(...)  CONCATENATE(__VA_ARGS__,ll)    
#endif

#define _u80(...)  CONCATENATE(__VA_ARGS__,llu)
#define _i80(...)  CONCATENATE(__VA_ARGS__,ll)
#define _s80(...)  CONCATENATE(__VA_ARGS__,ll)

#define _r32(...)  CONCATENATE(__VA_ARGS__,f)
#define _r64(...)  __VA_ARGS__
#define _r80(...)  CONCATENATE(__VA_ARGS__,L)

#define _z(...) (size_t)__VA_ARGS__
 

 
#endif /* cdType */



/**/


