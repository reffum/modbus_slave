/**
***********************************************************
* @name lrc_test.c
* @brief Расчет LRC. Тест.
*
***********************************************************
*/
#include "unity.h"
#include "lrc.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_get_lrc()
{
	uint8_t bytes1[] = {0x03,0x03,0x00,0x15,0x00,0x02};
	uint8_t bytes2[] = {0x03,0x03,0x04,0x14,0x00,0x00,0x00};
	
	TEST_ASSERT_EQUAL(0xE3, get_lrc(bytes1, sizeof(bytes1)));
	TEST_ASSERT_EQUAL(0xE2, get_lrc(bytes2, sizeof(bytes2)));
}
