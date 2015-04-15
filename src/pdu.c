/**
***********************************************************
* @name pdu.c
* @brief Perform Modbus PDU
*
***********************************************************
*/
#include "pdu.h"
#include "mb_functions.h"

/**
* @brief Perform Modbus PDU
* @pdu	 PDU object
* @need_resp Need responce flag 
* @retval
**/
void perf_pdu(struct pdu* t, bool need_resp)
{
	uint8_t func = t->req_buf[0];
	uint8_t exception_code;
	
	/* Check function correct */
	if(	func > MODBUS_FUNCTION_NUM	)
	{
		excetion_resp(MB_ILLEGAL_FUNCTION);
	}
	else
	{
		switch(func)
		{
		case MB_READ_HOLD:
			read_hold(t);
			break;
		
		case MB_WRITE_HOLD:
			write_hold(t);
			break;
		
		default:
			excetion_resp(MB_ILLEGAL_FUNCTION);
		}
	}
	
	t->is_resp = t->is_resp && need_resp;
}

