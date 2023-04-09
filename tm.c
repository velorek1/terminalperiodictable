/* Module to create a milisecond timer
 * @author: velorek
 * Last modified: 10/08/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tm.h"

/* Milliseconds timer */
int timerC(NTIMER *mytimer1){
clock_t difference = 0;
long res;
 if (mytimer1->ticks == -1) return 0;
 if (mytimer1->ticks == 0){
    //First tick, set up values
    mytimer1->oldtime = clock();
    mytimer1->ticks = 1;
    return 1;
  } else{
    //subsequent ticks
    difference =  clock() - mytimer1->oldtime;
    res = difference * 1000 / CLOCKS_PER_SEC;
    if (res < mytimer1->ms) {
      return 0;
    } else{
      mytimer1->oldtime = clock();
      mytimer1->ticks = mytimer1->ticks + 1;
      return 1;
    }
  }
}

void init_timer(NTIMER *mytimer1, int ms){
//Init routine
   mytimer1->ticks = 0;
   mytimer1->ms=ms;
}

void stop_timer(NTIMER *mytimer1){
//Init routine
   mytimer1->ticks=-1;
}
void resume_timer(NTIMER *mytimer1){
//Init routine
   mytimer1->ticks=0;
}
