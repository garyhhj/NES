#include "Bus.h"

Bus::Bus() 
{
	for (auto& i : ram) i = 0x00; 
}

Bus::~Bus()
{
	//done calling destructor 
}

void Bus::write(uint8_t data, uint16_t address)
{
	ram[address] = data; 
}

uint8_t Bus::read(uint16_t address)
{
	return ram[address]; 
}
