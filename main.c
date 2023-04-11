/*
======================================================================
PROGRAM Cli Periodic Table - A showcase of Lynx Terminal TUI library.
@author : Velorek
@version : 1.0
Last modified : 08/04/2023 
======================================================================*/

/*====================================================================*/
/* COMPILER DIRECTIVES AND INCLUDES                                   */
/*====================================================================*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "rterm.h"
#include "scbuf.h"
#include "keyb.h"
#include "about.h"
#include "tm.h"
#include "ui.h"
#include "listbox.h"
#include "global.h"
#include "string.h"
#include "ctype.h"
#define MAX_LINE_LENGTH 1000
/*====================================================================*/
/* GLOBAL VARIABLES */
/*====================================================================*/

LISTCHOICE *listBox1 = NULL;
SCREENCELL *screen1=NULL;
SCREENCELL *screen2=NULL;
SCREENCELL *screen3=NULL;
NTIMER timer1;
NTIMER timer2;
NTIMER timer3;
SCROLLDATA scrollData;
BOOL blocked = FALSE;
int lastX1=0, lastY1=0, lastX2=0, lastY2=0;
int currentPointer = 0, oldPointer=0, oldElement=0, currentDirection = 0;
size_t animation = 0;
int centerX = 0;
int     status = 0;
char titlemsg[18] = "|PERIODIC TABLE|";
char elementText[MAXTEXT];
int table[162] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 1, 1, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 0, 0,
    0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 0, 0};

char initials[NUMELEMENTS][3] = {
"H", "Li", "Na", "K", "Rb", "Cs", "Fr",
"Be", "Mg", "Ca", "Sr", "Ba", "Ra", "Sc",
"Y", "La", "Ac", "Ti", "Zr", "Hf", "Rf",
"Ce", "Th", "V", "Nb", "Ta", "Db", "Pr",
"Pa", "Cr", "Mo", "W", "Sg", "Nd", "U",
"Mn", "Tc", "Re", "Bh", "Pm", "Np", "Fe",
"Ru", "Os", "Hs", "Sm", "Pu", "Co", "Rh",
"Ir", "Mt", "Eu", "Am", "Ni", "Pd", "Pt",
"Ds", "Gd", "Cm", "Cu", "Ag", "Au", "Rg",
"Tb", "Bk", "Zn", "Cd", "Hg", "Cn", "Dy",
"Cf", "B", "Al", "Ga", "In", "Tl", "Nh",
"Ho", "Es", "C", "Si", "Ge", "Sn", "Pb",
"Fl", "Er", "Fm", "Ni", "P", "As", "Sb",
"Bi", "Mc", "Tm", "Md", "O", "S", "Se",
"Te", "Po", "Lv", "Yb", "No", "F", "Cl",
"Br", "I", "At", "Ts", "Lu", "Lr", "He",
"Ne", "Ar", "Kr", "Xe", "Rn", "Og" 	
};

char atomicNumber[NUMELEMENTS][4] = {
"1", "3", "11", "19", "37", "55", "87",
"4", "12", "20", "38", "56", "88", "21",
"39", "57", "89", "22", "40", "72", "104",
"58", "90", "23", "41", "73", "105", "59",
"91", "24", "42", "74", "106", "60", "92",
"25", "43", "75", "107", "61", "93", "26",
"44", "76", "108", "62", "94", "27", "45",
"77", "109", "63", "95", "28", "46", "78",
"110", "64", "96", "29", "47", "79", "111",
"65", "97", "30", "48", "80", "112", "66",
"98", "5", "13", "31", "49", "81", "113",
"67", "99", "6", "14", "32", "50", "82",
"114", "68", "100", "7", "15", "33", "51",
"83", "115", "59", "101", "8", "16", "34",
"52", "84", "116", "70", "102", "9", "17",
"35", "53", "85", "117", "71", "103", "2",
"10", "18", "35", "54", "85", "118"};

