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
	Registers[addr + i] = values[i];

  return 0;
}

string resp;

void responce_handler(uint8_t* data, unsigned int size)
{
  resp.clear();
  resp.append(reinterpret_cast<char*>(data), size);
}

string GetString(uint16_t addr, vector<uint16_t> data)
{
  vector<uint8_t> bytes;

  bytes.push_back(0x01);
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
// 2. Запись 32 регистров по разным начальным адресам
// 3. Запись максимального кол-ва регистров по разным адресам
// 4. Возврат исключения, если кол-во регистров больше заданного.
// 5. Возврат кода исключения из обработчика
//
int main(int argc, char *argv[])
{
  const int ID = 1;
  
  memset(Registers, 0, sizeof(Registers));
  
  mb = modbus_ascii_init(ID);
  assert(mb);
  
  modbus_ascii_register_func_hand(mb, MB_WRITE_MULTIPLE_REGS, write_multiple_handler);
  modbus_ascii_set_resp_handler(mb, responce_handler);

  string req = GetString(0, {1});
  
  for(char c : req)
	modbus_ascii_rec_byte(mb, c);

  if(resp.empty() || !equal(req.begin(), req.begin() + 6, resp.begin()) )
  {
		  cout << "Error" << endl;
		  cout << "REQUEST: " << req << endl;
		  cout << "RESPONCE:" << resp << endl;
		  return -1;
  }

  cout << req << endl;
  cout << resp << endl;
  
  printf("********************************************\n");
  printf("WRITE MULTIPLE TEST SUCCESS\n");
  printf("********************************************\n");

  
  
  return 0;
}
