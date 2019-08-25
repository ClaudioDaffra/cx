
#include "time.h"

const char * stimeWeekDay[] = 
{ 
    "Sunday"    , "Monday"      ,
    "Tuesday"   , "Wednesday"   ,
    "Thursday"  , "Friday"      , "Saturday"
};


// ............................................... timeNow
void timeNow_(time_t* t)
{
  time(t);     
}

// ............................................... timeIsLeap
int timeIsLeap(date_t date)  
{  
    int year = timeYear(date);
    
    if (year % 400 == 0)  return 1;  
    if (year % 100 == 0)  return 0;  
    if (year % 4   == 0)  return 1;  
    
    return 0;  
}


/**/


 