char elementNames[NUMELEMENTS][MAXLINE] = {
    "Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon", "Nitrogen",
    "Oxygen", "Fluorine", "Neon", "Sodium", "Magnesium", "Aluminum", "Silicon",
    "Phosphorus", "Sulfur", "Chlorine", "Argon", "Potassium", "Calcium", "Scandium",
    "Titanium", "Vanadium", "Chromium", "Manganese", "Iron", "Cobalt", "Nickel",
    "Copper", "Zinc", "Gallium", "Germanium", "Arsenic", "Selenium", "Bromine",
    "Krypton", "Rubidium", "Strontium", "Yttrium", "Zirconium", "Niobium", "Molybdenum",
    "Technetium", "Ruthenium", "Rhodium", "Palladium", "Silver", "Cadmium", "Indium",
    "Tin", "Antimony", "Tellurium", "Iodine", "Xenon", "Cesium", "Barium", "Lanthanum",
    "Cerium", "Praseodymium", "Neodymium", "Promethium", "Samarium", "Europium",
    "Gadolinium", "Terbium", "Dysprosium", "Holmium", "Erbium", "Thulium", "Ytterbium",
    "Lutetium", "Hafnium", "Tantalum", "Tungsten", "Rhenium", "Osmium", "Iridium",
    "Platinum", "Gold", "Mercury", "Thallium", "Lead", "Bismuth", "Polonium",
    "Astatine", "Radon", "Francium", "Radium", "Actinium", "Thorium", "Protactinium",
    "Uranium", "Neptunium", "Plutonium", "Americium", "Curium", "Berkelium",
    "Californium", "Einsteinium", "Fermium", "Mendelevium", "Nobelium", "Lawrencium",
    "Rutherfordium", "Dubnium", "Seaborgium", "Bohrium", "Hassium", "Meitnerium", "Darmstadtium", 
    "Roentgenium", "Copernicium", "Nihonium", "Flerovium", "Moscovium", "Livermorium", "Tennessine", "Oganesson"
};
char nameinColumns[NUMELEMENTS][MAXLINE] = {
    "Hydrogen", "Lithium", "Sodium", "Potassium", "Rubidium", "Cesium", "Francium",
    "Beryllium", "Magnesium", "Calcium", "Strontium", "Barium", "Radium", "Scandium",
    "Yttrium", "Lanthanum", "Actinium", "Titanium", "Zirconium", "Hafnium", "Rutherfordium",
    "Cerium", "Thorium", "Vanadium", "Niobium", "Tantalum", "Dubnium", "Praseodymium",
    "Protactinium", "Chromium", "Molybdenum", "Tungsten", "Seaborgium", "Neodymium", "Uranium",
    "Manganese", "Technetium", "Rhenium", "Bohrium", "Promethium", "Neptunium", "Iron",
    "Ruthenium", "Osmium", "Hassium", "Samarium", "Plutonium", "Cobalt", "Rhodium",
    "Iridium", "Meitnerium", "Europium", "Americium", "Nickel", "Palladium", "Platinum",
    "Darmstadtium", "Gadolinium", "Curium", "Copper", "Silver", "Gold", "Roentgenium",
    "Terbium", "Berkelium", "Zinc", "Cadmium", "Mercury", "Copernicium", "Dysprosium",
    "Californium", "Boron", "Aluminum", "Gallium", "Indium", "Thallium", "Nihonium",
    "Holmium", "Einsteinium", "Carbon", "Silicon", "Germanium", "Tin", "Lead",
    "Flerovium", "Erbium", "Fermium", "Nitrogen", "Phosphorus", "Arsenic", "Antimony",
    "Bismuth", "Moscovium", "Thulium", "Mendelevium", "Oxygen", "Sulfur", "Selenium",
    "Tellurium", "Polonium", "Livermorium", "Ytterbium", "Nobelium", "Fluorine", "Chlorine",
    "Bromine", "Iodine", "Astatine", "Tennessine", "Lutetium", "Lawrencium", "Helium",
    "Neon", "Argon", "Krypton", "Xenon", "Radon", "Oganesson"
};
char colorKey[10][MAXLINE] = {
"Unknown Properties    ",
"Alkaline Metals       ",
"Alkaline Earth Metals ",
"Transition Metals     ",
"Post-transition Metals",
"Metalloids            ",
"Reactive non-metals   ",
"Nobel Gases           ",
"Lanthanides           ", 
"Actinides             "
};
//Check function for colour explanation
int colorScheme[NUMELEMENTS] = {
6, 1, 1, 1, 1, 1, 1,
2, 2, 2, 2, 2, 2, 3,
3, 8, 9, 3, 3, 3, 3,
8, 9, 3, 3, 3, 3, 8,
9, 3, 3, 3, 3, 8, 9,
3, 3, 3, 3, 8, 9, 3,
3, 3, 3, 8, 9, 3, 3,
3, 0, 8, 9, 3, 3, 3,
0, 8, 9, 3, 3, 3, 0,
8, 9, 3, 3, 3, 0, 8,
9, 6, 4, 4, 4, 4, 0,
8, 9, 6, 5, 5, 4, 4,
0, 8, 9, 6, 6, 5, 5,
4, 0, 8, 9, 6, 6, 6,
5, 4, 0, 8, 9, 6, 6,
6, 6, 4, 0, 8, 9, 7,
7, 7, 7, 7, 7, 0};

char menu[NUMOPTION][MAXLINE] = {OPTION1, OPTION2,OPTION3, OPTION4, OPTION5, OPTION6}; 
char help[HELPLINES][MAXLINE] = {HELP0, 
	HELP1,HELP2, HELP3, 
	HELP4, HELP5, HELP6, 
	HELP7, HELP8, HELP9,
	HELP10, HELP11, HELP12,
	HELP13, HELP14, HELP15,
	HELP16, HELP17, HELP18,
	HELP19, HELP20
     }; 
char aboutMSG[8][MAXLINE] = {ABOUT0, ABOUT1, ABOUT2, ABOUT3, ABOUT4, ABOUT5, ABOUT6, ABOUT7};
char catInfo[11][MAXTEXT] = {INFO0, INFO1, INFO2, INFO3, INFO4, INFO5, INFO6, INFO7, INFO8,INFO9};

typedef struct{
    unsigned x1,y1;
    unsigned size;
    int color;
    int atomicNumber;
    BOOL is_selected;    
    BOOL is_drawn;
} TILE;

//VLINES *edBuf1=NULL; //Buffer vector of lines(1022 chars)
//VLINES tempLine;

TILE periodictable[TABLESIZE];
BOOL displaytable = TRUE;

int     new_rows = 0, new_columns = 0, old_rows = 0, old_columns = 0;	// Terminal dimensions

/*====================================================================*/
/* PROTOTYPES OF FUNCTIONS                                            */
/*====================================================================*/

//Display prototypes
int       displayColorKey();
int       displayHelp();
int       displayList();
int       displayInfo();
int       displayText(SCREENCELL *aux, char *text);
int       displayAbout();
int       displaySearch();
void      selectItem(int direction);
void      resetScrollData();
//void    credits();
void      draw_screen();
void      draw_table(int raw);
int       special_keys(char ch);
void      getColorScheme (int index, int *bcol, int *fcol, BOOL simple);
void      option_menu();
int       getElementfromFile(char *text, int elementNumber);

//Timers
void     _resizeScreen();


/*====================================================================*/
/* MAIN PROGRAM - CODE                                                */
/*====================================================================*/


