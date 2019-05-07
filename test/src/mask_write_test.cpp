/**
 * Test for MASK WRITE MODBUS funciton
 *
 **/
#include <iostream>
#include <string>
#include <ctime>
#include <cassert>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include "mb.h"

using namespace std;

//
// 1. Отправляю запрос со случайными адресом, и максами AND и OR. В обработчике MASK WRITE проверяю, что они совпадают
// 2. Проверяю ситуацию, когда обработчик возвращает код исключания
//

// MODBUS ID
const uint8_t ID = 0x01;

// Параметры запроса. 
uint16_t OrMask, AndMask, Addr;

string resp;

// Обработчик, которые проверяет параметры запроса
int mask_write(
	uint16_t addr,
	uint16_t and_mask,
	uint16_t or_mask)
{
	assert(addr == Addr);
	assert(or_mask == OrMask);
	assert(and_mask == AndMask);
	
	return 0;
}

// Обработчик для проверки исключения
int mask_write_exc(
	uint16_t addr,
	uint16_t and_mask,
	uint16_t or_mask)
{
	return 3;
}

// Обработчик ответного сообщения
void response_handler(uint8_t* data, unsigned size)
{
	resp.clear();
	resp.append((char*)data, size);
}

int main(int argc, char* argv[])
{
	struct modbus_ascii *mb = modbus_ascii_init(ID);
	assert(mb);

	modbus_ascii_register_func_hand(mb, MB_MASK_WRITE, mask_write);
	modbus_ascii_set_resp_handler(mb, response_handler);
	
	srand(time(NULL));

	// 1. Проверка параметров запроса. Задаем случайные параметры, формируем запрос
	// и передаем его на обработку. 
	OrMask = rand();
	AndMask = rand();
	Addr = rand();

	// Запрос в числах
	vector<uint8_t> reqv = {(uint8_t)0x01,
							(uint8_t)0x16,
							(uint8_t)((Addr >> 8) & 0xFF),
							(uint8_t)(Addr & 0xFF),
							(uint8_t)((AndMask >> 8) & 0xFF),
							(uint8_t)(AndMask & 0xFF),
							(uint8_t)((OrMask >> 8) & 0xFF),
							(uint8_t)(OrMask & 0xFF)

	};

	// Добавляем LRC
	uint8_t lrc = 0;
	for(uint8_t d : reqv)
		lrc += d;
	lrc = -lrc;

	reqv.push_back(lrc);

	// Формируем запрос в ASCII
	string req;

	char asc[2];

	req = ":";

	for(uint16_t val : reqv)
	{
		sprintf(asc, "%02hhX", val);
		req += asc;
	}

	req += "\r\n";

	// Передаем на обработку
	for(char c : req)
		modbus_ascii_rec_byte(mb, c);

	// Ответ должен быть равен запросу
	assert(req == resp);

	//
	// Проверяем передачу исключения
	//
	modbus_ascii_register_func_hand(mb, MB_MASK_WRITE, mask_write_exc);
	
	// Передаем на обработку
	for(char c : req)
		modbus_ascii_rec_byte(mb, c);

	assert(resp == ":01960366\r\n");
	
	cout << "****************************************************************************" << endl;
	cout << "* MASK WRITE TEST SUCCESS" << endl;
	cout << "****************************************************************************" << endl;
	
	return 0;
}
