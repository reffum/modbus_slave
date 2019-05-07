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


all: test.exe write_multiple_test.exe
	cd bin
	test write_single.pat read_hold.pat exc.pat eit.pat
	write_multiple_test

write_multiple: write_multiple_test.exe

clean:
	del /Q *.obj
	del /Q *.pdb


test.exe: $(SRC) $(INCL)
	$(CPP) $(CFLAGS) $(INCS) /Febin\test.exe $(SRC) DbgHelp.lib
	del /Q *.obj vc100.pdb

write_multiple_test.exe: src\write_multiple_test.cpp ..\src\*.c
	$(CPP) $(CFLAGS) $(INCS) /Febin\write_multiple_test.exe src\write_multiple_test.cpp ..\src\*.c /MTd 
	del /Q *obj vc100.pdb

