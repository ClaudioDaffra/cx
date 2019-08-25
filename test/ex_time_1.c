
#include "../lib/time.h"
#include <stdio.h>

/*
    cl  lib\time.c test\ex_time_1.c /Fex.exe /WX
    gcc lib\time.c test\ex_time_1.c -o x.exe -Wall -Wextra -pedantic
    gcc lib/time.c test/ex_time_1.c -o x.exe -Wall -Wextra -pedantic    
*/

int main (void)
{
  time_t    time;
  date_t   date ;

  timeNow(time) ;
  date = dateNow (time );

//

    printf ( "\n anno   %d " , timeYear(date) ) ;
    printf ( "\n mese   %d " , timeMonth(date) ) ;
    printf ( "\n giorno  %d ", timeDayOfWeek(date) ) ;
    printf ( "\n giorno  %d ", timeDayOfYear(date) ) ;
    printf ( "\n giorno  %s ", timeDayOfWeekStrC(date) ) ;   
    printf ( "\n ora solare  %d ", timeIsDayLight(date) ) ;      
    //
    printf ( "\n ora      %d " , timeHour(date) ) ;
    printf ( "\n minuti   %d " , timeMin(date) ) ;
    printf ( "\n secondi  %d " , timeSec(date) ) ; 
    //    
    printf ( "\n leap   %d " , timeIsLeap(date) ) ; 
    printf ( "\n ora12 %d AM %d PM %d\n" , timeHour12(date),timeIsAM(date),timeIsPM(date) ) ; 
 
// 
    date_t   dateGM ;
    
    dateGM  = timeGM(time) ;
    
    printf ( "\n ora GM     %d \n" , timeGMHour(dateGM,+1) ) ;
    
//

    clock_t start ;
    clock_t stop ;
    clock_t c ;
    
    clockNow(start) ;

    for(int i=0;i<10000;i++)
        for(int j=0;j<10000;j++)

    clockNow(stop) ;
    
    c = stop - start ;
    
    printf (
    "\ncomputation \nclick/%ld \nmicroS/%.0f \nmilliS/%.0f \nSec/%.0f \nMin/%.0f \nHour/%.0f.\n",
     c,clockMicroSec(c),clockMilliSec(c),clockSec(c),clockMin(c),clockHour(c) 
    ) ;

//
  
  printf ("\n");
  return 0;
}

