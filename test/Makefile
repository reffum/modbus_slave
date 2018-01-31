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
	del /Q *.obj
	del /Q *.pdb


test.exe: $(SRC) $(INCL)
	$(CPP) $(CFLAGS) $(INCS) /Febin\test.exe $(SRC) DbgHelp.lib
	del /Q *.obj vc100.pdb
