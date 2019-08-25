
//  FUNCTION OVERLOAD

#ifndef cdOOP
#define cdOOP

    #include <stdio.h>
    #include <stdlib.h>

    // ***********************
    // TRY THROW CATCH FINALLY
    // ***********************
    
    /* Copyright (C) 2009-2015 Francesco Nidito 
     *
     * Permission is hereby granted, free of charge, to any person obtaining a copy
     * of this software and associated documentation files (the "Software"), to deal
     * in the Software without restriction, including without limitation the rights to
     * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
     * of the Software, and to permit persons to whom the Software is furnished to do
     * so, subject to the following conditions: 
     *
     * The above copyright notice and this permission notice shall be included in all
     * copies or substantial portions of the Software. 
     *
     * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
     * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
     * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
     * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
     * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
     * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
     * SOFTWARE. 
     */

    #ifndef _TRY_THROW_CATCH_H_
    #define _TRY_THROW_CATCH_H_

    #include <stdio.h>
    #include <setjmp.h>

    /* For the full documentation and explanation of the code below, please refer to
     * http://www.di.unipi.it/~nids/docs/longjump_try_trow_catch.html
     */

    #define TRY do { jmp_buf ex_buf__; switch( setjmp(ex_buf__) ) { case 0: while(1) {
    #define CATCH(x) break; case x:
    #define FINALLY break; } default: {
    #define END_TRY break; } } }while(0)
    #define THROW(x) longjmp(ex_buf__, x)

    #endif /*!_TRY_THROW_CATCH_H_*/

    // **********
    // excetpion
    // **********
    
    typedef enum exception_e
    {
        no_excetpion            ,
        logic_error             ,
        invalid_argument        ,
        domain_error            ,
        length_error            ,
        out_of_range            ,
        future_error            ,    
        bad_optional_access     , 
        runtime_error           ,
        range_error             ,
        overflow_error          ,
        underflow_error         ,
        regex_error             , 
        nonexistent_local_time  ,  
        ambiguous_local_time    ,    
        tx_exception            ,    
        system_error            ,    
        filesystem_error        ,    
        bad_typeid              ,
        bad_cast                ,
        bad_any_cast            ,    
        bad_weak_ptr            ,    
        bad_function_call       ,   
        bad_alloc               ,
        bad_array_new_length    ,    
        bad_exception           ,
        ios_base_failure        ,   
        bad_variant_access
    } exception_t ;    

    // **********
    // JOIN, CAT
    // **********
    
    // .................................................... JOIN
    #define JOIN(x,y) x ## y
    
    // .................................................... CONCAT
    #define CONCAT(x,y) JOIN(x,y)


    // *****************
    // FUNCTION OVERLOAD
    // *****************
    
    // https://stackoverflow.com/questions/2124339/c-preprocessor-va-args-number-of-arguments

    #ifdef _MSC_VER // Microsoft compilers

    #   define GET_ARG_COUNT(...)  INTERNAL_EXPAND_ARGS_PRIVATE(INTERNAL_ARGS_AUGMENTER(__VA_ARGS__))

    #   define INTERNAL_ARGS_AUGMENTER(...) unused, __VA_ARGS__
    #   define INTERNAL_EXPAND(x) x
    #   define INTERNAL_EXPAND_ARGS_PRIVATE(...) INTERNAL_EXPAND(INTERNAL_GET_ARG_COUNT_PRIVATE(__VA_ARGS__, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
    #   define INTERNAL_GET_ARG_COUNT_PRIVATE(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count

    #else // Non-Microsoft compilers

    #   define GET_ARG_COUNT(...) INTERNAL_GET_ARG_COUNT_PRIVATE(0, ## __VA_ARGS__, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
    #   define INTERNAL_GET_ARG_COUNT_PRIVATE(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count

    #endif

    #define OVERLOAD    CONCAT
    #define ARG         GET_ARG_COUNT

    
    // *****************
    // ENUM CLASS
    // *****************
 
    #define EnumClass1(ID,X1      )  ID##_##X1 
    #define EnumClass2(ID,X1,...  )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass3(ID,X1,...  )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass4(ID,X1,...  )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass5(ID,X1,...  )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass6(ID,X1,...  )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass7(ID,X1,...  )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass8(ID,X1,...  )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass9(ID,X1,...  )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass10(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass11(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass12(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass13(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass14(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass15(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass16(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass17(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass18(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass19(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass20(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass21(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass22(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass23(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass24(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass25(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass26(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass27(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass28(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass29(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass30(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass31(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass32(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass33(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass34(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass35(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass36(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass37(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass38(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass39(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass40(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass41(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass42(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass43(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass44(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass45(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass46(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass47(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass48(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass49(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass50(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass51(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass52(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass53(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass54(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass55(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass56(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass57(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass58(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass59(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass60(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass61(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass62(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass63(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )
    #define EnumClass64(ID,X1,... )  ID##_##X1 ,  OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ )                            
                     
    //

    #define EnumClass(ID,...)  enum ID##_e { OVERLOAD ( EnumClass  , ARG(__VA_ARGS__) ) ( ID,__VA_ARGS__ ) }
    
    #define ENUM_CLASS EnumClass
    
    // *********** 
    // true false
    // *********** 

    #ifndef false
    #define false 0
    #endif

    #ifndef true
    #define true 1
    #endif

    #ifndef FALSE
    #define FALSE 0
    #endif

    #ifndef TRUE
    #define TRUE 1
    #endif
    
    // ****
    // OOP
    // ****


    #if defined(__MINGW32__) || defined(__MINGW64__) || defined(__GNUC__)
        #pragma GCC diagnostic ignored "-Wunused-variable"
        #pragma GCC diagnostic ignored "-Wunused-parameter"
    #endif

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <string.h>

    /**
    
        obj_t   :   struttura dati
        obj_s   :   struttura metodi
        obj     :   namespace metodo
        
    */

    // la base sono le interfacce

    /**
    
        // definisce l'interfaccia per i tipi   (t)
        // p.s. vs non vuole ;; in struttura
        
        #define INTERFACE_ANIMAL_T\
                int x ;\
                int y ;
     
        // definisce l'interfaccia per i metodi (s)
                
        #define INTERFACE_ANIMAL_S\
                void        (*delete)       (void*,...) ;\
                void        (*makeSound)    (void*,...) ;\
                void        (*setXY)        (void*,...) ;

        CLASS_TYPE( animal,

            INTERFACE_ANIMAL_T  
            
        );
    
    */
    
    // definisce la struttura per i tipi

    #define CLASS_TYPE(ID,...)\
    struct ID##_t\
    {\
        __VA_ARGS__\
    };\
    typedef struct ID##_t ID##_t ;

    // definisce la struttura per i metodi

    #define CLASS_STRUCTURE(ID,...)\
    typedef struct ID##_s\
    {\
        __VA_ARGS__\
    } ID##_s ; 

    // NEW , ansi C richiede di definire il primo campo, trick.

    #define NEW(ID,...) ID##_new("",##__VA_ARGS__)

    // copia dei metodi, trick.

    #define IMPORT_METHOD memmove

    #define CLASS(class,id,...)\
    typedef struct id ## _s\
    {\
        __VA_ARGS__\
        class##_s call;\
    } id##_t;\
    id##_t id;\
    memmove ( & id . call ,& class ,sizeof(class) );\

    #define $(id,method,...) (id . call. method( & id ),#__VA_ARGS__)

    #define INHERIT(ID) INTERFACE_##ID##_T

    // ...................................... PROPERTY  

    #define PROPERTY(TYPE,ID)\
    struct ID##_s\
    {\
       TYPE data;\
       TYPE (*get)(void);\
       void (*set)(TYPE value);\
    } ID

    // ...................................... GET  

    #define GET(ID)  (ID).data

    // ...................................... SET 

    #define SET(ID,value) (ID).data = value

    // ...................................... THIS 
    
    #define THIS(obj)    ((obj*)this)
     
    /**
    
        // final desstination
    
        CLASS(cat,c3,
        
            INHERIT(ANIMAL);
            animal_t xxx ;
            PROPERTY(int,a);

        ); // c3_t  
    
    */
    
    
    /**
    
        // utilizzo
    
        $(c3,makeSound); 

        c3.x = 11;
        c3.y = 12;    

        SET(c3.a,13) ;

        printf( "\n %d/%d - %d\n",c3.x,c3.y,GET(c3.a) );
    
    */
    /**/



#endif // cdOOP



/**/


