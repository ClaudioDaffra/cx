
#include "mutility.h"

int float_approximatelyEqual(float a, float b )
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON);
}
int float_essentiallyEqual(float a, float b )
{
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON);
}
int float_definitelyGreaterThan(float a, float b )
{
    return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON);
}
int float_definitelyLessThan(float a, float b )
{
    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON);
}
int float_equal(float a,float b)
{
   if(  fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON)  ) return 1 ;
   if(  fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON)  ) return 1 ;
   return 0 ;
}
int float_ge(float a,float b)
{
   if(  fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON)  ) return 1 ;
   if(  fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON)  ) return 1 ;
   if(  (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON)       ) return 1 ; 
   return 0 ;
}
int float_le(float a,float b)
{
   if(  fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON)  ) return 1 ;
   if(  fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON)  ) return 1 ;
   if(  (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * FLT_EPSILON)       ) return 1 ; 
   return 0 ;
}
int double_approximatelyEqual(double a, double b )
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON);
}
int double_essentiallyEqual(double a, double b )
{
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON);
}
int double_definitelyGreaterThan(double a, double b )
{
    return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON);
}
int double_definitelyLessThan(double a, double b )
{
    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON);
}
int double_equal(double a,double b)
{
   if(  fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON)  ) return 1 ;
   if(  fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON)  ) return 1 ;
   return 0 ;
}
int double_ge(double a,double b)
{
   if(  fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON)  ) return 1 ;
   if(  fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON)  ) return 1 ;
   if(  (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON)       ) return 1 ; 
   return 0 ;
}
int double_le(double a,double b)
{
   if(  fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON)  ) return 1 ;
   if(  fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON)  ) return 1 ;
   if(  (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * DBL_EPSILON)       ) return 1 ; 
   return 0 ;
}
int longdouble_approximatelyEqual(long double a, long double b )
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON);
}
int longdouble_essentiallyEqual(long double a, long double b )
{
    return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON);
}
int longdouble_definitelyGreaterThan(long double a, long double b )
{
    return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON);
}
int longdouble_definitelyLessThan(long double a, long double b )
{
    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON);
}
int longdouble_equal(long double a,long double b)
{
   if(  fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON)  ) return 1 ;
   if(  fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON)  ) return 1 ;
   return 0 ;
}
int longdouble_ge(long double a,long double b)
{
   if(  fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON)  ) return 1 ;
   if(  fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON)  ) return 1 ;
   if(  (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON)       ) return 1 ; 
   return 0 ;
}
int longdouble_le(long double a,long double b)
{
   if(  fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON)  ) return 1 ;
   if(  fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON)  ) return 1 ;
   if(  (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * LDBL_EPSILON)       ) return 1 ; 
   return 0 ;
}

// https://stackoverflow.com/questions/28511621/how-to-swap-memory-between-two-void-pointers-in-c

void cdSwapObjects(void *pa, void *pb, size_t size) 
{
    unsigned char tmp;
    unsigned char *a = pa, *b = pb;
    while(size--) 
    {
        tmp = *a;
        *a++ = *b;
        *b++ = tmp;
    }
}
  
  
/**/


