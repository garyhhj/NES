#include "Bus.h"

class CPU
{
public: 
	CPU(); 
	~CPU(); 

	
	enum psFlags
	{
		N = (1 << 7), //negative
		V = (1 << 6), //overflow 
		O = (1 << 5), //unused flag(always one)
		B = (1 << 4), //break 
		D = (1 << 3), //decimal mode
		I = (1 << 2), //interupt disable 
		Z = (1 << 1), //zero 
		C = (1 << 0)  //carry
	};

	uint16_t pc = 0x0000; //program counter 
	uint8_t sp = 0x00; //stack pointer 
	uint8_t ps = 0x00; //processor status 

	uint8_t aReg = 0x00; //accumulator register
	uint8_t xReg = 0x00;  //X register
	uint8_t yReg = 0x00;  //Y register

	//how are we going tos et the psFLags

	/*
	* ADDRESSING MODES
	* accumulator  implied 
	* immediate    relative 
	* zero page    absolute indirect 
	* zero page x  index indirect x 
	* zero page y  index indirect y
	* absolute 
	* absolute x
	* absolute y 
	*/
	uint8_t ACCUM();   uint8_t IMPL();
	uint8_t IMM();	   uint8_t REL();
	uint8_t ZP();      uint8_t IND();
	uint8_t ZPX();	   uint8_t INDX();
	uint8_t ZPY();     uint8_t INDY();
	uint8_t ABS();
	uint8_t ABSX(); 
	uint8_t ABSY(); 
	

	
	//opcodes 
	uint8_t ADC();    uint8_t CLC();    uint8_t INY();    uint8_t ROL();    uint8_t TSX();
	uint8_t AND();    uint8_t CLD();    uint8_t JMP();    uint8_t ROR();    uint8_t TXA(); 
	uint8_t ASL();    uint8_t CLI();    uint8_t JSR();    uint8_t RTI();    uint8_t TXS(); 
	uint8_t BCC();    uint8_t CLV();    uint8_t LDA();    uint8_t RTS();    uint8_t TYA();
	uint8_t BCS();    uint8_t CMP();    uint8_t LDX();    uint8_t SBC();
	uint8_t BEQ();    uint8_t CPX();    uint8_t LDY();    uint8_t SEC();
	uint8_t BIT();    uint8_t CPY();    uint8_t LSR();    uint8_t SED();
	uint8_t BMI();    uint8_t DEC();    uint8_t NOP();    uint8_t SEI(); 
	uint8_t BNE();    uint8_t DEX();    uint8_t ORA();    uint8_t STA();
	uint8_t BPL();    uint8_t DEY();    uint8_t PHA();    uint8_t STX();
	uint8_t BRK();    uint8_t EOR();    uint8_t PHP();    uint8_t STY();
	uint8_t BVC();    uint8_t INC();    uint8_t PLA();    uint8_t TAX();
	uint8_t BVS();    uint8_t INX();    uint8_t PLP();    uint8_t TAY();

	uint8_t XXX(); 

	//read and write operations/  connecting with the bus 
	void write(uint8_t data, uint16_t address);
	uint8_t read(uint16_t address);
	

private: 
	Bus* bus = nullptr; 

};
