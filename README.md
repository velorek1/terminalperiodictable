# ptable
A beautiful TUI periodic table for GNU/linux terminals coded in C - no extra dependencies

TO COMPILE and RUN:  

    * GNU/LINUX:
    - Download or clone repository.
    - Type "make" to compile and "./ptable" to run-
    - Alternatively, type "bash build.sh" and ./ptable" to run.
    
    
![Alt text](sc0.jpg?raw=true "Demo")


The periodic table, also known as the periodic table of the elements, is a rows and columns arrangement of the chemical elements. It is widely used in chemistry, physics, and other sciences, and is generally seen as an icon of chemistry. (WIKIPEDIA)

In my last project in C I wanted to compile everything I've learned with text user interfaces and create a retro-looking periodic table that looks nice :) 

Though not my best or cleanest code, it is intended to be used as a "demo" for the Lynx TUI. Is is also made with a lot of love.

The explanation of all the modules below:

(Increasing in order of abstraction until you reach main.c)
________________

LEVEL 0: (BASE)
- rterm.c : With the ANSI escape sequences to color our output in the terminal
- tm.c : Create a millisecond timer for animations
_______________

LEVEL 1: (LOW LEVEL ABSTRACTIONS)
- keyb.c : Creates a small keyboard abstraction to read escaped keys \e on Linux
- scbuf.c (1) : Creates an intermediate layer between the display and the terminal as a double screen buffer - listbox.c (2) : Creates a list with a selector with horizontal scroll
_______________

LEVEL 2: (HIGH LEVEL ABSTRACTIONS)
- ui.c : Different tools like textbox and window for user interface
- global.c: text messages and global variables
_______________

main.c: Main program
elements.dat: Database of elements, most of the info generated with chatGPT.

(1) http://oldstuff286.blogspot.com/2017/09/a-very-simple-screen-double-buffer.html

(2) http://oldstuff286.blogspot.com/2018/07/segmentation-fault-c-pointers.html
