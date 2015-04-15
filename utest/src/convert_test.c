/**
***********************************************************
* @name convert_test.c
* @brief ������� �������������� ASCII ����� � ��������
*
***********************************************************
*/
#include "unity.h"
#include "convert.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/* ������������� ��������� ������� � ����� */
void test_hex2dig(void)
{
	/* �������� ������ */
	TEST_ASSERT_TRUE(hex2dig('0') == 0);
	TEST_ASSERT_TRUE(hex2dig('1') == 1);
	TEST_ASSERT_TRUE(hex2dig('2') == 2);
	TEST_ASSERT_TRUE(hex2dig('3') == 3);
	TEST_ASSERT_TRUE(hex2dig('4') == 4);
	TEST_ASSERT_TRUE(hex2dig('5') == 5);
	TEST_ASSERT_TRUE(hex2dig('6') == 6);
	TEST_ASSERT_TRUE(hex2dig('7') == 7);
	TEST_ASSERT_TRUE(hex2dig('8') == 8);
	TEST_ASSERT_TRUE(hex2dig('9') == 9);
	TEST_ASSERT_TRUE(hex2dig('A') == 10);
	TEST_ASSERT_TRUE(hex2dig('B') == 11);
	TEST_ASSERT_TRUE(hex2dig('C') == 12);
	TEST_ASSERT_TRUE(hex2dig('D') == 13);
	TEST_ASSERT_TRUE(hex2dig('E') == 14);
	TEST_ASSERT_TRUE(hex2dig('F') == 15);
	
	/* ������ ������� */
	TEST_ASSERT_TRUE(hex2dig('a') == 0);
	TEST_ASSERT_TRUE(hex2dig(0) == 0);
}

/* �������������� ����� � ������ */
void test_dig2hex(void)
{
	TEST_ASSERT_TRUE(dig2hex(0) == '0');
	TEST_ASSERT_TRUE(dig2hex(1) == '1');
	TEST_ASSERT_TRUE(dig2hex(2) == '2');
	TEST_ASSERT_TRUE(dig2hex(3) == '3');
	TEST_ASSERT_TRUE(dig2hex(4) == '4');
	TEST_ASSERT_TRUE(dig2hex(5) == '5');
	TEST_ASSERT_TRUE(dig2hex(6) == '6');
	TEST_ASSERT_TRUE(dig2hex(7) == '7');
	TEST_ASSERT_TRUE(dig2hex(8) == '8');
	TEST_ASSERT_TRUE(dig2hex(9) == '9');
	TEST_ASSERT_TRUE(dig2hex(10) == 'A');
	TEST_ASSERT_TRUE(dig2hex(11) == 'B');
	TEST_ASSERT_TRUE(dig2hex(12) == 'C');
	TEST_ASSERT_TRUE(dig2hex(13) == 'D');
	TEST_ASSERT_TRUE(dig2hex(14) == 'E');
	TEST_ASSERT_TRUE(dig2hex(15) == 'F');
	
	TEST_ASSERT_TRUE(dig2hex(16) == -1);	
}

