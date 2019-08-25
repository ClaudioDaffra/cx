#include "ratio.h"
#include "mutility.h"

/*
ratio_t octo	 = { 1,1000000000000000000000000ULL } ; //  1'-24 * 
ratio_t zepto	 = { 1,1000000000000000000000ULL } ; // 	10-21 *
*/
ratio_t atto	 = { 1,1000000000000000000ULL } ; // 	10-18
ratio_t femto	 = { 1,1000000000000000 } ; // 	10-15
ratio_t pico	 = { 1,1000000000000 } ; // 	10-12
ratio_t nano	 = { 1,1000000000 } ; // 	10-9
ratio_t micro	 = { 1,1000000 } ; // 	10-6
ratio_t milli	 = { 1,1000 } ; // 	10-3
ratio_t centi	 = { 1,100 } ; // 	10-2
ratio_t deci	 = { 1,10 } ; // 10-1
ratio_t deca	 = { 10,1 } ; // 101
ratio_t hecto	 = { 100,1 } ; // 	102
ratio_t kilo	 = { 1000,1 } ; // 	103
ratio_t mega	 = { 1000000,1 } ; // 	106
ratio_t giga	 = { 1000000000,1 } ; // 	109
ratio_t tera	 = { 1000000000000,1 } ; // 	1012
ratio_t peta	 = { 1000000000000000,1 } ; // 	1015
ratio_t exa	     = { 1000000000000000000ULL,1 } ; // 	1018
/*
ratio_t zetta	 = { 1000000000000000000000L,1 } ; // 	1021 *
ratio_t yotta	 = { 1000000000000000000000000L,1 } ; // 
*/

int ratioEQ( ratio_t x,ratio_t y)
{
    //return (x.num/x.den)==(x.num/x.den)?1:0;
    return DEQ(  x.num/x.den ,   y.num/y.den );
}
int ratioNE( ratio_t x,ratio_t y)
{
    //return !ratioEQ(x,y);
    return DNE(  x.num/x.den ,   y.num/y.den );  
}
int ratioLT( ratio_t x,ratio_t y)
{
    //return !(x.num/x.den) < (y.num/y.den)?1:0;
    return DLT(  x.num/x.den ,   y.num/y.den );    
}
int ratioLE( ratio_t x,ratio_t y)
{
    //return !(x.num/x.den) <= (y.num/y.den)?1:0;
    return DLE(  x.num/x.den ,   y.num/y.den );    
}
int ratioGT( ratio_t x,ratio_t y)
{
    //return !(x.num/x.den) < (y.num/y.den)?1:0;
    return DGT(  x.num/x.den ,   y.num/y.den );     
}
int ratioGE( ratio_t x,ratio_t y)
{
    //return !(x.num/x.den) <= (y.num/y.den)?1:0;
    return DGE(  x.num/x.den ,   y.num/y.den );    
}
double ratio( ratio_t x )
{
  return x.num/x.den;
}
int gcd(intmax_t  m, intmax_t  n)
{
    intmax_t  tmp;
    while(m) 
    { 
        tmp = m; 
        m = n % m; 
        n = tmp; 
    }       
    return n;
}
int lcm(intmax_t  m, intmax_t  n)
{
    return m / gcd(m, n) * n;
}
 void ratioAdd( ratio_t *result, ratio_t x,ratio_t y)
{
    intmax_t  mcm = lcm ( x.den , y.den ) ;
    intmax_t  a = mcm / x.den * x.num ;
    intmax_t  b = mcm / y.den * y.num ;
    result->num = a+b;
    result->den = mcm;
}
void ratioSub( ratio_t *result, ratio_t x,ratio_t y)
{
    intmax_t  mcm = lcm ( x.den , y.den ) ;
    intmax_t  a = mcm / x.den * x.num ;
    intmax_t  b = mcm / y.den * y.num ;
    result->num = a-b;
    result->den = mcm;
}
void ratioMul( ratio_t *result, ratio_t x,ratio_t y)
{
    intmax_t  a = x.num * y.num ;
    intmax_t  b = x.den * y.den ;
    result->num = a;
    result->den = b;
}
void ratioDiv( ratio_t *result, ratio_t x,ratio_t y)
{
    intmax_t  temp ; // inverto la seconda e poi moltiplico
    temp = y.num ;
    y.num = y.den ;
    y.den = temp ; 

    intmax_t  a = x.num * y.num ;
    intmax_t  b = x.den * y.den ;

    result->num = a;
    result->den = b;
}



/**/


