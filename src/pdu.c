/**
***********************************************************
* @name pdu.c
* @brief Perform Modbus PDU
*
***********************************************************
*/
#include <string.h>
#include <assert.h>
#include "pdu.h"
#include "mb_functions.h"

/**********************************************************************
* Constants
**********************************************************************/
const int READ_HOLD_MAX = 125;	/* Maximum number of registers in Read Hold request */

/**********************************************************************
* Private functions
**********************************************************************/
#ifdef DEBUG
#define PRIVATE
#else
#define PRIVATE static
#endif

/* Functions */
PRIVATE void read_hold(struct pdu*);
PRIVATE void write_single(struct pdu*);

PRIVATE void exception_responce(
	struct pdu*, 
	uint8_t code);
	
uint16_t __inline byte2word(
	uint8_t l, 
	uint8_t h)
{
	return (uint16_t)h << 8 | l;
}

PRIVATE void le2bea(uint16_t* leVal, unsigned count);
PRIVATE uint16_t le2be(uint16_t leVal);
/**
* @brief Perform Modbus PDU
* @pdu	 PDU object
* @need_resp Need responce flag 
* @retval
**/
void perf_pdu(struct pdu* t, bool need_resp)
{
	uint8_t func = t->req_buf[0];
	
	/* Check function correct */
	if(	func > MODBUS_FUNCTION_NUM	)
	{
		exception_responce(t, MB_ILLEGAL_FUNCTION);
	}
	else
	{
		switch(func)
		{
		case MB_READ_HOLD:
			read_hold(t);
			break;
		
		case MB_WRITE_SINGLE:
			write_single(t);
			break;
		
		default:
			exception_responce(t, MB_ILLEGAL_FUNCTION);
		}
	}
	
	t->is_resp = t->is_resp && need_resp;
}

/**********************************************************************
* Private functions
**********************************************************************/
void read_hold(struct pdu* pdu)
{
	uint16_t addr;
	uint16_t len;
	int r;
	
	if(pdu->req_count != 5)
	{
		exception_responce(pdu, MB_ILLEGAL_FUNCTION);
		return;
	}
	
	addr = byte2word(
		pdu->req_buf[2], 
		pdu->req_buf[1]
	);
	
	len = byte2word(
		pdu->req_buf[4],
		pdu->req_buf[3]
	);

	assert(len > 0);

	if(len > READ_HOLD_MAX)
	{
		exception_responce(pdu, MB_ILLEGAL_FUNCTION);
		return;
	}
	
	r = ((read_hold_handler)(pdu->func_handlers[MB_READ_HOLD]))
		(addr, 
		 len, 
		(uint16_t*)(pdu->resp_buf + 2)
	);
	
	/* Error */
	if(r)
	{
		exception_responce(pdu, r);
		return;
	}
	
	le2bea((uint16_t*)(pdu->resp_buf + 2), len);

	pdu->resp_buf[1] = len * 2;
	pdu->resp_buf[0] = MB_READ_HOLD;

	pdu->resp_count = len*2 + 2;
	
	pdu->is_resp = true;
}

void write_single(struct pdu* pdu)
{
	uint16_t addr, value;
	int r;
	
	if( pdu->req_count != 5)
	{
		exception_responce(pdu, MB_ILLEGAL_FUNCTION);
		return;		
	}
	
	addr = byte2word(
		pdu->req_buf[2], 
		pdu->req_buf[1]
	);
	
	value = byte2word(
		pdu->req_buf[4],
		pdu->req_buf[3]
	);
	
	r = ((write_single_handler)(pdu->func_handlers[MB_WRITE_SINGLE]))
		( 	addr, 
			value
	);
	
	/* Error */
	if(r)
	{
		exception_responce(pdu, r);
		return;
	}	

	pdu->resp_count = pdu->req_count;
	memcpy(pdu->resp_buf, pdu->req_buf, pdu->req_count);
	
	pdu->is_resp = true;
}

void exception_responce(
	struct pdu* pdu, 
	uint8_t code)
{
	pdu->is_resp = true;
	
	pdu->resp_count = 2;
	pdu->resp_buf[0] = MB_EXCEPTION;
	pdu->resp_buf[1] = code;	
}

uint16_t le2be(uint16_t leVal)
{
  uint8_t l,h;

  l =  (uint8_t)(leVal & 0xFF);
  h =  (uint8_t)((leVal & 0xFF00) >> 8);

  return (((uint16_t)l) << 8) | h;
}

void le2bea(uint16_t* leVal, unsigned count)
{
  int i;

  for(i = 0; i < count; i++)
    leVal[i] = le2be(leVal[i]);
}
