#ifndef cdTime
#define cdTime 

#include <stdio.h>    
#include <time.h>     

//struct tm {
//   int date_tec;       /* seconds,  range 0 to 59          */
//   int tm_min;         /* minutes, range 0 to 59           */
//   int tm_hour;        /* hours, range 0 to 23             */
//   int tm_mday;        /* day of the month, range 1 to 31  */
//   int tm_mon;         /* month, range 0 to 11             */
//   int tm_year;        /* The number of years since 1900   */
//   int tm_wday;        /* day of the week, range 0 to 6    */
//   int tm_yday;        /* day in the year, range 0 to 365  */
//   int tm_isdst;       /* daylight saving time             */
//};

extern const char * stimeWeekDay[] ;

typedef struct tm* date_t ;

#define timeSec(t)              t->tm_sec
#define timeMin(t)              t->tm_min
#define timeHour(t)             t->tm_hour
#define timeDayOfMonth(t)       t->tm_mday
#define timeMonth(t)            (t->tm_mon+1)
#define timeYear(t)             (t->tm_year+1900) 
#define timeDayOfWeek(t)        t->tm_mday
#define timeDayOfWeekStrC(t)    stimeWeekDay[t->tm_wday]
#define timeDayOfYear(t)        t->tm_yday
#define timeIsDayLight(t)       t->tm_isdst 
#define timeMin(t)              t->tm_min 
#define timesec(t)              t->tm_sec 

void    timeNow_    (time_t* t)    ;
int     timeIsLeap  (date_t date)  ;

#define timeNow(T)  timeNow_(&T)
#define dateNow(T)  localtime(&T)

#define timeHour12(T)   ((T->tm_hour)>12?(T->tm_hour-12):T->tm_hour)
#define timeIsAM(T)     ((T->tm_hour)< 12?1:0)
#define timeIsPM(T)     ((T->tm_hour)>=12?1:0)

//

#define clockNow(C)    (C=clock())

#define clockMicroSec(C)    (((float)C)/CLOCKS_PER_SEC*1000000)
#define clockMilliSec(C)    (((float)C)/CLOCKS_PER_SEC*1000)
#define clockSec(C)         (((float)C)/CLOCKS_PER_SEC)
#define clockMin(C)         (((float)C)/CLOCKS_PER_SEC/60)
#define clockHour(C)        (((float)C)/CLOCKS_PER_SEC/60/60)

//

#define timeGM(T)           gmtime(&T)
#define timeGMHour(T,GM)    ((((T)->tm_hour+(GM))%24) + ((T)->tm_isdst) )

#endif

/**/

