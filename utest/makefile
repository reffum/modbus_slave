# ==========================================
# 
# ==========================================  

SRC_DIR=$(PROJECT_DIR)\src
TEST_SRC_DIR=$(UTESTDIR)\src
UNITY_DIR=$(UTESTDIR)\unity

INC_DIRS =  /I $(TEST_SRC_DIR) 			\
			/I $(UNITY_DIR)\src 		\
			/I $(SRC_DIR)
CFLAGS = /DDEBUG			

all: execute clean

convert.exe: $(SRC_DIR)\convert.c $(TEST_SRC_DIR)\convert_test.c $(TEST_SRC_DIR)\convert_test_Runner.c
	chcp 1251			
	
	cd $(UTESTDIR)\bin
	$(CPP) $(INC_DIRS) $** $(UNITY_DIR)\src\unity.c /Fe$(UTESTDIR)\bin\convert.exe
	cd ..
	
lrc.exe: $(SRC_DIR)\lrc.c $(TEST_SRC_DIR)\lrc_test.c $(TEST_SRC_DIR)\lrc_test_Runner.c
	chcp 1251			
	
	cd $(UTESTDIR)\bin
	$(CPP) $(INC_DIRS) $** $(UNITY_DIR)\src\unity.c /Fe$(UTESTDIR)\bin\lrc.exe
	cd ..

ascii.exe: $(SRC_DIR)\ascii.c $(SRC_DIR)\convert.c $(SRC_DIR)\lrc.c $(TEST_SRC_DIR)\ascii_test.c $(TEST_SRC_DIR)\ascii_test_Runner.c
	chcp 1251			
	
	cd $(UTESTDIR)\bin
	$(CPP) $(INC_DIRS) $** $(UNITY_DIR)\src\unity.c /Fe$(UTESTDIR)\bin\ascii.exe $(CFLAGS)
	cd ..

pdu.exe: $(SRC_DIR)\pdu.c $(TEST_SRC_DIR)\pdu_test.c $(TEST_SRC_DIR)\pdu_test_Runner.c 
	chcp 1251			
	
	cd $(UTESTDIR)\bin
	$(CPP) $(INC_DIRS) $** $(UNITY_DIR)\src\unity.c /Fe$(UTESTDIR)\bin\pdu.exe $(CFLAGS)
	cd ..

$(TEST_SRC_DIR)\convert_test_Runner.c: $(TEST_SRC_DIR)\convert_test.c
	ruby $(UNITY_DIR)\auto\generate_test_runner.rb $(TEST_SRC_DIR)\convert_test.c

$(TEST_SRC_DIR)\lrc_test_Runner.c:  $(TEST_SRC_DIR)\lrc_test.c
	ruby $(UNITY_DIR)\auto\generate_test_runner.rb $(TEST_SRC_DIR)\lrc_test.c

$(TEST_SRC_DIR)\ascii_test_Runner.c: $(TEST_SRC_DIR)\ascii_test.c
	ruby $(UNITY_DIR)\auto\generate_test_runner.rb $(TEST_SRC_DIR)\ascii_test.c

$(TEST_SRC_DIR)\pdu_test_Runner.c: $(TEST_SRC_DIR)\pdu_test.c
	ruby $(UNITY_DIR)\auto\generate_test_runner.rb $(TEST_SRC_DIR)\pdu_test.c

clean:
	rm bin/*
	
execute: convert.exe lrc.exe ascii.exe pdu.exe
	bin\convert.exe 
	bin\lrc.exe
	bin\ascii.exe
	bin\pdu

