##########################################################################
# ModBus test Makefile
#
#
#########################################################################
SRC_DIR=..\src

SRC=src\main.c ..\src\*.c
INCL=$(SRC_DIR)\*.h

INCS=/I ..\src

CFLAGS=/Zi /DEBUG /D_DEBUG

all: test.exe
	cd bin
	test write_single.pat read_hold.pat exc.pat
	
clean:
	rm -f bin/*

test.exe: $(SRC) $(INCL)
	$(CPP) $(CFLAGS) $(INCS) /Febin\test.exe $(SRC) DbgHelp.lib
	rm *.obj vc100.pdb
