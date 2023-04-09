#include "global.h"
#include "rterm.h"
#include "time.h"
int _animation(){ 
                 time_t  mytime = time(NULL);
                char   *time_str = ctime(&mytime);

     		//Write char to screen raw to make title animation
     		get_terminal_dimensions(&new_rows,&new_columns);
    		centerX = ((new_columns) / 2) - (strlen(titlemsg) /2);
      		gotoxy(centerX+1, 1);
      		outputcolor(F_WHITE, B_BLACK);
      		printf("%s\n", titlemsg);  //unicode
     		gotoxy(centerX+animation+1, 1);
      		outputcolor(F_WHITE, B_YELLOW);
      		printf("%c\n", titlemsg[animation]);  //unicode
     		animation++;
                time_str[strlen(time_str) - 1] = '\0';
               //display system time
	       if (screen1 != NULL) 
		   write_str(screen1,12, 2, time_str,F_BLACK, B_WHITE,1);
     		if (animation == strlen(titlemsg)) {
	     		animation = 0;
             		gotoxy(centerX+1, 1);
             		outputcolor(F_WHITE, B_CYAN);
             		//printf("%s\n", titlemsg);  //unicode 
	     	}
		//return a signal if screen size changes
		if (new_rows != old_rows || new_columns != old_columns)
		  return -1;
		else return 0;
}
