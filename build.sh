#!/bin/bash
# file: build.sh
echo -e "\e[34mTUI Periodic Table - Coded By v3l0r3k\e[0m"
echo
echo -e "Run as \e[34m./ptable\e[0m" 
echo Enjoy it!
gcc -Wextra -Wall -c rterm.c
gcc -Wextra -Wall -c scbuf.c
gcc -Wextra -Wall -c global.c
gcc -Wextra -Wall -c ui.c
gcc -Wextra -Wall -c tm.c
gcc -Wextra -Wall -c main.c
gcc -Wextra -Wall -c listbox.c
gcc -Wextra -Wall -c keyb.c

gcc rterm.o tm.o ui.o scbuf.o listbox.o keyb.o global.o main.o -Wextra -Wall -o ptable

