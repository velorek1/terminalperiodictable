.POSIX:
TARGET = tptable
CC     = cc
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS  =

# The list of object files.
OBJS =  main.o rterm.o listbox.o scbuf.o
OBJS += ui.o global.o
OBJS += keyb.o tm.o

# the list of files to clean
TOCLEAN = $(TARGET) $(OBJS)

RM ?= rm -f
INSTALL = install
INSTALLDIR = /usr/bin
SHAREDDIR = /usr/share/ptable

all: $(TARGET)
clean:
	$(RM) $(TOCLEAN)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

install: $(TARGET)
	$(INSTALL) -d $(INSTALLDIR)
	$(INSTALL) -m 755 $(TARGET) $(INSTALLDIR)
	$(INSTALL) -d $(SHAREDDIR)
	$(INSTALL) -m 644 elements.dat $(SHAREDDIR)

uninstall:
	$(RM) $(INSTALLDIR)/$(TARGET)
	$(RM) $(SHAREDDIR)/elements.dat

# INCLUDE DEPENDENCIES to compile depending on which
# source has been touched.
main.o: main.c rterm.h listbox.h scbuf.h keyb.h global.h ui.h tm.h
keyb.o: keyb.c rterm.h keyb.h
listbox.o: rterm.h keyb.h
rterm.o: rterm.c
tm.o: tm.c tm.h
scbuf.o: scbuf.c rterm.h keyb.h scbuf.h
ui.o: ui.c scbuf.h rterm.h keyb.h ui.h