int main() {
  char    ch=0; 
  int     keypressed = 0;
  /*------------------------INITIAL VALUES----------------------------*/
   setlocale(LC_ALL, ""); //set right unicode setting
   init_term();
   get_terminal_dimensions(&new_rows,&new_columns);
   
    init_timer(&timer1,150);
    init_timer(&timer2,150);
    init_timer(&timer3,150);
    //Init Terminal
    old_rows=new_rows;
    old_columns=new_columns;
    create_screen(&screen1);
    centerX = ((new_columns) / 2) - (strlen(titlemsg) /2);
    draw_screen();
    //Check whether screen is big enough; if not, display error.    
    if ((new_columns < MINWIDTH) || (new_rows < MINHEIGHT)) {
         draw_window(screen1, (new_columns/2) - 13 , (new_rows/2) -2 , (new_columns/2) + 13, (new_rows/2) +2, B_WHITE, F_BLACK, B_RED, 1,1,1,0);
         write_str(screen1, (new_columns/2) - 12, (new_rows/2)-2, WINERRMSGTL, B_RED, F_WHITE,0);
         write_str(screen1, (new_columns/2) - 12, (new_rows/2)-1, WINERRMSGLN1, B_WHITE, F_BLACK,0);
         write_str(screen1, (new_columns/2) - 12, (new_rows/2), WINERRMSGLN2, B_WHITE, F_BLACK,0);
         write_str(screen1, (new_columns/2) - 12, (new_rows/2)+1, WINERRMSGLN3, B_WHITE, F_BLACK,0);	
	 displaytable=FALSE;
	 old_rows = new_rows;
         old_columns = new_columns;
     } 
    if (displaytable==TRUE) draw_table(1);
    for (int i=0; i<TABLESIZE;i++){ 
      periodictable[i].is_selected = FALSE;
    }
    dump_screen(screen1);
    resetch();
     do{    
         keypressed = kbhit();
          

         if (keypressed == TRUE) 
          ch=readch();
           if (special_keys(ch) == ENDSIGNAL) status = ENDSIGNAL;	
                
	 if (timerC(&timer1) == TRUE){
	      //Screen update
              _resizeScreen();
	      ch=0;
           }
          if (timerC(&timer2) == TRUE){
	      //Animation in global.c
              _animation();
           }
         // write_num(screen1,1,5,currentPointer,B_GREEN,F_WHITE,1);
         // write_num(screen1,1,6,oldPointer,B_RED,F_WHITE,1);
         // write_num(screen1,1,7,periodictable[oldPointer].atomicNumber,B_CYAN,F_WHITE,1);
        if (displaytable){
	  if (ch == K_ENTER) {
	  //Tile info
	     resetScrollData();
             memset(elementText, 0, sizeof(elementText));
             getElementfromFile(elementText,periodictable[oldPointer].atomicNumber);
             displayText(screen1, elementText);
	  }
	  //Failsafe keys for terminal compatibility
          if (ch == K_CTRL_C) status = ENDSIGNAL;
          if (ch == K_CTRL_L) option_menu();
          if (ch == K_CTRL_B) displayList();
          if (ch == K_CTRL_A) displayAbout();
          if (ch == K_CTRL_S) displaySearch();
          if (ch == K_CTRL_H) displayHelp();

          if (ch == 'x') status = ENDSIGNAL;
          if (ch == 'k') displayColorKey();
	}
          if (ch == 's') {
		  //Hide-show table even if screen size is not big enough
		  if (blocked == FALSE) {
			     blocked = TRUE;
			     displaytable = FALSE;
			     draw_screen();
			     dump_screen(screen1);
		           }  
			  else{ 
				  displaytable = TRUE;
				  blocked= FALSE;
				  draw_screen();
				  draw_table(0);
			          dump_screen(screen1);
			      }
		         }
       } while (status != ENDSIGNAL);    
    if (screen1 != NULL) deleteList(&screen1);
    if (listBox1 != NULL) removeList(&listBox1);
    //restore terminal
    close_term();
    return 0;
}
void getColorScheme (int index, int *bcol, int *fcol, BOOL simple){
/* TEN groups
0 Unknown Properties - Black/white
1 Alkaline Metals - Green/white
2 Alkaline Earth Metals - Red
3 Transition Metals - Cyan/white
4 Post-transition Metals - Green/black
5 Metalloids - Yellow/black
6 Reactive non-metals - Blue
7 Nobel Gases - Magenta
8 Lanthanides - Cyan/black
9 Actinides - Yellow/white
*/
int getColorFrom=0;
if (!simple){
	getColorFrom = colorScheme[index];
}
else
{
       getColorFrom = index;
}

     switch (getColorFrom){
     case 0:
	     *bcol = B_BLACK;
	     *fcol = F_WHITE;
	     break;
     case 1:
	     *bcol = B_GREEN;
	     *fcol = F_WHITE;
	     break;
     case 2:
	     *bcol = B_RED;
	     *fcol = F_WHITE;
	     break;
     case 3:
	     *bcol = B_CYAN;
	     *fcol = F_WHITE;
	     break;
     case 4:
	     *bcol = B_GREEN;
	     *fcol = F_BLACK;
	     break;
     case 5:
	     *bcol = B_YELLOW;
	     *fcol = F_BLACK;
	     break;
     case 6:
	     *bcol = B_BLUE;
	     *fcol = F_WHITE;
	     break;
     case 7:
	     *bcol = B_MAGENTA;
	     *fcol = F_WHITE;
	     break;
     case 8:
	     *bcol = B_CYAN;
	     *fcol = F_BLACK;
	     break;
     case 9:
	     *bcol = B_YELLOW;
	     *fcol = F_WHITE;
	     break;
     
  }
}

