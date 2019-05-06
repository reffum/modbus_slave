/**
 * write_multiple_test.c
 * Test for Write Multiple Registers function
 *
 **/
#include <assert.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <cstdint>
#include <ctime>
#include <functional>

#include "mb.h"

using namespace std;

// Registers
uint16_t Registers[UINT16_MAX];

struct modbus_ascii *mb = NULL;

int write_multiple_handler(uint16_t addr,
						   uint16_t num,
						   const uint16_t *values)
{
  int i;
  
  assert(addr + num < UINT16_MAX);

  for(i = 0; i < num; i++)
  {
	  Registers[addr + i] = values[i];
  }

  return 0;
}

int write_multiple_handler_exception(uint16_t addr,
									 uint16_t num,
									 const uint16_t *values)
{
	return 4;
}


string resp;

void responce_handler(uint8_t* data, unsigned int size)
{
  resp.clear();
  resp.append(reinterpret_cast<char*>(data), size);
}

string GetString(uint16_t addr, vector<uint16_t> data, bool broadcast = false)
{
  vector<uint8_t> bytes;

  bytes.push_back(broadcast ? 0xFF : 0x01);
  bytes.push_back(0x10);

  bytes.push_back((addr >> 8) & 0xFF);
  bytes.push_back(addr & 0xFF);

  bytes.push_back((data.size() >> 8) & 0xFF);
  bytes.push_back(data.size() & 0xFF);
  bytes.push_back( (data.size()*2) & 0xFF);

  
  for(uint16_t word : data)
  {
	  bytes.push_back((word >> 8) & 0xFF);
	  bytes.push_back(word & 0xFF);
  }

  uint8_t lrc = 0;
  for(uint8_t b : bytes)
		  lrc += b;

  lrc = -lrc;

  bytes.push_back(lrc);

  char sb[2];
  string r = ":";
  for(uint8_t b : bytes)
  {
	  sprintf(sb, "%02X", b);
	  r += sb;
  }

  r += "\r\n";

  return r;
}

//
// Проверяется:
// 1. Запись одного регистра по разным адресам
// 2. Запись максимального кол-ва регистров по разным адресам
// 3. Возврат исключения, если кол-во регистров больше заданного.
// 4. Возврат кода исключения из обработчика
//
int main(int argc, char *argv[])
{
	const int ID = 1;

	srand(time(NULL));
	
	memset(Registers, 0, sizeof(Registers));
  
	mb = modbus_ascii_init(ID);
	assert(mb);
  
	modbus_ascii_register_func_hand(mb, MB_WRITE_MULTIPLE_REGS, write_multiple_handler);
	modbus_ascii_set_resp_handler(mb, responce_handler);

	//
	// 1. Запись одного регистра по нескольким случайным адресам
	//
	int num = 10;
	for(bool broadcast : {false, true})
		for(int i = 0; i < num; i++)
		{
			memset(Registers, 0, sizeof(Registers));
		
			uint16_t data, addr;
			data = rand();
			addr = rand();

			string req = GetString(addr, {data}, broadcast);
			resp.clear();
  
			for(char c : req)
				modbus_ascii_rec_byte(mb, c);

			if(broadcast)
			{
				if(!resp.empty())
				{
					cout << "1 register write error" << endl;
					cout << "Broadcast request. Responce not empty" << endl;
					return -1;
				}

				if(Registers[addr] != data)
				{
					cout << "1 register write error(broadcast)" << endl;
					cout << "ADDR:" << addr << endl;
					cout << "DATA:" << data << endl;
					cout << "REQUEST: " << req << endl;
					cout << "RESPONCE:" << resp << endl;
					return -1;					
				}
					
			}
			else
			{
				if(resp.empty() ||
				   !equal(req.begin(), req.begin() + 12, resp.begin()) ||
				   Registers[addr] != data)
				{
					cout << "1 register write error" << endl;
					cout << "ADDR:" << addr << endl;
					cout << "DATA:" << data << endl;
					cout << "REQUEST: " << req << endl;
					cout << "RESPONCE:" << resp << endl;
					return -1;
				}
			}
		}

	//
	// 2. Запись 123 регистров по разным начальным адресам
	//
	vector<uint16_t> data;
	for(int i = 0; i < MB_WR_MULT_MAX; i++)
		data.push_back(rand());

	vector<uint16_t> addresses = {0, 0x10, 0x1000, 0x123};

	for(bool broadcast : {false, true})
		for(uint16_t addr : addresses)
		{
			string req = GetString(addr, data, broadcast);
			memset(Registers, 0, sizeof(Registers));

			resp.clear();

			for(char c : req)
				modbus_ascii_rec_byte(mb, c);

			if(broadcast)
			{
				if(!resp.empty())
				{
					cout << "Maximum register write error" << endl;
					cout << "Responce received for broadcast request" << endl;
					return -1;
				}
			}
			else
			{
				if(resp.empty() ||
				   !equal(req.begin(), req.begin() + 12, resp.begin()))
				{
					cout << "Maximum register write error" << endl;
					cout << "REQUEST: " << req << endl;
					cout << "RESPONCE:" << resp << endl;
					return -1;
				}
			}

			for(int i = 0; i < data.size(); i++)
			{
				if(Registers[addr + i] != data[i])
				{
					cout << "Maximum register write error. Data mismath." << endl;
					cout << "Registers[" << addr + i << "]:" << Registers[addr + i] << endl;
					cout << "DATA:" << data[i] << endl;
					return -1;
				}
			}
		}

	//
	// 3. Попытка записи более, чем 123 регистров. Должно возаращаться исключение с кодом 03
	//
	string req = GetString(0, vector<uint16_t>(MB_WR_MULT_MAX + 1));
	resp.clear();

	for(char c : req)
		modbus_ascii_rec_byte(mb, c);

	if(resp != ":0190036C\r\n")
	{
		cout << "Write more than max registers error." << endl;
		cout << "REQUEST: " << req << endl;
		cout << "RESPONCE:" << resp << endl;
		return -1;
	}

	//
	// 4. Возврат кода исключения из обработчика
	//

	modbus_ascii_register_func_hand(
		mb,
		MB_WRITE_MULTIPLE_REGS,
		write_multiple_handler_exception);

	req = GetString(0, vector<uint16_t>(1));
	resp.clear();

	for(char c : req)
		modbus_ascii_rec_byte(mb, c);

	if(resp != ":0190046B\r\n")
	{
		cout << "Exception return error" << endl;
		cout << "REQUEST: " << req << endl;
		cout << "RESPONCE:" << resp << endl;
		return -1;
	}
	
	printf("********************************************\n");
	printf("WRITE MULTIPLE TEST SUCCESS\n");
	printf("********************************************\n");
  
	return 0;
}
