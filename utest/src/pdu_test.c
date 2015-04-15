/**
***********************************************************
* @name pdu.c
* @brief Îáğàáîòêà PDU
*
***********************************************************
*/
#include "unity.h"
#include "pdu.h"
#include "params.h"
#include "func_codes.h"

struct pdu uut;

static Function pdu_func[FUNC_NUM];


/* Çàêğûòûå ôóíêöèè */
static int8_t read_coils(void* req, void* resp);
static int8_t read_coils_er(void* req, void* resp);
static int8_t read_hold(void* _req, void* _resp);
static int8_t read_hold_er(void* _req, void* _resp);


void setUp(void)
{
	uut.pdu_func = pdu_func;
}

void tearDown(void)
{
}

static uint8_t coils[8] = {0,1,2,3,4,5,6,7};

void test_ReadCoil()
{
	const uint8_t pdu[] = {0x01, 0x01,0x02, 0x2,0x3};
	const uint8_t expect[] = {1, 8, 0,1,2,3,4,5,6,7};
	const int pdu_size = sizeof(pdu);

	pdu_func[READ_COILS] = read_coils;

	TEST_ASSERT_TRUE(pdu_execute(&uut, pdu, pdu_size));
	
	TEST_ASSERT_EQUAL(10, uut.responce_size);
	TEST_ASSERT(memcmp(uut.responce, expect, 10) == 0);
}

void test_ReadCoilsER()
{
	const uint8_t expect[] = {2};
	const uint8_t pdu[] = {0x01, 0x01,0x02, 0x2,0x3};
	const int pdu_size = sizeof(pdu);

	pdu_func[READ_COILS] = read_coils_er;

	TEST_ASSERT_TRUE(pdu_execute(&uut, pdu, pdu_size));
	
	TEST_ASSERT_EQUAL(1, uut.responce_size);
	TEST_ASSERT_EQUAL(2, uut.responce[0]);
}

int8_t read_coils(void* req, void* resp)
{
	static struct read_coils_resp _resp = {8, coils};

	TEST_ASSERT_EQUAL(0x0102, ((struct read_coils_req*)req)->addr);
	TEST_ASSERT_EQUAL(0x0203, ((struct read_coils_req*)req)->count);

	*((struct read_coils_resp*)resp) = _resp;
	
	return 0;
}

int8_t read_coils_er(void* req, void* resp)
{
	return -2;
}

void test_ReadHold()
{
	const uint8_t pdu[] = {0x03, 0x01,0x02, 0x0,0x2};
	const int pdu_size = sizeof(pdu);
	const uint8_t expect[] = {0x3, 12, 0xAB,0xCD, 0x12,0x34, 
							 0,0, 0,0, 0,0, 0,0};
	
	pdu_func[READ_HOLD] = read_hold;

	TEST_ASSERT_TRUE(pdu_execute(&uut, pdu, pdu_size));

	TEST_ASSERT_EQUAL(sizeof(expect), uut.responce_size);
	TEST_ASSERT(memcmp(expect, uut.responce, sizeof(expect)) == 0);
}

int8_t read_hold(void* _req, void* _resp)
{
	struct read_hold_req* req = (struct read_hold_req*)_req;
	struct read_hold_resp* resp = (struct read_hold_resp*)_resp;
	static uint16_t reg[] = {0xABCD, 0x1234, 0,0,0,0};
	
	TEST_ASSERT_EQUAL(0x0102, req->addr);
	TEST_ASSERT_EQUAL(2, req->count);
	
	resp->data = reg;
	resp->count = sizeof(reg)/2;
	
	return 0;
}

void test_ReadHoldER()
{
	const uint8_t pdu[] = {0x03, 0x01,0x02, 0x0,0x2};
	const int pdu_size = sizeof(pdu);
	const uint8_t expect[] = {0x3, 12, 0xAB,0xCD, 0x12,0x34, 
							 0,0, 0,0, 0,0, 0,0};
	pdu_func[READ_HOLD] = read_hold_er;
							 
	TEST_ASSERT_TRUE(pdu_execute(&uut, pdu, pdu_size));
	TEST_ASSERT_EQUAL(1, uut.responce_size);
	TEST_ASSERT_EQUAL(3, uut.responce[0]);
}

int8_t read_hold_er(void* _req, void* _resp)
{
	return -3;
}

static int8_t write_hold(void* req, void* resp);

void test_WriteHold()
{
	const uint8_t pdu[] = {0x06, 0x01,0x02, 0xAB,0xCD};
	const int pdu_size = sizeof(pdu);
	
	pdu_func[WRITE_HOLD] = write_hold;
	TEST_ASSERT_TRUE(pdu_execute(&uut, pdu, pdu_size));
	
	TEST_ASSERT_EQUAL(pdu_size, uut.responce_size);
	TEST_ASSERT(memcmp(pdu, uut.responce, pdu_size) == 0);	
}

int8_t write_hold(void* _req, void* resp)
{
	struct write_hold_req *req = (struct write_hold_req *)_req;
	
	TEST_ASSERT_EQUAL(0x0102, req->addr);
	TEST_ASSERT_EQUAL(0xABCD, req->data);
	
	return 0;
}