void resetTable(){
int bcol=0, fcol=0;
//reset table values
  write_str(screen1,0,3,"                           ", B_BLACK, F_BLACK,FALSE); 

 //Clear previous tile
if(currentPointer != oldPointer) {
       getColorScheme(oldElement, &bcol, &fcol,FALSE);
       draw_window(screen1, lastX1 ,lastY1 , lastX2 , lastY2, B_WHITE, F_BLACK, B_BLACK, 1,0,0,0);
       write_str(screen1,lastX1+1,lastY1,atomicNumber[oldElement],bcol, fcol,FALSE);             
       write_str(screen1,lastX1+2,lastY1+1,initials[oldElement], B_WHITE, F_BLACK,FALSE);     
      periodictable[oldPointer].is_selected = FALSE;
}


  for (int i=0; i< TABLESIZE; i++){
        periodictable[i].is_selected = FALSE;
  }
  lastX1=0, lastY1=0, lastX2=0, lastY2=0;
  currentPointer = 0, oldPointer=0, oldElement=0, currentDirection = 0;   

}
void selectItem(int direction){
int i=0;
int bcol=0,fcol=0;

//Unselect previous tile
if(currentPointer != oldPointer) {
       getColorScheme(oldElement, &bcol, &fcol,FALSE);
       draw_window(screen1, lastX1 ,lastY1 , lastX2 , lastY2, B_WHITE, F_BLACK, B_BLACK, 1,0,0,0);
       write_str(screen1,lastX1+1,lastY1,atomicNumber[oldElement],bcol, fcol,FALSE);             
       write_str(screen1,lastX1+2,lastY1+1,initials[oldElement], B_WHITE, F_BLACK,FALSE);     
      periodictable[oldPointer].is_selected = FALSE;
}

//Go forward down key
if (direction == 1) {
for (i=currentPointer; i<TABLESIZE;i++){
    	if (periodictable[i].is_drawn == TRUE) {
          periodictable[i].is_selected = TRUE;
	  currentPointer = i;
	  currentPointer++;
	break;
    }
   	
}
}

//Go RIGHT key
if (direction == 2) {
for (i=currentPointer; i<TABLESIZE;i++){
    	if (periodictable[i].is_drawn == TRUE) {
          periodictable[i].is_selected = TRUE;
	  currentPointer = i;
	  currentPointer = currentPointer + 9;
	break;
    }
   	
}
}

//Go LEFT key
if (direction == -2) {
for (i=currentPointer; i>=0;i--){
    	if (periodictable[i].is_drawn == TRUE) {
        periodictable[i].is_selected = TRUE;
	currentPointer = i;
	currentPointer = currentPointer - 9;
	break;
    }
}

}

//Go backwards up key
if (direction == -1) {
for (i=currentPointer; i>=0;i--){
    	if (periodictable[i].is_drawn == TRUE) {
        periodictable[i].is_selected = TRUE;
	currentPointer = i;
	currentPointer--;
	break;
    }
}

}
//If table is active always point to first element when you reach it
  if (currentPointer == -1) {currentPointer=1; oldPointer =1;}
}
void draw_table(int raw){
//draw elements in the periodic table
int bcol, fcol;
int track_columns = 0;
int track_rows = 0;
int i=0;
//Shifty helps to separate the last 2 rows of the table
int shifty =0;
int centerTableX=(new_columns/2) - 54;
int counterElement=0;
int counterAtomic=0;

//Map elements and store atomic Numbers in position
for (i=0; i<TABLESIZE;i++)
 {
    periodictable[i].is_drawn = table[i];
    if (periodictable[i].is_drawn) { 
	    periodictable[i].atomicNumber = atoi(atomicNumber[counterAtomic]);
            counterAtomic++;
    }
 }

for (i=0; i<TABLESIZE;i++)
{ 
    if (i % 9 == 0 && i != 0) track_columns=track_columns+6;	
    if (track_rows == 9) track_rows=0;
    if (track_rows > 6) shifty=2; 
    else shifty = 0;

    if (periodictable[i].is_drawn == TRUE){
       if (periodictable[i].is_selected == FALSE && raw != 2) {
  	  draw_window(screen1, centerTableX+track_columns , 5+(3*track_rows)+shifty , centerTableX+5+track_columns , 7+(3*track_rows)+shifty, B_WHITE, F_BLACK, B_BLACK, 1,0,1,raw);
          getColorScheme(counterElement, &bcol, &fcol,FALSE);
          write_str(screen1,centerTableX+track_columns+1,5+(3*track_rows)+shifty,atomicNumber[counterElement], bcol, fcol,FALSE);             
         write_str(screen1,centerTableX+track_columns+2,5+(3*track_rows)+shifty+1,initials[counterElement], B_WHITE, F_BLACK,FALSE);             
       } else{
	if (periodictable[i].is_selected == TRUE) {
          //Safe coordinates of selected tile to late un-select next time from selectItem
          //select new tile and save coordinates; save element indeces too
	  draw_window(screen1, centerTableX+track_columns , 5+(3*track_rows)+shifty , centerTableX+5+track_columns , 7+(3*track_rows)+shifty, B_BLUE, F_WHITE, B_BLACK, 1,0,0,0);
          write_str(screen1,centerTableX+track_columns+1,5+(3*track_rows)+shifty,atomicNumber[counterElement], B_WHITE, F_BLACK,FALSE);             
          write_str(screen1,centerTableX+track_columns+2,5+(3*track_rows)+shifty+1,initials[counterElement], B_BLUE, F_WHITE,FALSE);     
 	  lastX1 = centerTableX+track_columns;
          lastY1 = 5+(3*track_rows)+shifty;
	  lastX2 = centerTableX+5+track_columns;
	  lastY2 = 7+(3*track_rows)+shifty;
	  oldPointer = i;
	  oldElement = counterElement;
          write_str(screen1,0,3,"                           ", B_BLACK, F_BLACK,FALSE); 
          write_str(screen1,0,3,nameinColumns[counterElement], B_BLACK, F_YELLOW,FALSE); 
          dump_screen(screen1);
	}
       }
	counterElement++;
       
    }    	
    track_rows++;
}
}

void draw_screen(){
//This function draws the base screen
int i=0;
if (screen1 != NULL) deleteList(&screen1);
     create_screen(&screen1);
     screen_color(screen1, B_BLUE, F_WHITE, UNICODEBAR);
     //Top-Bar
     for (i=0;i<new_columns;i++){
          write_ch(screen1, i,1, UNICODEBAR, B_BLUE, F_BLACK,FALSE);
          write_ch(screen1, i,2, 0x20, B_WHITE, F_WHITE,FALSE);
          write_ch(screen1, i,3, 0x20, B_BLACK, F_WHITE,FALSE);
          write_ch(screen1, i,new_rows, 0x20, B_WHITE, F_BLUE,FALSE);
     }
     write_str(screen1,centerX,1,titlemsg, B_BLACK, F_WHITE,FALSE);             
     write_str(screen1,1,new_rows,STATUSMSG1, B_WHITE, F_BLACK,FALSE);             
     write_str(screen1,1,2,"OPTIONS | ", B_WHITE, F_BLACK,FALSE);             
     write_str(screen1,0,new_rows-1,"^v<> NAVIGATE TABLE | ENTER: INFO DIALOG | K: COLOR KEY", B_BLUE, F_WHITE,FALSE);             

     dump_screen(screen1);

}

