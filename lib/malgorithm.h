#ifndef cdAlgorithm
#define cdAlgorithm

    #ifdef __linux__
    #define _GNU_SOURCE 
    #endif

    #include "miterator.h"
    #include "mutility.h"    
    #include <stdlib.h>

    // ............................................................. all of

    #define algorithm_all_of(obj,id,from,to,lambda,ret)         \
    do {                                                        \
        unsigned int counter=0;                                 \
        obj##DataType##id* it;                                  \
        for ( it=from ; it!=to ; it++ )                         \
        {                                                       \
                if ( lambda )                                   \
                {                                               \
                    ++counter;                                  \
                }                                               \
        }                                                       \
        *ret = (counter == obj##Size(id)) ? 1 : 0   ;           \
    } while(0);

    // ............................................................. any of
    
    #define algorithm_any_of(obj,id,from,to,lambda,ret)         \
    do {                                                        \
        unsigned int counter=0;                                 \
        obj##DataType##id* it;                                  \
        for ( it=from ; it!=to ; it++ )                         \
        {                                                       \
                if ( lambda )                                   \
                {                                               \
                    counter=1; break;                           \
                }                                               \
        }                                                       \
        *ret = counter;                                         \
    } while(0);

    // ............................................................. none of
    
    #define algorithm_none_of(obj,id,from,to,lambda,ret)         \
    do {                                                        \
        unsigned int counter=0;                                 \
        obj##DataType##id* it;                                  \
        for ( it=from ; it!=to ; it++ )                         \
        {                                                       \
                if ( lambda )                                   \
                {                                               \
                    ++counter;                                  \
                }                                               \
        }                                                       \
        *ret = (counter == obj##Size(id)) ? 0 : 1   ;           \
    } while(0);

    // ............................................................. fore each
    
    #define algorithm_for_each(obj,id,from,to,lambda,ret)       \
    do {                                                        \
        obj##DataType##id* it;                                  \
        for ( it=from ; it!=to ; it++ )                         \
        {                                                       \
            *ret=lambda ;                                       \
        }                                                       \
    } while(0);
    
    // ............................................................. find
    
    #define algorithm_find(obj,id,from,to,value,ret)            \
    do {                                                        \
        obj##DataType##id* it;                                  \
        for ( it=from ; it!=to ; it++ )                         \
        {                                                       \
            if ( *it == value ) break;                          \
        }                                                       \
        ret = it ;                                              \
    } while(0);

    // ............................................................. find if
    
    #define algorithm_find_if(obj,id,from,to,lambda,ret)        \
    do {                                                        \
        obj##DataType##id* it;                                  \
        for ( it=from ; it!=to ; it++ )                         \
        {                                                       \
            if ( lambda ) break;                                \
        }                                                       \
        ret = it ;                                              \
    } while(0);

    // ............................................................. find if not
    
    #define algorithm_find_if_not(obj,id,from,to,lambda,ret)    \
    do {                                                        \
        obj##DataType##id* it;                                  \
        for ( it=from ; it!=to ; it++ )                         \
        {                                                       \
            if ( !(lambda) ) break;                             \
        }                                                       \
        ret = it ;                                              \
    } while(0);

    // ............................................................. find end
    
    #define algorithm_find_end(obj,id,_first1,_last1,_first2,_last2,ret)\
    do {\
        obj##DataType##id* first1=_first1;\
        obj##DataType##id* first2=_first2;\
        obj##DataType##id* last1=_last1;\
        obj##DataType##id* last2=_last2;\
        if ((first2)==(last2))\
        { \
            (ret) = (last1) ;\
            break;\
        }\
        else\
        {\
            (ret) = (last1);\
            while ((first1)!=(last1))\
            {\
                obj##DataType##id* it1 = (first1);\
                obj##DataType##id* it2 = (first2);\
                while (*it1==*it2)\
                {\
                    ++it1;\
                    ++it2;\
                    if (it2==last2)\
                    {\
                        (ret)=(first1);\
                        break;\
                    }\
                    if ((it2)==(last1))\
                    {\
                        break;\
                    }\
                }\
                ++(first1);\
            }\
        }\
    } while(0);

    // ............................................................. find first of

    #define algorithm_find_first_of(obj,id,_first1,_last1,_first2,_last2,ret)\
    do {\
        obj##DataType##id* first1=_first1;\
        obj##DataType##id* first2=_first2;\
        obj##DataType##id* last1=_last1;\
        obj##DataType##id* last2=_last2;\
        obj##DataType##id* it;\
        ret=NULL;\
        while (first1!=last1)\
        {\
            for (it=first2; it!=last2; ++it)\
            {\
                if (*it==*first1)\
                {\
                    ret = first1;\
                    break;\
                }\
            }\
            ++first1;\
        }\
        if (ret==NULL) ret =  last1;\
    } while(0);

    // .............................................................adjacent find

    #define algorithm_adjacent_find(obj,id,_first,_last,ret)\
    do {\
        obj##DataType##id* first=_first;\
        obj##DataType##id* last =_last;\
        ret=NULL;\
        if (first != last)\
        {\
            obj##DataType##id* next=first;\
            ++next;\
            while (next != last)\
            {\
                if (*first == *next)\
                {\
                    ret = first;\
                    break ;\
                }\
                ++first; ++next;\
            }\
        }\
        if ( ret==NULL) ret=last;\
    } while(0);

    // ............................................................. count

    #define algorithm_count(obj,id,from,to,value,ret)           \
    do {                                                        \
        unsigned int counter=0;                                 \
        obj##DataType##id* it;                                  \
        for ( it=from ; it!=to ; it++ )                         \
        {                                                       \
                if ( *it==value )                               \
                {                                               \
                    ++counter;                                  \
                }                                               \
        }                                                       \
        ret = counter;                                          \
    } while(0);

    // ............................................................. count if

    #define algorithm_count_if(obj,id,from,to,lambda,ret)       \
    do {                                                        \
        unsigned int counter=0;                                 \
        obj##DataType##id* it;                                  \
        for ( it=from ; it!=to ; it++ )                         \
        {                                                       \
                if ( lambda )                                   \
                {                                               \
                    ++counter;                                  \
                }                                               \
        }                                                       \
        ret = counter;                                          \
    } while(0);
    
    // ............................................................. Equal

    #define algorithm_equal(obj,id,_first1,_last1,_first2,_last2,ret)\
    do {\
        obj##DataType##id* first1=_first1;\
        obj##DataType##id* first2=_first2;\
        obj##DataType##id* last1=_last1;\
        obj##DataType##id* last2=_last2;\
        obj##DataType##id* it;\
        ret=-1;\
        while (first1!=last1)\
        {\
            if (!(*first1 == *first2))\
            {\
                ret=0;\
            }\
            ++first1; ++first2;\
        }\
        if (ret!=-1) ret = 1 ;\
    } while(0);

    // ............................................................. mismmatch

    #define algorithm_mismatch(obj,id,_first1,_last1,_first2,pair)\
    do {\
        obj##DataType##id* first1=_first1;\
        obj##DataType##id* first2=_first2;\
        obj##DataType##id* last1=_last1;\
        while ( (first1!=last1) && (*first1==*first2) )\
        {\
            ++first1; ++first2;\
        }\
        pair.first   = *first1;\
        pair.second  = *first2;\
    } while(0);


    // ............................................................. is permutation
    
   #define algorithm_is_permutation(obj,v1,v2,flag,compare)\
   do {\
        flag=0;\
        if (obj##Size(v1)==obj##Size(v2))\
        {\
            int size=obj##Size(v1);\
            \
            obj##DataType##v1 * v1X=(obj##DataType##v1*) malloc(sizeof(obj##DataType##v1)*size);\
            obj##DataType##v1 * v2X=(obj##DataType##v1*) malloc(sizeof(obj##DataType##v1)*size);\
            \
            memmove(v1X,v1.data,sizeof(obj##DataType##v1)*size);\
            memmove(v2X,v2.data,sizeof(obj##DataType##v1)*size);\
            \
            qsort(v1X,  size, sizeof(obj##DataType##v1),compare );\
            qsort(v2X,  size, sizeof(obj##DataType##v1),compare );\
            \
            flag=1;\
            for(int i=0;i<size;i++)\
            {\
                if(v1X[i]!=v2X[i]) { flag=0; break; }\
            }\
            free(v1X);\
            free(v2X);\
        }\
   } while(0);   

    // ............................................................. search
    
    #define algorithm_search(obj,id,_first1,_last1,_first2,_last2,ret)\
    do {\
        obj##DataType##id* first1=_first1;\
        obj##DataType##id* first2=_first2;\
        obj##DataType##id* last1=_last1;\
        obj##DataType##id* last2=_last2;\
        ret=NULL;\
        if (first2==last2)\
        {\
            ret = first1;\
        }\
        else\
        {\
            while (first1!=last1)\
            {\
                obj##DataType##id* it1 = first1;\
                obj##DataType##id* it2 = first2;\
                while (*it1==*it2)\
                {\
                    if (it2==last2)\
                    {\
                        ret = first1;\
                        break ;\
                    }\
                    if (it1==last1)\
                    {\
                        ret = last1;\
                        break ;\
                    }\
                ++it1; ++it2;\
                }\
                ++first1;\
            }\
            if (ret==NULL) ret = last1;\
        }\
    } while(0);

    // ............................................................. search N
    
    #define algorithm_search_n(obj,id,_first,_last,count,val,ret)\
    do {\
        obj##DataType##id* first =_first;\
        obj##DataType##id* last  =_last;\
        obj##DataType##id* it;\
        obj##DataType##id* limit =_first;\
        size_t i;\
        size_t dist;\
        itDistance(obj,id,first,last,dist);\
        dist-=count;\
        itAdvance(limit,dist);\
        ret=NULL;\
        while (first!=limit)\
        {\
            it = first;\
            i=0;\
            while (*it==val)\
            {\
              ++it;\
              if (++i==count)\
              {\
                  ret =  first;\
                  break;\
              }\
            }\
            ++first;\
        }\
        if (ret==NULL) ret=last;\
    } while(0);

    // ............................................................. copy
    
    #define algorithm_copy(obj,dest,source)\
    do {\
        obj##Clear(dest);\
        for(obj##DataType##source* it=obj##Begin(source);it!=obj##End(source);it++)\
            obj##PushBack(dest,*it);\
    } while(0);

    // ............................................................. copy range
    
    #define algorithm_copy_range(obj,id,_first,_last,_dest)\
    do {\
        obj##DataType##id* first    =_first ;\
        obj##DataType##id* last     =_last  ;\
        obj##DataType##id* dest     =_dest ;\
        while (first!=last)\
        {\
            *dest   = *first;\
            ++dest; ++first;\
        }\
    } while(0);

    // ............................................................. copy range N
    
    #define algorithm_copy_range_n(obj,id,_first,_last,_dest,N)\
    do {\
        obj##DataType##id* first    =_first ;\
        obj##DataType##id* last     =_last  ;\
        obj##DataType##id* dest     =_dest ;\
        N=0;\
        while (first!=last)\
        {\
            *dest   = *first;\
            ++dest; ++first;\
            N++;\
        }\
    } while(0);
    
    // ............................................................. copyIf
    
    #define algorithm_copy_if(obj,dest,source,lambda)\
    if(source.size>0) {\
        obj##Clear(dest);\
        for(obj##DataType##source* it=obj##Begin(source);it!=obj##End(source);it++)\
            if(lambda)obj##PushBack(dest,*it);\
    } ;

    // ............................................................. copy N
        
    #define algorithm_copy_n(obj,dest,source,N)\
    if(source.size>0) {\
        obj##Clear(dest);\
        size_t count=0;\
        for(obj##DataType##source* it=obj##Begin(source);it!=obj##End(source);it++)\
            if (count++<N) obj##PushBack(dest,*it); else break;\
    } ; 

    // ............................................................. copy backward
        
    #define algorithm_backward(obj,dest,source)\
    if(source.size>0) {\
        obj##Clear(dest);\
        obj##DataType##source* it;\
        for(it=obj##End(source)-1;it!=obj##Begin(source);it--) obj##PushBack(dest,*it);\
        obj##PushBack(dest,*it);\
    } ;

    // ............................................................. move
    
    #define algorithm_move(obj,dest,source)\
    if(source.size>0) {\
        dest.size=0;\
        for(obj##DataType##source* it=obj##Begin(source);it!=obj##End(source);it++)\
            obj##PushBack(dest,*it);\
        source.size=0;\
    } ;

    // ............................................................. move backward
        
    #define algorithm_move_backward(obj,dest,source)\
    if(source.size>0) {\
        dest.size=0;\
        obj##DataType##source* it;\
        for(it=obj##End(source)-1;it!=obj##Begin(source);it--) obj##PushBack(dest,*it);\
        obj##PushBack(dest,*it);\
        source.size=0;\
    } ;

    // ............................................................. Swap Range
   
    #define algorithm_swap_range(obj,id,_first1,_last1,_first2)\
    do {\
        obj##DataType##id* first1    =_first1;\
        obj##DataType##id* first2    =_first2;\
        obj##DataType##id* last1     =_last1;\
        obj##DataType##id  temp;\
        while (first1!=last1)\
        {\
            temp    = *first1;\
            *first1 = *first2;\
            *first2 = temp;\
            ++first1; ++first2;\
        }\
    } while(0);

    #define algorithm_swap_ranges algorithm_swap_range

// ............................................................. Swap Iter
    
    #define algorithm_swap_iter(obj,id,_first,_last)\
    do {\
        obj##DataType##id* first    =_first;\
        obj##DataType##id* last     =_last;\
        obj##DataType##id  temp;\
            temp    = *first;\
            *first = *last;\
            *last = temp;\
    } while(0);
    
    #define algorithm_IterSwap algorithm_SwapIter

    // ............................................................. transform
        
    #define algorithm_transform(obj,id,_first,_last,lambda)\
    do {\
        obj##DataType##id* it    =_first;\
        obj##DataType##id* last  =_last;\
        while ( (it!=last )   )\
        {\
            lambda;\
            ++it;\
        }\
    } while(0);

    // ............................................................. replace
    
    #define algorithm_replace(obj,id,_first,_last,findValue,replaceWith)\
    do {\
            obj##DataType##id* it;\
            for(it=_first;it!=_last;it++)\
            {\
                if ( *it==(obj##DataType##id)findValue )\
                {\
                    *it=(replaceWith);\
                };\
            }\
    } while(0);
    
    // ............................................................. replaceIf
    
    #define algorithm_replace_if(obj,id,_first,_last,lambda,replaceWith)\
    do {\
            obj##DataType##id* it;\
            for(it=_first;it!=_last;it++)\
            {\
                if ( lambda )\
                {\
                    *it=(replaceWith);\
                };\
            }\
    } while(0);     

    // ............................................................. replaceCopy
    
    #define algorithm_replace_copy(obj,id,_first,_last,dest,findValue,replaceWith)\
    do {\
            obj##Clear(dest);\
            obj##DataType##id* it;\
            for(it=_first;it!=_last;it++)\
            {\
                if ( (obj##DataType##id)*it==(obj##DataType##id)findValue )\
                {\
                    *it=(replaceWith);\
                };\
                obj##PushBack(dest,*it);\
            }\
    } while(0);

    // ............................................................. replaceCopyIf
   
    #define algorithm_replace_copy_if(obj,id,_first,_last,dest,lambda,replaceWith)\
    do {\
            obj##Clear(dest);\
            obj##DataType##id* it;\
            for(it=_first;it!=_last;it++)\
            {\
                if ( lambda )\
                {\
                    *it=(replaceWith);\
                };\
                obj##PushBack(dest,*it);\
            }\
    } while(0);

    // ............................................................. fill
   
    #define algorithm_fill(obj,id,_first,_last,replaceWith)\
            for(obj##DataType##id* it=_first;it!=_last;it++)\
            {\
                    *it=(replaceWith);\
            }\

    // ............................................................. fill N
   
    #define algorithm_fill_n(obj,id,_first,lambda,_n)\
    do {\
        obj##DataType##id* first    =_first;\
        size_t N=_n;\
          while (N>0) {\
            *first = lambda;\
            ++first; --N;\
          }\
    } while(0);
     
    // ............................................................. generate
   
    #define algorithm_generate(obj,id,_first,_last,lambda)\
            for(obj##DataType##id* it=_first;it!=_last;it++)\
            {\
                    *it=(lambda);\
            }\

    // ............................................................. generate N
   
    #define algorithm_generate_n(obj,id,_first,lambda,_n)\
    do {\
        obj##DataType##id* first    =_first;\
        size_t N=_n;\
          while (N>0) {\
            *first = lambda;\
            ++first; --N;\
          }\
    } while(0);


    // ............................................................. remove
   
    #define algorithm_remove(obj,id,_first,_last,_val)\
    do {\
        obj##DataType##id* first    =_first;\
        obj##DataType##id* result   =_first;\
        obj##DataType##id* last     =_last;\
        obj##DataType##id  val      =_val;\
        size_t size=0;\
        while (first!=last)\
        {\
            if (!(*first == val))\
            {\
                *result = *first;\
                ++result;\
                size++;\
            }\
            ++first;\
        }\
        obj##Size(id)=size;\
    } while(0);

    // ............................................................. remove if
   
    #define algorithm_remove_if(obj,id,_first,_last,lambda)\
    do {\
        obj##DataType##id* it       =_first;\
        obj##DataType##id* result   =_first;\
        obj##DataType##id* last     =_last;\
        size_t size=0;\
        while (it!=last)\
        {\
            if (!(lambda))\
            {\
                *result = *it;\
                ++result;\
                size++;\
            }\
            ++it;\
        }\
        obj##Size(id)=size;\
    } while(0);


    // ............................................................. removeCopy
   
    #define algorithm_remove_copy(obj,id,_first,_last,dest,_val)\
    do {\
        obj##DataType##id* first    =_first;\
        obj##DataType##id* last     =_last;\
        obj##DataType##id  val      =_val;\
        obj##Clear(dest);\
        while (first!=last)\
        {\
            if (!(*first == val))\
            {\
                obj##PushBack( dest , *first);\
            }\
            ++first;\
        }\
    } while(0);

    // ............................................................. remove Copy If
   
    #define algorithm_remove_copy_if(obj,id,_first,_last,dest,lambda)\
    do {\
        obj##DataType##id* it       =_first;\
        obj##DataType##id* last     =_last;\
        obj##Clear(dest);\
        while (it!=last)\
        {\
            if (!(lambda))\
            {\
                obj##PushBack( dest , *it);\
            }\
            ++it;\
        }\
    } while(0);

    // ............................................................. unique
   
    #define algorithm_unique(obj,id,_first,_last)\
    do {\
        obj##DataType##id* first    =_first;\
        obj##DataType##id* last     =_last;\
        obj##DataType##id* result   =_first;\
        size_t size=0;\
        if (first!=last)\
        {\
            while (++first != last)\
            {\
                if (!(*result == *first))\
                {\
                    size++;\
                    *(++result)=*first;\
                }\
            }\
           obj##Size(id)=size+1;\
        }\
    } while(0);

    // ............................................................. unique copy
   
    #define algorithm_unique_copy(obj,id,_first,_last,dest)\
    do {\
        obj##DataType##id* first    =_first;\
        obj##DataType##id* last     =_last;\
        obj##DataType##id* result   = obj##Begin(dest);\
        obj##Clear(dest);\
        if (first!=last)\
        {\
             obj##PushBack( dest ,*first );\
             *result = *first;\
              while (++first != last) \
              {\
                obj##DataType##id val = *first;\
                if (!(*result == val))\
                {\
                  obj##PushBack( dest ,val );\
                  *(++result)=val;\
                }\
              }\
        }\
    } while(0);
 
    // ............................................................. reverse
   
    #define algorithm_reverse(obj,id,_first,_last)\
    do {\
        obj##DataType##id* first    =_first;\
        obj##DataType##id* last     =_last;\
        while ((first!=last)&&(first!=--last))\
        {\
            obj##DataType##id temp;\
            temp  = *first;\
            *first = *last;\
            *last  = temp;\
            ++first;\
        }\
    } while(0);

    // ............................................................. reverse copy
   
    #define algorithm_reverse_copy(obj,id,_first,_last,dest)\
    do {\
        obj##DataType##id* first    =_first;\
        obj##DataType##id* last     =_last;\
        obj##Clear(dest);\
        size_t max=obj##Size(id);\
        for(int i=max-1;i>0;i--)\
        {\
                obj##PushBack(dest,(id).data[i] );\
        }\
        obj##Size(dest)=obj##Size(id);\
    } while(0);

    // ............................................................. rotate
   
    #define algorithm_rotate(obj,id,_first,_middle,_last)\
    do {\
        obj##DataType##id* first    =_first;\
        obj##DataType##id* middle   =_middle;\
        obj##DataType##id* last     =_last;\
        obj##DataType##id* next     =_middle;\
        while (first!=next)\
        {\
            obj##DataType##id temp ;\
            temp = *first;\
            *first = *next;\
            *next = temp;\
            first++;\
            next++;\
            if (next==last) next=middle;\
            else if (first==middle) middle=next;\
        }\
    } while(0);

    // ............................................................. rotate copy
 
    #define algorithm_rotate_copy(obj,id,_first,_middle,_last,dest)\
    do{\
        algorithm_copy(obj,dest,id);\
        algorithm_rotate(obj,dest,_first,_middle,_last );\
    }while(0);
 
    // ............................................................. shuffle
    
    #define algorithm_shuffle(obj,id,_first,_last)\
    do {\
        obj##DataType##id* it=_first;\
        obj##DataType##id  temp;\
        size_t ndx=0;\
        size_t rnd=0;\
        itDistance(obj,id,_first,_last,rnd);\
        for(it=_first;it!=_last;it++)\
        {\
            ndx             = rand() % rnd ;\
            temp            = *it ;\
            *it             = (id).data[ndx];\
            (id).data[ndx]  = temp;\
        }\
    } while(0);
 
    // ............................................................. Random shuffle
    
    #define algorithm_random_shuffle(obj,id,_first,_last,lambda)\
    do {\
        obj##DataType##id* it=_first;\
        obj##DataType##id  temp;\
        size_t ndx;\
        for(it=_first;it!=_last;it++)\
        {\
            ndx             = (lambda) ;\
            temp            = *it ;\
            *it             = (id).data[ndx];\
            (id).data[ndx]  = temp;\
        }\
    } while(0);
    
    // ............................................................. sort
    
    #define algorithm_sort(obj,id,_first,_last,CMP)\
    do {\
        obj##DataType##id* first=_first;\
        obj##DataType##id* last =_last;\
        size_t N;\
        itDistance(obj,id,first,last,N);\
        qsort ( first, N , sizeof(obj##DataType##id), CMP);\
    } while(0);
    
    #define algorithm_stable_sort  algorithm_sort

    // ............................................................. Partal Sort
    
    #define algorithm_partial_sort(obj,id,_first,_middle,_last,CMP)\
    do {\
        obj##DataType##id* first =_first;\
        obj##DataType##id* middle=_middle;\
        obj##DataType##id* last  =_last;\
        size_t N;\
        itDistance(obj,id,middle,last,N);\
        qsort ( middle , N , sizeof(obj##DataType##id), CMP);\
        algorithm_rotate(obj,id,_first,_middle,_last);\
    } while(0);

    // ............................................................. Partal Sort copy
    
    #define algorithm_partial_sort_copy(obj,id,_first,_middle,_last,copy,CMP)\
    do {\
        obj##Clear(copy);\
        algorithm_copy(obj,copy,id);\
        algorithm_partial_sort(obj,copy,_first,_middle,_last,CMP);\
    } while(0);

    // ............................................................. is sorted
    
    #define algorithm_is_sorted(obj,id,_first,_last,sorted)\
    do {\
        obj##DataType##id* first=_first;\
        obj##DataType##id* last =_last-1;\
        obj##DataType##id* it;\
        sorted=1;\
        for(it=first;it!=last;it++)\
        {\
            if ( *it > *(it+1) ) { sorted=0; break;};\
        }\
    } while(0);

    // ............................................................. is sorted until
    
    #define algorithm_is_sorted_until(obj,id,_first,_last,sorted)\
    do {\
        obj##DataType##id* first=_first;\
        obj##DataType##id* last =_last-1;\
        obj##DataType##id* it;\
        sorted=NULL;\
        for(it=first;it!=last;it++)\
        {\
            if ( *it > *(it+1) ) { sorted=it; break;};\
        }\
    } while(0); 

    // ............................................................. lower bound
    
    #define algorithm_lower_bound(obj,id,_first,_last,val,ITPOS)\
    do {\
        obj##DataType##id* first=_first  ;\
        obj##DataType##id* last =_last-1 ;\
        obj##DataType##id* it;\
        size_t count=0;\
        size_t step=0;\
        itDistance(obj,id,first,last,count);\
        while (count>0)\
        {\
            it = first;\
            step=count/2;\
            itAdvance (it,step);\
            if (*it<val)\
            {\
                first   =   ++it;\
                count   -=  step+1;\
            }\
            else\
            {\
                count=step;\
            }\
        }\
        ITPOS = first;\
    } while(0); 

    // ............................................................. upper bound
    
    #define algorithm_upper_bound(obj,id,_first,_last,val,ITPOS)\
    do {\
        obj##DataType##id* first=_first  ;\
        obj##DataType##id* last =_last-1 ;\
        obj##DataType##id* it;\
        size_t count=0;\
        size_t step=0;\
        itDistance(obj,id,first,last,count);\
        while (count>0)\
        {\
            it = first;\
            step=count/2;\
            itAdvance (it,step);\
            if (!(val<*it))\
            {\
                first   =   ++it;\
                count   -=  step+1;\
            }\
            else\
            {\
                count=step;\
            }\
        }\
        ITPOS = (first-1);\
    } while(0); 

    // ............................................................. binary search
    
    #define algorithm_binary_search(obj,id,_first,_last,val,found)\
    do {\
        obj##DataType##id* ITPOS;\
        obj##DataType##id* last =_last;\
        found=0;\
        algorithm_lower_bound(obj,id,_first,_last,val,ITPOS);\
        found=(ITPOS!=last && !(val<*ITPOS));\
    } while(0);


    // ............................................................. equal range
    
    #define algorithm_equal_range(obj,id,_first,_last,val,from,to)\
    do {\
        obj##DataType##id* ITPOS;\
        \
        algorithm_lower_bound(obj,id,_first,_last,val,ITPOS);\
        itDistance(obj,id,_first,ITPOS,from);\
        \
        algorithm_upper_bound(obj,id,_first,_last,val,ITPOS);\
        itDistance(obj,id,ITPOS,_last,to);\
        \
    } while(0);
        

    // .................................... min max in range
    
    #define algorithm_minmax_element(obj,id,_first,_last,min,max)\
    do {\
        obj##DataType##id* first=_first  ;\
        obj##DataType##id* last =_last   ;\
        obj##DataType##id* it ;\
        min = *first;\
        max = *first;\
        for ( it=first ; it!=last; it++)\
        {\
            if ( (*it) < min ) { min = *it ;}\
            if ( (*it) > max ) { max = *it ;}\
        }\
    } while(0);

    #define algorithm_min_element(obj,id,_first,_last,min)\
    do {\
        obj##DataType##id* first=_first  ;\
        obj##DataType##id* last =_last   ;\
        obj##DataType##id* it ;\
        min = *first;\
        for ( it=first ; it!=last; it++)\
        {\
            if ( (*it) < min ) { min = *it ;}\
        }\
    } while(0);

    #define algorithm_max_element(obj,id,_first,_last,max)\
    do {\
        obj##DataType##id* first=_first  ;\
        obj##DataType##id* last =_last   ;\
        obj##DataType##id* it ;\
        max = *first;\
        for ( it=first ; it!=last; it++)\
        {\
            if ( (*it) > max ) { max = *it ;}\
        }\
    } while(0);

    // .................................... min max in object
     
    #define algorithm_minmax(obj,id,min,max)\
    do {\
        obj##DataType##id* first=obj##Begin(id) ;\
        obj##DataType##id* last =obj##End(id)   ;\
        obj##DataType##id* it ;\
        min = *first;\
        max = *first;\
        for ( it=first ; it!=last; it++)\
        {\
            if ( (*it) < min ) { min = *it ;}\
            if ( (*it) > max ) { max = *it ;}\
        }\
    } while(0);

    #define algorithm_min(obj,id,min)\
    do {\
        obj##DataType##id* first=obj##Begin(id) ;\
        obj##DataType##id* last =obj##End(id)   ;\
        obj##DataType##id* it ;\
        min = *first;\
        for ( it=first ; it!=last; it++)\
        {\
            if ( (*it) < min ) { min = *it ;}\
        }\
    } while(0);
    
    #define algorithm_max(obj,id,max)\
    do {\
        obj##DataType##id* first=obj##Begin(id) ;\
        obj##DataType##id* last =obj##End(id)   ;\
        obj##DataType##id* it ;\
        max = *first;\
        for ( it=first ; it!=last; it++)\
        {\
            if ( (*it) > max ) { max = *it ;}\
        }\
    } while(0);
    
    #define algorithm_minmax_range   algorithm_minmax_element
    #define algorithm_min_range      algorithm_min_element
    #define algorithm_max_range      algorithm_max_element
    
    #define algorithm_minmax_object  algorithm_minmax  
    #define algorithm_min_object     algorithm_min  
    #define algorithm_max_object     algorithm_max  
        
    // .................................... lexicographical_compare
    
    #define lexicographical_compare(obj,id,_first1,_last1,_first2,_last2,ret)\
    do {\
        obj##DataType##id* first1=_first1 ;\
        obj##DataType##id* last1 =_last1  ;\
        obj##DataType##id* first2=_first2 ;\
        obj##DataType##id* last2 =_last2  ;\
        ret=-1;\
        while (first1!=last1)\
        {\
            if (first2==last2 || *first2<*first1)\
            {\
                ret = 0;\
                break;\
            }\
            else\
            {\
                if (*first1<*first2)\
                {\
                    ret = 1;\
                    break;\
                }\
            }\
            if (ret!=-1) break;\
            ++first1; ++first2;\
        }\
        if ( ret==-1) ret = (first2!=last2);\
    } while(0);

    // .................................... next permutation

    int next_permutation(char* s) ;

    // .................................... next permutation
    
    int prev_permutation(char* s)  ;

    // ............................................................. make heap
    
    #define make_heap(obj,id,_first,_last)\
    do {\
        obj##DataType##id  max   = *_first;\
        obj##DataType##id* itmax =  _first;\
        for ( obj##DataType##id* it=_first ; it!=_last; it++)\
        {\
            if ( (*it) > max )\
            {\
                max   = *it ;\
                itmax =  it ;\
            }\
        }\
        if ( itmax!=_first )\
        {\
            obj##DataType##id   temp ;\
            temp    = *itmax;\
            *itmax  = *_first;\
            *_first = temp;\
        }\
    } while(0);

    // ............................................................. pop heap
    #define pop_heap(obj,id,_first,_last)\
    do {\
        obj##DataType##id* first = _first;\
        obj##DataType##id* last  = _last ;\
        size_t N ;\
        itDistance(obj,id,_first,_last,N);\
        memmove(_first,_first+1,sizeof(obj##DataType##id)*N);\
        --(id).size;\
    } while(0);

    // ............................................................. push heap

    #define push_heap(obj,id,_first,_last,val)\
    do {\
        obj##DataType##id* first = _first;\
        obj##DataType##id* last  = _last ;\
        obj##DataType##id* end   = obj##End(id);\
        size_t N ;\
        itDistance(obj,id,_last,end,N);\
        N=obj##Size(id)-N;\
        obj##InsertAtVal(id, N, val);\
    } while(0);

    // ............................................................. sort heap

    #define sort_heap(obj,id,_first,_last,CMP)\
    do {\
        obj##DataType##id* first=_first;\
        obj##DataType##id* last =_last;\
        size_t N;\
        itDistance(obj,id,first,last,N);\
        qsort ( first, N , sizeof(obj##DataType##id), CMP);\
    } while(0);   

    // ............................................................. is heap until

    #define is_heap_until(obj,id,_first,_last,it)\
    do {\
        it = _first+1;\
        for ( ; it!=_last; it++)\
        {\
            if (  (*it) > (*_first) ) break ;\
        }\
    } while(0);

    // ............................................................. is heap

    #define is_heap(obj,id,_first,_last,flag)\
    do {\
        obj##DataType##id* it=_first+1;\
        flag=1;\
        for ( ; it!=_last; it++)\
        {\
            if (  (*it) > (*_first) ) { flag=0; break ; }\
        }\
    } while(0);

    // ............................................................. merge

    #define algorithm_merge(obj,id,_first1,_last1,_first2,_last2)\
    do {\
        obj##DataType##id* first1    =_first1 ;\
        obj##DataType##id* last1     =_last1 ;\
        obj##DataType##id* first2    =_first2 ;\
        obj##DataType##id* last2     =_last2 ;\
        obj##Clear(id);\
        size_t ndx=0;\
        while(first1!=last1)  obj##At(id,ndx++)=*first1++;\
        while(first2!=last2)  obj##At(id,ndx++)=*first2++;\
    } while(0);\

    // ............................................................. includes

    #define algorithm_includes(obj,id,_first1,_last1,_first2,_last2,result)\
    do {\
        obj##DataType##id* first1    =_first1 ;\
        obj##DataType##id* last1     =_last1 ;\
        obj##DataType##id* first2    =_first2 ;\
        obj##DataType##id* last2     =_last2 ;\
        result=-1;\
        while (first2!=last2) \
        {\
            if ( (first1==last1) || (*first2<*first1) ) {result=1;break;};\
            if (!(*first1<*first2)) ++first2;\
            ++first1;\
        }\
        if ( result==-1 ) result=0;\
    } while(0);

    // ............................................................. set intersection

    #define algorithm_set_insersection(obj,id,_first1,_last1,_first2,_last2,_result)\
    do {\
        obj##DataType##id* first1    =_first1 ;\
        obj##DataType##id* last1     =_last1  ;\
        obj##DataType##id* first2    =_first2 ;\
        obj##DataType##id* last2     =_last2  ;\
        obj##DataType##id* result    =_result ;\
        while (first1!=last1 && first2!=last2)\
        {\
            if (*first1<*first2) ++first1;\
            else if (*first2<*first1) ++first2;\
            else {\
              *result = *first1;\
              ++result; ++first1; ++first2;\
            }\
        }\
        obj##Size(id)=*result;\
    } while(0);

    // ............................................................. set difference

    #define algorithm_set_difference(obj,id,_first1,_last1,_first2,_last2,_result)\
    do {\
        obj##DataType##id* first1    =_first1 ;\
        obj##DataType##id* last1     =_last1  ;\
        obj##DataType##id* first2    =_first2 ;\
        obj##DataType##id* last2     =_last2  ;\
        obj##DataType##id* result    =_result ;\
        size_t dist=0;\
        while (first1!=last1 && first2!=last2)\
        {\
            if (*first1<*first2) { dist++; *result = *first1; ++result; ++first1; }\
            else if (*first2<*first1) ++first2;\
            else { ++first1; ++first2; }\
        }\
        obj##Size(id)=dist;\
        obj##DataType##id* it;\
        for(it=first1;it!=last1;it++)   *result++ = *it++ ;\
    } while(0);

        
   
    // ............................................................. set symmetric difference

    #define algorithm_set_symmetric_difference(obj,id,_first1,_last1,_first2,_last2,_result)\
    do {\
        obj##DataType##id* first1    =_first1 ;\
        obj##DataType##id* last1     =_last1  ;\
        obj##DataType##id* first2    =_first2 ;\
        obj##DataType##id* last2     =_last2  ;\
        obj##DataType##id* result    =_result ;\
        size_t N,dist=0;\
        while (1)\
        {\
            if (first1==last1) { algorithm_copy_range_n(obj,id,first2,last2,result,N); dist+=N; break ;}\
            if (first2==last2) { algorithm_copy_range_n(obj,id,first1,last1,result,N); dist+=N; break ;}\
            if (*first1<*first2) { dist++; *result = *first1; ++result; ++first1; }\
                else\
            if (*first2<*first1)\
                 { dist++; *result = *first2; ++result; ++first2; }\
            else { ++first1; ++first2; }\
        }\
        obj##Size(id)=dist;\
     } while(0);

    // ............................................................. set union

    #define algorithm_set_union(obj,id,_first1,_last1,_first2,_last2,_result)\
    do {\
        obj##DataType##id* first1    =_first1 ;\
        obj##DataType##id* last1     =_last1  ;\
        obj##DataType##id* first2    =_first2 ;\
        obj##DataType##id* last2     =_last2  ;\
        obj##DataType##id* result    =_result ;\
        size_t N,dist=0;\
        while (1)\
        {\
            if (first1==last1) { algorithm_copy_range_n(obj,id,first2,last2,result,N); dist+=N; break ;}\
            if (first2==last2) { algorithm_copy_range_n(obj,id,first1,last1,result,N); dist+=N; break ;}\
            if (*first1<*first2) { dist++ ; *result = *first1; ++first1; }\
                else\
            if (*first2<*first1)\
                 { dist++ ; *result = *first2; ++first2; }\
            else { dist++ ; *result = *first1; ++first1; ++first2; }\
            ++result;\
        }\
        obj##Size(id)=dist;\
     } while(0);

    // ............................................................. partition

    #define algorithm_partition(obj,id,_first,_last,lambda)\
    do {\
        obj##DataType##id* first    =_first ;\
        obj##DataType##id* last     =_last  ;\
        obj##DataType##id* it;\
        obj##DataType##id* end=NULL;\
        while (first!=last)\
        {\
            it=first;\
            while (lambda)\
            {\
              ++first;\
              if (first==last) { end=first; break;}\
              it=first;\
            }\
            if ( end!=NULL) break;\
            do {\
              --last;\
              if (first==last) { end=first; break;}\
              it=last;\
            } while (!(lambda));\
            if ( end!=NULL) break;\
            obj##DataType##id temp;\
            temp=*first;\
            *first=*last;\
            *last=temp;\
            ++first;\
        }\
        if (end==NULL) end=first;\
     } while(0);

    // ............................................................. is partitioned

    #define algorithm_is_partitioned(obj,id,_first,_last,lambda,flag)\
    do {\
        obj##DataType##id* it     =_first ;\
        obj##DataType##id* first  =_first ;\
        obj##DataType##id* last   =_last  ;\
        flag=-1;\
        while ((it=first)!=last && (lambda))\
        {\
            ++first;\
        }\
        while ((it=first)!=last)\
        {\
            if (lambda) { flag=0; break; }\
            ++first;\
        }\
        if (flag==-1) flag=1;\
     } while(0);

    // ............................................................. partition point

    #define algorithm_partition_point(obj,id,_first,_last,lambda,point)\
    do {\
        obj##DataType##id* first  =_first ;\
        obj##DataType##id* last   =_last  ;\
        obj##DataType##id* it     =_first ;\
        obj##DataType##id  n;\
        itDistance(obj,id,first,last,n);\
        while (n>0)\
        {\
            obj##DataType##id step=n/2 ;\
            itAdvance (it,step);\
            if (lambda) { first=++it; n-=step+1; }\
            else n=step;\
        }\
        point=first;\
     } while(0);

    // ............................................................. partition copy

    #define algorithm_partition_copy(obj,id,_first,_last,d1,d2,lambda)\
    do {\
        obj##DataType##id* first  = _first ;\
        obj##DataType##id* last   = _last ;\
        obj##DataType##id* it     = _first ;\
        size_t ndx1=0;\
        size_t ndx2=0;\
        while (first!=last)\
        {\
            if (lambda)\
            {\
                obj##At(d1,ndx1) = *first;\
                ndx1++;\
            }\
            else\
            {\
                obj##At(d2,ndx2) = *first;\
                ndx2++;\
            }\
            ++first;\
            it=first;\
        }\
        obj##Size(d1)=ndx1;\
        obj##Size(d2)=ndx2;\
     } while(0);
     
/**/




#endif



/**/


