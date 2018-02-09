/**
*****************************************************************
* @file main.c
* @brief Modbus test 
*****************************************************************
**/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef _MSC_VER
#include <windows.h>
#include <DbgHelp.h>
#include <crtdbg.h>
#endif 

#include "mb.h"

#define  LINE_NUM  2048
#define  REGS_NUM  65536

struct modbus_ascii *mb = NULL;

unsigned char req[LINE_NUM];
unsigned char resp[LINE_NUM];

unsigned char resp_fact[LINE_NUM];
unsigned resp_fact_len;

const uint8_t id = 1;
uint16_t hold_regs[REGS_NUM];

static int read_hold_hand(
    uint16_t addr, 
    uint16_t len, 
    uint16_t* out_buffer);

static int write_single_hand(
    uint16_t addr,
    uint16_t *value);

static int eit_hand(
    const uint8_t *data_req,
    unsigned size_req,
    uint8_t *data_resp,
    unsigned *size_resp);
			     
static void responce(
    uint8_t* data,
    unsigned len);

/* Safe core dump and some
 needed information */
static void save_debug_info(void);

static void LastErrorString(LPTSTR lpszFunction);

/* Replace LF to CRLF in string. It is needed because gets function return 
 * only LF symbol at end of the string. 
 */
static void lf2crlf(unsigned char* str);	     

/**
 * The programm usage:
 * <prgname> <files-list>
 * files-list - List of test files. Each file contain test MODBUS request and responce, line by line. 
 * Program read 2 lines from file, line 1 - request, line 2 - responce, take request to MODBUS library and 
 * save responce. Then check MODBUS responce with file responce. Report error if it was.
 **/
int main(int argc, char *argv[])
{
  char *filename = NULL;
  FILE *file = NULL;
  int r, i, file_n;
  bool error = false;

  // Must be at least one test file
  if(argc < 2)
  {
    printf("Usage: test <test.file>\n\r");
    return -1;
  }
  
  printf("Modbus test start...\n\r");

  memset(hold_regs, 0, sizeof(hold_regs));

  // Initialize MODBUS 
  mb = modbus_ascii_init(id);
  if(!mb) goto exit;

  modbus_ascii_register_func_hand(mb, MB_READ_HOLD, read_hold_hand);
  modbus_ascii_register_func_hand(mb, MB_WRITE_SINGLE, write_single_hand);
  modbus_ascii_register_func_hand(mb, MB_EIT, eit_hand);
  modbus_ascii_set_resp_handler(mb, responce);

  // For each test file
  for(file_n = 1; file_n < argc; file_n++)
  {
    filename = argv[file_n];

    file = fopen(filename, "r");
    if(!file)
    {
	printf("Open file error");
	return -1;
    }

    /* Read file line by line. */
    while( fgets(req,  LINE_NUM, file) &&
	   fgets(resp, LINE_NUM, file))
      {
	lf2crlf(req);
	lf2crlf(resp);
	memset(resp_fact, 0, sizeof(resp_fact));
	resp_fact_len = 0;

	for(i = 0; req[i];)
	  modbus_ascii_rec_byte(mb, req[i++]);

	if(strcmp(resp_fact, resp))
	  {
	    save_debug_info();
	    error = true;
	    goto exit;
	  }
      }

    fclose(file);
  }

 exit: 
  if(!error)
  {
    printf("Test SUCCESS\n\r");
  }
  else
  {
    printf("%s fail\n\r", filename);
    printf("Request:%s", req);
    printf("Responce fact:%s\n\r", resp_fact);
    printf("Responce expe:%s\n\r", resp);
  }

  if(mb)   free(mb);
  if(file) fclose(file);

  return 0;
}

/**
 * READ HOLD 
 * Return hold_regs to MODBUS MASTER
 **/
static int read_hold_hand(
    uint16_t addr, 
    uint16_t len, 
    uint16_t* out_buffer)
{
  int i;
  
  for(i = 0; i < len; i++)
    out_buffer[i] = hold_regs[addr + i];

  return 0;
}

/**
 * Write single
 * Write in hold_regs
 **/
static int write_single_hand(
    uint16_t addr,
    uint16_t *value)
{
  hold_regs[addr] = *value;
  *value = addr - 1;

  return 0;
}


/**
 * Encapsulated Interface Transport handler.
 **/
static int eit_hand(
    const uint8_t *data_req,
    unsigned size_req,
    uint8_t *data_resp,
    unsigned *size_resp)
{
  int i;
  
  // Print request data
  printf("EIT: ");
  for(i = 0; i < size_req; i++){
    printf("%hX ", data_req[i]);
  }

  printf("\n");

  // Write 251 sequntial numbers in responce
  for(i = 0; i < 251; i++){
    data_resp[i] = i;
  }
  *size_resp = 251;
  return 0;
}


static void responce(
    uint8_t* data,
    unsigned len)
{
  memcpy(resp_fact, data, len);
  resp_fact_len = len;
}

/* Safe core dump and some needed information */
void save_debug_info()
{
#ifdef _MSC_VER
  HANDLE hFile = NULL;
  BOOL r;

  printf("Save minidump file\n\r");
  
  hFile = CreateFile("test.dmp", 
		     GENERIC_READ | GENERIC_WRITE,
		     FILE_SHARE_READ,
		     NULL,
		     CREATE_ALWAYS,
		     FILE_ATTRIBUTE_NORMAL,
		     NULL);
  if( !hFile )
  {
    printf("Can't create dump file\n\r");
    return;
  }

  r = MiniDumpWriteDump
    (
     GetCurrentProcess(),
     GetCurrentProcessId(),
     hFile,
     (MINIDUMP_TYPE)(MiniDumpNormal | MiniDumpWithDataSegs | MiniDumpWithHandleData | 
		     MiniDumpScanMemory | MiniDumpWithUnloadedModules | 
		     MiniDumpWithFullMemory |  MiniDumpWithProcessThreadData | MiniDumpWithFullAuxiliaryState |
		     MiniDumpWithFullMemoryInfo),
     NULL, NULL, NULL);

  if(r == FALSE)
  {
    printf("Dump write error with code: %X\n\r", GetLastError());
  }

  CloseHandle(hFile);
#endif

}

void LastErrorString(LPTSTR lpszFunction) 
{ 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and exit the process

    printf("Hello %s", lpMsgBuf);

    //    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
}
/* Replace LF to CRLF */
void lf2crlf(unsigned char* str)
{
  unsigned char* lfpos = strchr(str, 0xA);

  /* LF not found in the string */
  if(!lfpos)
  {
      return;
  }
  else if(lfpos == str)/* Empty line */
  {
    *str = NULL;
  }
  else
  {
    *lfpos = 0xD, *(lfpos + 1) = 0xA, *(lfpos + 2) = NULL;
  }
}