void _resizeScreen(void){
//This timer checks wether screen size is big enough to display table and
//resizes screen accordingly when it changes.
     if (new_rows != old_rows || new_columns != old_columns)
	
               {
		   //Refresh screen size buffers if terminal dimension changes
     		    get_terminal_dimensions(&new_rows,&new_columns);
    		    if (screen1 != NULL) deleteList(&screen1);
                    create_screen(&screen1);
    		    centerX = ((new_columns) / 2) - (strlen(titlemsg) /2);
    		    draw_screen();
		    if (displaytable == TRUE && !blocked) draw_table(0);
		    old_rows = new_rows;
		    old_columns = new_columns;
                    resetTable();
		    dump_screen(screen1);
	     	if ((new_columns < MINWIDTH) || (new_rows < MINHEIGHT)) {
		    //Window size is too small display error message
		    draw_screen();
         	    draw_window(screen1, (new_columns/2) - 13 , (new_rows/2) -2 , (new_columns/2) + 13, (new_rows/2) +2, B_WHITE, F_BLACK, B_RED, 1,1,1,0);
         	    write_str(screen1, (new_columns/2) - 12, (new_rows/2)-2, WINERRMSGTL, B_RED, F_WHITE,0);
         	    write_str(screen1, (new_columns/2) - 12, (new_rows/2)-1, WINERRMSGLN1, B_WHITE, F_BLACK,0);
         	    write_str(screen1, (new_columns/2) - 12, (new_rows/2), WINERRMSGLN2, B_WHITE, F_BLACK,0);
         	    write_str(screen1, (new_columns/2) - 12, (new_rows/2)+1, WINERRMSGLN3, B_WHITE, F_BLACK,0);
		    dump_screen(screen1);
	 	    displaytable=FALSE;
	 	    old_rows = new_rows;
         	    old_columns = new_columns;
     		} else {
	            displaytable = TRUE;
		    if (displaytable == TRUE && !blocked) draw_table(0);
    		}
                  dump_screen(screen1);
             } 
}
void addItems(LISTCHOICE ** listBox1, char textarray[][MAXLINE], int rows) {
//Load items into the list.  
  //if (*listBox1 != NULL) removeList(listBox1);
     for (int h=0; h<rows; h++){
      //*ch = textarray[h];
      *listBox1 = addatend(*listBox1, newitem(textarray[h]));
  }
}

int displayHelp(){
   char ch=0;
   resetScrollData();
   scrollData.selectorLimit=(26*2)-1;    //No. of chars per item display
   create_screen(&screen2);
   copy_screen(screen2,screen1);
   draw_window(screen1, (new_columns/2)-26,(new_rows/2)-8,(new_columns/2)+26,(new_rows)/2+8,B_CYAN,F_BLACK,B_WHITE,1,0,1,0);
   write_str(screen1, (new_columns/2)-1,(new_rows/2)+7,"[OK]",B_WHITE,F_BLACK,1);
   dump_screen(screen1); 
   addItems(&listBox1, help, HELPLINES);
   if (listBox1 != NULL) ch = listBox(listBox1, (new_columns/2)-24, (new_rows/2)-7, &scrollData, B_CYAN, F_BLACK, B_CYAN,F_WHITE, 14, LOCKED);
   copy_screen(screen1,screen2);
   if (screen2 != NULL) deleteList(&screen2); 
   if (listBox1 != NULL) removeList(&listBox1);
   dump_screen(screen1); 
   return ch;
}

int displayAbout(){
   char ch=0;
   int i=0;
   int colAnimation=F_BLACK;
   int keypressed=0;
   resetScrollData();
   scrollData.selectorLimit=4;    //No. of chars per item display
   create_screen(&screen2);
   copy_screen(screen2,screen1);

   window(screen1, (new_columns/2)-28,(new_rows/2)-6,(new_columns/2)+27,(new_rows)/2+5,B_YELLOW,F_BLACK,B_WHITE,1,0,1);
    for (i=0; i<6; i++){
      write_str(screen1, (new_columns/2)-27,(new_rows/2)-5+i,aboutMSG[i],B_YELLOW,F_BLACK,0);
   }
      write_str(screen1, (new_columns/2)-25,(new_rows/2)+1,aboutMSG[6],B_YELLOW,F_BLACK,0);
      write_str(screen1, (new_columns/2)-25,(new_rows/2)+2,aboutMSG[7],B_YELLOW,F_BLACK,0);
   write_str(screen1, (new_columns/2)-1,(new_rows/2)+4,"[OK]",B_WHITE,F_BLACK,1);
   dump_screen(screen1); 
   if(kbhit() == 1) ch = readch();
   ch = 0;
  i=0;
  do {
      keypressed = kbhit();
      if (timerC(&timer3) == TRUE){
	   //About animation            
          write_str(screen1, (new_columns/2)-27,(new_rows/2)-5+i,aboutMSG[i],B_YELLOW,colAnimation,1);
	  i++;      
          if (i==6) {
		  i=0;
		  if (colAnimation == F_WHITE) colAnimation =F_BLACK;
		  else colAnimation = F_WHITE;
	  }
        if(_animation() == -1) break;
      }
      //Process keys
    if(keypressed == 1) {
        ch = readch();
        keypressed = 0;

        //Read special keys
        if (ch==K_ESCAPE) {
               break;
      
         }

    }  
    } while (ch!= K_ENTER);

   copy_screen(screen1,screen2);
   if (screen2 != NULL) deleteList(&screen2); 
   if (listBox1 != NULL) removeList(&listBox1);
   dump_screen(screen1); 
   return ch;
}


