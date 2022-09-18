#pragma once
#include <stdint.h>
#include <array>

#include "CPU.h"

class Bus
{
public: 
	Bus();
	~Bus();

	//hardware components 
	CPU cpu; 

	std::array<uint8_t, 64 * 1024> ram;

	//read and written to cpu 
	void write(uint8_t data, uint16_t address); 
	uint8_t read(uint16_t address); 
};
