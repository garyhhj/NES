#include "CPU.h"

CPU::CPU()
{

}

CPU::~CPU()
{

}

void CPU::write(uint8_t data, uint16_t address)
{
	bus->write(data, address); 
}
uint8_t CPU::read(uint16_t address)
{
	return bus->read(address); 
}