int displayColorKey(){
   //Color Key
   char ch=0;
   int bcol, fcol;
   resetScrollData();
   create_screen(&screen2);
   copy_screen(screen2,screen1);
   scrollData.selectorLimit=4;    //No. of chars per item display
   window(screen1,(new_columns/2)-11,(new_rows/2)-6,(new_columns/2)+12,(new_rows)/2+6, B_WHITE,F_BLACK, B_BLUE,1,1,1);
   for (int i=0; i<10; i++){
     getColorScheme(i, &bcol, &fcol,TRUE);
      write_str(screen1, (new_columns/2)-10,(new_rows/2)-5+i,colorKey[i],bcol,fcol,0);
   }
      write_str(screen1, (new_columns/2)-11,(new_rows/2)-7,"[+] COLOR KEY",B_BLUE,F_WHITE,0);
   dump_screen(screen1); 
   listBox1 = addatend(listBox1, newitem("[OK]"));
   if (listBox1 != NULL) ch = listBox(listBox1, (new_columns/2), (new_rows/2)+5, &scrollData, B_CYAN, F_BLACK, B_CYAN,F_WHITE, 1, LOCKED);
   copy_screen(screen1,screen2);
   if (screen2 != NULL) deleteList(&screen2); 
   if (listBox1 != NULL) removeList(&listBox1);
   dump_screen(screen1);
   return ch; 
}

int displayList(){
   char ch=0;
   resetScrollData();
   scrollData.selectorLimit=(14*2)-3;    //No. of chars per item display
   create_screen(&screen2);
   copy_screen(screen2,screen1);
   draw_window(screen1, (new_columns/2)-14,(new_rows/2)-12,(new_columns/2)+14,(new_rows)/2+12,B_WHITE,F_BLACK,B_CYAN,1,0,1,0);
   write_str(screen1, (new_columns/2)-9,(new_rows/2)+11,"Press [ESC] to close",B_CYAN,F_WHITE,1);
  // dump_screen(screen1); 
  // addItems(&listBox1, elementNames, NUMELEMENTS);
  // if (listBox1 != NULL) ch = listBox(listBox1, (new_columns/2)-11, (new_rows/2)-11, &scrollData, B_WHITE, F_BLACK, B_BLUE,F_WHITE, 22, LOCKED);
   do{
     resetScrollData();
     memset(elementText, 0, sizeof(elementText));
     scrollData.selectorLimit=(14*2)-3;    //No. of chars per item display
     addItems(&listBox1, elementNames, NUMELEMENTS);
     dump_screen(screen1); 
     if (listBox1 != NULL) ch = listBox(listBox1, (new_columns/2)-11, (new_rows/2)-11, &scrollData, B_WHITE, F_BLACK, B_BLUE,F_WHITE, 22, LOCKED);
     if (scrollData.itemIndex == -1) break;
     getElementfromFile(elementText,scrollData.itemIndex+1);
     displayText(screen2, elementText);

   } while (ch != 0x27); 
   copy_screen(screen1,screen2);
   if (screen2 != NULL) deleteList(&screen2); 
   if (listBox1 != NULL) removeList(&listBox1);
   dump_screen(screen1);
   return ch; 
}


int displayInfo(){
   char ch=0;
   //loop here to go back to menu after displaying text
   resetScrollData();
   scrollData.selectorLimit=(11*2);    //No. of chars per item display
   create_screen(&screen2);
   copy_screen(screen2,screen1);
   window(screen1,(new_columns/2)-11,(new_rows/2)-6,(new_columns/2)+12,(new_rows)/2+6, B_WHITE,F_BLACK, B_BLUE,1,0,1);
   write_str(screen1, (new_columns/2)-9,(new_rows/2)+5,"Press [ESC] to close",B_CYAN,F_WHITE,1);
   dump_screen(screen1); 
   do{
     resetScrollData();
     scrollData.selectorLimit=(11*2);    //No. of chars per item display
     dump_screen(screen1); 
     addItems(&listBox1, colorKey, 10);
   
    if (listBox1 != NULL) ch = listBox(listBox1, (new_columns/2)-9, (new_rows/2)-5, &scrollData, B_WHITE, F_BLACK, B_BLUE,F_WHITE, 10, LOCKED);
     if (scrollData.itemIndex == -1) break;
     displayText(screen2, catInfo[scrollData.itemIndex]);

   } while (ch != 0x27);
   copy_screen(screen1,screen2);
   if (screen2 != NULL) deleteList(&screen2); 
   if (listBox1 != NULL) removeList(&listBox1);
   dump_screen(screen1);
   return ch; 
}

