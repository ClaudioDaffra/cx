#ifndef cdRatio
#define cdRatio

#include <inttypes.h>

typedef struct ratio_s
{
    intmax_t num ;
    intmax_t den ;
} ratio_t ;

int ratioEQ( ratio_t x,ratio_t y);
int ratioNE( ratio_t x,ratio_t y);
int ratioLT( ratio_t x,ratio_t y);
int ratioLE( ratio_t x,ratio_t y);
int ratioGT( ratio_t x,ratio_t y);
int ratioGE( ratio_t x,ratio_t y);
double ratio( ratio_t x );
int gcd(intmax_t m, intmax_t n);
int lcm(intmax_t m, intmax_t n);
void ratioAdd( ratio_t *result, ratio_t x,ratio_t y);
void ratioSub( ratio_t *result, ratio_t x,ratio_t y);
void ratioMul( ratio_t *result, ratio_t x,ratio_t y);
void ratioDiv( ratio_t *result, ratio_t x,ratio_t y);

/*
ratio_t octo    ;
ratio_t zepto   ;
*/
ratio_t atto    ;
ratio_t femto   ;
ratio_t pico    ;
ratio_t nano    ;
ratio_t micro   ;
ratio_t milli   ;
ratio_t centi   ;
ratio_t deci    ;
ratio_t deca    ;
ratio_t hecto   ;
ratio_t kilo    ;
ratio_t mega    ;
ratio_t giga    ;
ratio_t tera    ;
ratio_t peta    ;
ratio_t exa     ;
/*
ratio_t zetta	;
ratio_t yotta   ;
*/

#endif


/**/



