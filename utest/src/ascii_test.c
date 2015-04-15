/**
***********************************************************
* @name convert_test.c
* @brief Функции преобразования ASCII строк и символов
*
***********************************************************
*/
#include <stdbool.h>
#include "unity.h"
#include "ascii.h"
#include "pdu.h"

static void send_resp(uint8_t resp, int size);

char resp_fdu[64];
int resp_fdu_size = 0;

uint8_t pdu_buffer[32];
int pdu_size = 0;

struct ascii uut;
struct pdu pdu = {	{1,2,3,0xAB, 0xCD}, 5, NULL};

#define ID 1

void setUp(void)
{
	ascii_init(&uut, ID);
	uut.pdu = &pdu;
	uut.send_resp = send_resp;
}

void tearDown(void)
{
}

/* Прием фрейма */
void test_normal()
{
	const static char ascii_fdu[] = ":01010203ABCD81\r\n";
	const static char resp_fdu_exp[] = ":01010203ABCD81\r\n";
	int i;
			
	for(i = 0; i <= sizeof(ascii_fdu)-1; i++)
		ascii_rec_byte(&uut, ascii_fdu[i]);
	
	TEST_ASSERT_EQUAL(5, pdu_size);
	TEST_ASSERT_EQUAL(1, pdu_buffer[0]);
	TEST_ASSERT_EQUAL(2, pdu_buffer[1]);
	TEST_ASSERT_EQUAL(3, pdu_buffer[2]);	
	TEST_ASSERT_EQUAL(0xAB, pdu_buffer[3]);
	TEST_ASSERT_EQUAL(0xCD, pdu_buffer[4]);
	
	TEST_ASSERT_EQUAL(sizeof(resp_fdu_exp) - 1, resp_fdu_size);
	TEST_ASSERT(memcmp(resp_fdu_exp, resp_fdu, resp_fdu_size) == 0);
}

/* Ошибки */
void test_ErrNoDig()
{
	const static char ascii_fdu[] = ":0101V203ABCD81\r\n";
	int i;
	
	for(i = 0; i <= sizeof(ascii_fdu)-1; i++)
		ascii_rec_byte(&uut, ascii_fdu[i]);
}

void test_ErrLine()
{
	const static char ascii_fdu[] = ":01010203ABCD81\r\n";
	int i;
	
	for(i = 0; i <= sizeof(ascii_fdu)-1; i++){
		ascii_rec_byte(&uut, ascii_fdu[i]);	
		if(i == 5)
			ascii_error(&uut);
	}
}


bool pdu_execute(struct pdu* t, uint8_t* _pdu, int size)
{
	pdu_size = size;
	memcpy(pdu_buffer, _pdu, size);
	return true;
}

void send_resp(uint8_t* resp, int size)
{
	int i;
	
	resp_fdu_size = size;
	memcpy(resp_fdu, resp, size);
	
	for(i = 0; i < size; i++)
		printf("%c", resp[i]);
	printf("\n");
}