int displayText(SCREENCELL *aux, char *text){
char lineStr[255];
int strPtr=0;
char ch=0;
int k=0;

strcpy(lineStr, "");

  if (listBox1 != NULL) removeList(&listBox1);
  create_screen(&screen3);
  copy_screen(screen3,aux);
  window(aux,(new_columns/2)-22,(new_rows/2)-7,(new_columns/2) + 22,(new_rows/2)+7,B_WHITE,F_BLUE,B_BLACK,1,0,1);
  window(aux,(new_columns/2)-21,(new_rows/2)-6,(new_columns/2) + 21,(new_rows/2)+6,B_WHITE,F_BLACK,B_BLUE,1,1,0);
  window(aux,(new_columns/2)-20,(new_rows/2)-5,(new_columns/2) + 20,(new_rows/2)+5,B_WHITE,F_WHITE,B_BLACK,0,0,0);
  write_str(aux, (new_columns/2)-22,(new_rows/2)-7,"[+] INFORMATION",B_BLUE,F_WHITE,1);
  write_str(aux, (new_columns/2)-1,(new_rows/2)+5,"[OK]",B_CYAN,F_WHITE,1);
  dump_screen(aux);
  resetScrollData();
  outputcolor(F_WHITE,B_BLACK);
  scrollData.selectorLimit=39;    //No. of chars per item displayed
  strcpy(lineStr,"");
  memset(lineStr, 0, sizeof(lineStr));
  strPtr=0;
  do{
    for (k=0; k<39; k++){
	  if (k==0 && text[strPtr]  == 0x20) strPtr++;
	  //remove unwanted chars
	  if (text[strPtr] != 0x10 && text[strPtr] != 0x0A && text[strPtr] != '\0') lineStr[k]=text[strPtr];
	  strPtr++;
	  if (text[strPtr] == '_') break;
    }
   lineStr[k]='\0';
   // make sure we don't split words
   if (strlen(lineStr) > 38){
     if (text[strPtr] !=0x20 || text[strPtr+1] !=0x20 || text[strPtr-1] !=0x20){
        for (k=38; k>0; k--){
                if (lineStr[k] == 0x20) break;
                lineStr[k]=0x20;
                strPtr--;
        }
       lineStr[k]='\0';
     }
   }
   listBox1 = addatend(listBox1, newitem(lineStr));
   strcpy(lineStr,"");
   memset(lineStr, 0, sizeof(lineStr));
  } while (text[strPtr] != '\0');

  scrollData.selectorLimit=39;    //No. of chars per item displayed
  if (listBox1 != NULL) ch = listBox(listBox1, (new_columns/2)-18, (new_rows/2)-5, &scrollData, B_WHITE, F_BLACK, B_WHITE,F_BLUE, 10, LOCKED);
  copy_screen(aux,screen3);
  if (screen3 != NULL) deleteList(&screen3); 
  if (listBox1 != NULL) removeList(&listBox1);
  dump_screen(aux);
  return ch;
}
int displaySearch(){
char texto[MAXLINE];
char lowercase[MAXLINE];
BOOL elementFound = FALSE;
int i=0, k=0;
char ch=0;
   create_screen(&screen2);
   copy_screen(screen2,screen1);
   window(screen1,(new_columns/2)-13,(new_rows/2)-1,(new_columns/2)+14,(new_rows)/2+1, B_BLUE,F_WHITE, B_BLUE,1,0,1);
   ch=textbox(screen1, (new_columns/2)-12,(new_rows/2),15, "Element: ", texto, B_BLUE,F_WHITE, F_WHITE,FALSE,LOCKED);
   dump_screen(screen1); 
   memset(lowercase, 0, sizeof(lowercase));
   strcpy(lowercase,"\0");
   for (i=0; i<NUMELEMENTS; i++){
    //convert both strings to lowercase
     for (k = 0; texto[k]; k++) {
      texto[k] = tolower(texto[k]);
     }	   
    
     strcpy(lowercase, elementNames[i]);
     for (k = 0; lowercase[k]; k++) {
      lowercase[k] = tolower(lowercase[k]);
     }	   
 
     if (strcmp(texto, lowercase) == 0){
 	     resetScrollData();
             memset(elementText, 0, sizeof(elementText));
             getElementfromFile(elementText,i+1);
             //write_num(screen1,1,1,i,B_BLACK, F_WHITE,1);
             //write_str(screen1,1,2,texto,B_BLACK, F_WHITE,1);
	     displayText(screen1, elementText);
             elementFound = TRUE;	     
        }

   strcpy(lowercase,"\0");
   } 
   if ((!elementFound) && (strlen(texto) >0) ){
      draw_window(screen1, (new_columns/2) - 13 , (new_rows/2) -2 , (new_columns/2) + 13, (new_rows/2) +2, B_WHITE, F_BLACK, B_RED, 1,1,1,0);
      write_str(screen1, (new_columns/2) - 12, (new_rows/2)-2, "[+] ERROR" , B_RED, F_WHITE,0);
      write_str(screen1, (new_columns/2) - 12, (new_rows/2), "    Element not found!", B_WHITE, F_BLACK,0);
      dump_screen(screen1); 
      resetScrollData();
      scrollData.selectorLimit=4;    //No. of chars per item display
      listBox1 = addatend(listBox1, newitem("[OK]"));
      if (listBox1 != NULL) ch = listBox(listBox1, (new_columns/2), (new_rows/2)+1, &scrollData, B_WHITE, F_BLACK, B_CYAN,F_WHITE, 1, LOCKED);
  }
   copy_screen(screen1,screen2);
   dump_screen(screen1); 
   if (screen2 != NULL) deleteList(&screen2); 
   if (listBox1 != NULL) removeList(&listBox1);
 
   return ch;
}
void resetScrollData(){
   scrollData.scrollActive=0;    //To know whether scroll is active or not.
   scrollData.scrollLimit=0;     //Last index for scroll.
   scrollData.listLength=0;      //Total no. of items in the list
   scrollData.currentListIndex=0;    //Pointer to new sublist of items when scrolling.
   scrollData.displayLimit=0;    //No. of elements to be displayed.
   scrollData.selectorLimit=15;    //No. of chars per item display
   scrollData.scrollDirection=0; //To keep track of scrolling Direction.
   scrollData.selector=0;        //Y++
   scrollData.wherex=0;
   scrollData.wherey=0;
   scrollData.backColor0=0;      //0 unselected; 1 selected
   scrollData.foreColor0=0;
   scrollData.backColor1=0;
   scrollData.foreColor1=0;
   scrollData.itemIndex=0; 
}

void option_menu(){
char ch=0;
   resetScrollData();
   create_screen(&screen2);
   copy_screen(screen2,screen1);
   write_str(screen1,0,2," OPTIONS ", B_BLUE, F_WHITE,TRUE);             
   addItems(&listBox1, menu, NUMOPTION);
   window(screen1, 0,3,16,10,B_BLUE,F_BLACK,B_BLACK,1,0,1);
   dump_screen(screen1);
   if (listBox1 != NULL) ch = listBox(listBox1, 2, 4, &scrollData, B_BLUE, F_WHITE, B_WHITE,F_BLACK, 6, LOCKED);
   copy_screen(screen1,screen2);
   if (screen2 != NULL) deleteList(&screen2); 
   if (listBox1 != NULL) removeList(&listBox1);
   dump_screen(screen1);
   if (ch == ENDSIGNAL) status = ENDSIGNAL;
   if (scrollData.itemIndex == 1) displayList(); 
   else if (scrollData.itemIndex == 0) displayHelp(); 
   else if (scrollData.itemIndex == 2) displaySearch(); 
   else if (scrollData.itemIndex == 3) displayInfo();
   else if (scrollData.itemIndex == 4) displayAbout();
   else if (scrollData.itemIndex == 5) status =ENDSIGNAL; 
}

