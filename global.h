/*
 * Global variables are intented to be placed here
 * Last modified: 9/7/2022
 * @author: velorek
 *
 */
#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "scbuf.h"
#include "tm.h"
#define UNICODEBAR 0x2592
#define ENDSIGNAL -1
#define TABLESIZE 162
#define MINWIDTH 113
#define MINHEIGHT 36
#define MAXLINE 255
#define MAXTEXT 8192
#define MAXELEMENT 100
#define NUMELEMENTS 118
#define WINERRMSGTL "[+] DISPLAY ERROR\0" 
#define WINERRMSGLN1 "WINDOW SIZE IS TOO SMALL!\0" 
#define WINERRMSGLN2 "RESIZE WINDOW MANUALLY.\0" 
#define WINERRMSGLN3 "PRESS [S] TO OVERRIDE.\0" 
#define STATUSMSG1 "F1:HELP | F2:MENU | ALT+L: LIST | ESC:CLEAR TABLE-EXIT \0" 
#define OPTION1 "Help........F1\0"
#define OPTION2 "List.....ALT+L\0"
#define OPTION3 "Search...ALT+S\0"
#define OPTION4 "Info.....ALT+I\0"
#define OPTION5 "About....ALT+A\0"
#define OPTION6 "Exit.....ALT+X\0"
#define HELP0 "P-TABLE                                            \0"
#define HELP1 "=======                                            \0"
#define HELP2 "P-Table is a terminal TUI scientific program.      \0"
#define HELP3 "The periodic table is a rows and columns           \0"
#define HELP4 "arrangement of the chemical elements. It is widely \0"
#define HELP5 "used in chemistry, physics and other sciences and  \0"
#define HELP6 "it is widely seen as an icon of chemistry.         \0"
#define HELP7 "___________________________________________________\0"
#define HELP8 "[F1] or [ALT + H] -> Display help                  \0"
#define HELP9 "[F2] or [CTRL + L] -> Activate menu                \0"
#define HELP10 "[Arrow Keys] and [ENTER]-> Navigate periodic tiles \0"
#define HELP11 "[K]-> Display color key | ALT + I -> Category info \0"
#define HELP12 "[ALT + A] -> About      | ALT + L -> Elements List \0"
#define HELP13 "[ALT + S] -> Search for a specfic element          \0"
#define HELP14 "[ESC] or [CTRL + C] or [ALT+X] -> Exit program     \0"
#define HELP15 "[S] Hide/Show table | CTRL or ALT may be used.     \0"
#define HELP16 "___________________________________________________\0"
#define HELP17 "This program was coded in C & Vim in 2023.         \0"
#define HELP18 "Some of the techniques used can be found in my     \0"
#define HELP19 "personal blog : oldstuff286.blogspot.com           \0"
#define HELP20 "Peace!  - by v3l0r3k                               \0"

#define ABOUT0 "__________        ___________     ___.   .__          "          
#define ABOUT1 "\\______   \\       \\__    ___/____ \\_ |__ |  |   ____  "  
#define ABOUT2 " |     ___/  ______ |    |  \\__  \\ | __ \\|  | _/ __ \\ " 
#define ABOUT3 " |    |     /_____/ |    |   / __ \\| \\_\\ \\  |_\\  ___/" 
#define ABOUT4 " |____|             |____|  (____  /___  /____/\\___  >"
#define ABOUT5 "                                 \\/    \\/          \\/"
#define ABOUT6 "            Coded by v3l0r3k - v0.1 2023"
#define ABOUT7 "              oldstuff286.blogspot.com"

#define INFO1 "Alkali metals: Group 1 elements in the periodic table that are highly reactive and have one valence electron. They include lithium (Li), sodium (Na), potassium (K), rubidium (Rb), cesium (Cs), and francium (Fr)."

#define INFO2 "Alkaline earth metals: Group 2 elements in the periodic table that are also highly reactive and have two valence electrons. They include beryllium (Be), magnesium (Mg), calcium (Ca), strontium (Sr), barium (Ba), and radium (Ra)."

#define INFO3 "Transition metals: Elements in the middle of the periodic table, from group 3 to group 12, that have varying numbers of valence electrons and exhibit a wide range of physical and chemical properties. They include iron (Fe), copper (Cu), zinc (Zn), silver (Ag), and gold (Au)."

#define INFO4 "Post-transition metals: Elements located to the right of the transition metals that have some metallic and some non-metallic properties. They include aluminum (Al), gallium (Ga), indium (In), tin (Sn), lead (Pb), and bismuth (Bi)."

#define INFO5 "Metalloids: Elements that have properties of both metals and non-metals. They are located along the diagonal line that separates metals from non-metals in the periodic table. They include boron (B), silicon (Si), germanium (Ge), arsenic (As), antimony (Sb), tellurium (Te), and polonium (Po)."

#define INFO6 "Reactive non-metals: Non-metallic elements that are highly reactive and typically form negative ions. They include fluorine (F), chlorine (Cl), oxygen (O), sulfur (S), and selenium (Se)."

#define INFO7 "Noble gases: Elements in Group 18 of the periodic table that have a full outer shell of valence electrons, making them highly stable and unreactive. They include helium (He), neon (Ne), argon (Ar), krypton (Kr), xenon (Xe), and radon (Rn)."

#define INFO8 "Lanthanides: Elements in the lanthanide series, which are located in the bottom of the periodic table, and have similar chemical and physical properties. They include cerium (Ce), praseodymium (Pr), neodymium (Nd), and europium (Eu)."

#define INFO9 "Actinides: Elements in the actinide series, which are located at the bottom of the periodic table, and have similar chemical and physical properties. They include uranium (U), plutonium (Pu), and curium (Cm)."

#define INFO0 "Unknown properties: Elements that have not yet been fully characterized due to their rarity and difficulty in obtaining or synthesizing. They include elements with atomic numbers 113 (Nihonium) and higher."

#define NUMOPTION 6
#define HELPLINES 21
#define TIMER_SPEED 70
extern SCREENCELL *screen1;
extern NTIMER timer2;
extern size_t animation;
extern int centerX;
extern char titlemsg[18];
extern BOOL displaytable;
extern BOOL blocked;

//extern char aboutMSG[7][MAXLINE];

extern int     new_rows, new_columns, old_rows, old_columns;	// Terminal dimensions

int _animation(); 

#endif