int getElementfromFile(char *text, int elementNumber)
{
//get text data from file, max buffer 4096
    char filename[] = "elements.dat";
    char buffer[MAXTEXT];
    char dummy[4];
    char start_str[6];
    char end_str[6];
    char line[MAX_LINE_LENGTH];
    int flag = 0;
    FILE *fp;
    char ch=0;
   memset(buffer, 0, sizeof(buffer));
   memset(line, 0, sizeof(line));
   //memset(text, 0, sizeof(text));
    if (access(filename, F_OK) == -1) {
      //file not found; display error message and exit function
      create_screen(&screen2);
      copy_screen(screen2,screen1);
      draw_window(screen1, (new_columns/2) - 13 , (new_rows/2) -2 , (new_columns/2) + 13, (new_rows/2) +2, B_WHITE, F_BLACK, B_RED, 1,1,1,0);
      write_str(screen1, (new_columns/2) - 12, (new_rows/2)-2, "[+] ERROR" , B_RED, F_WHITE,0);
      write_str(screen1, (new_columns/2) - 12, (new_rows/2), "    File not found!", B_WHITE, F_BLACK,0);
      dump_screen(screen1); 
      resetScrollData();
      scrollData.selectorLimit=4;    //No. of chars per item display
      listBox1 = addatend(listBox1, newitem("[OK]"));
      copy_screen(screen1,screen2);
      if (listBox1 != NULL) ch = listBox(listBox1, (new_columns/2), (new_rows/2)+1, &scrollData, B_WHITE, F_BLACK, B_CYAN,F_WHITE, 1, LOCKED);
      if (screen2 != NULL) deleteList(&screen2); 
      if (listBox1 != NULL) removeList(&listBox1);
      dump_screen(screen1);
      return -1;
    } 
    strcpy(start_str, "\0");
    strcpy(end_str, "\0");
    strcpy(dummy, "\0");
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(0);
    }
    sprintf(dummy,"%d", elementNumber);
    strcpy(start_str, "[");
    strcat(start_str,dummy);
    strcat(start_str,"]");
    strcpy(dummy, "\0");
    sprintf(dummy,"%d", elementNumber+1);
    strcpy(end_str, "[");
    strcat(end_str,dummy);
    strcat(end_str,"]");
    strcpy(dummy, "\0");
   
    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        if (strstr(line, start_str)) {
            flag = 1;
            continue;
        }
        if (strstr(line, end_str)) {
            flag = 0;
            break;
        }
        if (flag) {
            strcat(buffer, line);
        }
    }
    strcat(buffer, "\0");
    strcpy(text, buffer);

    fclose(fp);
    return ch;
}
int special_keys(char ch) {
/* MANAGE SPECIAL KEYS */
/* 
   New implementation: Trail of chars found in keyb.c
   If K_ESCAPE is captured read a trail up to 5 characters from the console.
   This is to control the fact that some keys may change
   according to the terminal and expand the editor's possibilities.
   Eg: F2 can be either 27 79 81 or 27 91 91 82.  
   - Note : if (currentColumn > 1) cleanArea(1);	
	When horizontal scroll is active all the screen is cleaned when moving.
*/

  char    chartrail[5];
  if(ch == K_ESCAPE) {
    read_keytrail(chartrail);	//Read trail after ESC key

    //Check key trails for special keys.


    //FUNCTION KEYS : F1 - F4
    if(strcmp(chartrail, K_F2_TRAIL) == 0 ||
       strcmp(chartrail, K_F2_TRAIL2) == 0) {
      //menu
      option_menu();
    } else if(strcmp(chartrail, K_F1_TRAIL) == 0 ||
	      strcmp(chartrail, K_F1_TRAIL2) == 0) {
      displayHelp(); 
      // ARROW KEYS
    } else if(strcmp(chartrail, K_LEFT_TRAIL) == 0 ) {
      //Left-arrow key
       if (oldPointer != 0) currentPointer = oldPointer-9;
       selectItem(-2);
       draw_table(2);
       currentDirection = -2;
       
   } else if(strcmp(chartrail, K_RIGHT_TRAIL) == 0) {
      if (oldPointer !=0) currentPointer = oldPointer+9;
       selectItem(2);
       draw_table(2);
       currentDirection = 2;
    } else if(strcmp(chartrail, K_UP_TRAIL) == 0) {
      if (oldPointer != 0) currentPointer = oldPointer-1;
      else currentPointer = 0; 
       selectItem(-1);
       draw_table(2);
       currentDirection = -1;
    } else if(strcmp(chartrail, K_DOWN_TRAIL) == 0)  {
      if (oldPointer !=0) currentPointer = oldPointer+1;
      selectItem(1);
       draw_table(2);
       currentDirection = 1;
     } else if(strcmp(chartrail, K_ALT_S) == 0)   {
       displaySearch();
     } else if(strcmp(chartrail, K_ALT_L) == 0) {
      displayList();
    } else if(strcmp(chartrail, K_ALT_H) == 0) {
      displayHelp(); 
    } else if(strcmp(chartrail, K_ALT_I) == 0) {
      displayInfo();
    } else if(strcmp(chartrail, ESC2X) == 0) {
	return ENDSIGNAL;
    } else if(strcmp(chartrail, "\e") == 0) {
    //clear Table or Exit accordingly	
	if (currentPointer !=0){    
	  resetTable();
	  //draw_table(0);
	  dump_screen(screen1);
	} else
	return ENDSIGNAL;
    } else if(strcmp(chartrail, K_ALT_X) == 0) {
      return ENDSIGNAL;
    } else if(strcmp(chartrail, K_ALT_A) == 0) {
       displayAbout();
      }
    }
 return 0;
}

