#include "Bus.h"
#include <vector>

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
	uint8_t ACUM();    uint8_t IMPL();
	uint8_t IMM();	   uint8_t REL();
	uint8_t ZP();      uint8_t IND();
	uint8_t ZPX();	   uint8_t INDX();
	uint8_t ZPY();     uint8_t INDY();
	uint8_t ABS();
	uint8_t ABSX(); 
	uint8_t ABSY(); 

	uint8_t XXXX();
	

	//http://datasheets.chipdb.org/Rockwell/6502.pdf
	//opcodes (including ones with multiple addressing modes) 
	uint8_t ADC(); uint8_t AND(); uint8_t ASL(); uint8_t BCC(); uint8_t BCS(); 
	uint8_t BEQ(); uint8_t BIT(); uint8_t BMI(); uint8_t BNE(); uint8_t BPL(); 
	uint8_t BRK(); uint8_t BVC(); uint8_t BVS(); uint8_t CLC(); uint8_t CLD(); 
	uint8_t CLI(); uint8_t CLV(); uint8_t CMP(); uint8_t CPX(); uint8_t CPY(); 
	uint8_t DEC(); uint8_t DEX(); uint8_t DEY(); uint8_t EOR(); uint8_t INC();
	uint8_t INX(); uint8_t INY(); uint8_t JMP(); uint8_t JSR(); uint8_t LDA(); 
	uint8_t LDX(); uint8_t LDY(); uint8_t LSR(); uint8_t NOP(); uint8_t ORA(); 
	uint8_t PHA(); uint8_t PHP(); uint8_t PLA(); uint8_t PLP(); uint8_t ROL(); 
	uint8_t ROR(); uint8_t RTI(); uint8_t RTS(); uint8_t SBC(); uint8_t SEC(); 
	uint8_t SED(); uint8_t SEI(); uint8_t STA(); uint8_t STX(); uint8_t STY(); 
	uint8_t TAX(); uint8_t TAY(); uint8_t TSX(); uint8_t TXA(); uint8_t TXS(); 
	uint8_t TYA();

	//opcodes not available in NMOS family 
	/*
	uint8_t BBR(); uint8_t BBS(); uint8_t BRA(); uint8_t PHX(); uint8_t PHY(); 
	uint8_t PLX(); uint8_t PLY(); uint8_t RMB(); uint8_t SMB(); uint8_t STZ(); 
	uint8_t TRB(); uint8_t TSB(); 
	*/

	uint8_t XXX(); 

	//now need a lookup table for the opcodes 
	struct INSTRUCTION {
		uint8_t (CPU::*opcode)();
		uint8_t(CPU::*addressingMode)(); 
		uint8_t instruByte; 
		uint8_t machineCycle;
	};


	//not including new opcode 
	std::vector<INSTRUCTION> instructionSet = { {&CPU::BRK, &CPU::IMPL, 1, 7}, {&CPU::ORA, &CPU::INDX, 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::ORA, &CPU::ZP  , 2, 3}, {&CPU::ASL, &CPU::ZP  , 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::PHP, &CPU::IMPL, 1, 3}, {&CPU::ORA, &CPU::IMM , 2, 2}, {&CPU::ASL, &CPU::ACUM, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::ORA, &CPU::ABS , 3, 4}, {&CPU::ASL, &CPU::ABS , 3, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0},
												{&CPU::BPL, &CPU::REL , 2, 2}, {&CPU::ORA, &CPU::INDY, 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::ORA, &CPU::ZPX , 2, 4}, {&CPU::ASL, &CPU::ZPX , 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::CLC, &CPU::IMPL, 1, 2}, {&CPU::ORA, &CPU::ABSY, 3, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::ORA, &CPU::ABSX, 3, 4}, {&CPU::ASL, &CPU::ABSX, 3, 7}, {&CPU::XXX, &CPU::XXXX, 0, 0},
												{&CPU::JSR, &CPU::ABS , 3, 6}, {&CPU::AND, &CPU::INDX, 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::BIT, &CPU::ZP  , 2, 3}, {&CPU::AND, &CPU::ZP  , 2, 3}, {&CPU::ROL, &CPU::ZP  , 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::PLP, &CPU::IMPL, 1, 4}, {&CPU::AND, &CPU::IMM , 2, 2}, {&CPU::ROL, &CPU::ACUM, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::BIT, &CPU::ABS , 3, 4}, {&CPU::AND, &CPU::ABS , 3, 4}, {&CPU::ROL, &CPU::ABS , 3, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, 
												{&CPU::BMI, &CPU::REL , 2, 2}, {&CPU::AND, &CPU::INDY, 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::AND, &CPU::ZPX , 2, 4}, {&CPU::ROL, &CPU::ZPX , 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::SEC, &CPU::IMPL, 1, 2}, {&CPU::AND, &CPU::ABSY, 3, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::AND, &CPU::ABSX, 3, 4}, {&CPU::ROL, &CPU::ABSX, 3, 7}, {&CPU::XXX, &CPU::XXXX, 0, 0},
												{&CPU::RTI, &CPU::IMPL, 1, 6}, {&CPU::EOR, &CPU::INDX, 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::EOR, &CPU::ZP  , 2, 3}, {&CPU::LSR, &CPU::ZP  , 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::PHA, &CPU::IMPL, 1, 3}, {&CPU::EOR, &CPU::IMM , 2, 2}, {&CPU::LSR, &CPU::ACUM, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::JMP, &CPU::ABS , 3, 3}, {&CPU::EOR, &CPU::ABS , 3, 4}, {&CPU::LSR, &CPU::ABS , 3, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0},
												{&CPU::BVC, &CPU::REL , 2, 2}, {&CPU::EOR, &CPU::INDY, 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::EOR, &CPU::ZPX , 2, 4}, {&CPU::LSR, &CPU::ZPX , 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::CLI, &CPU::IMPL, 1, 2}, {&CPU::EOR, &CPU::ABSY, 3, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::EOR, &CPU::ABSX, 3, 4}, {&CPU::LSR, &CPU::ABSX, 3, 7}, {&CPU::XXX, &CPU::XXXX, 0, 0}, 
												{&CPU::RTS, &CPU::IMPL, 1, 6}, {&CPU::ADC, &CPU::INDX, 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::ADC, &CPU::ZP  , 2, 3}, {&CPU::ROR, &CPU::ZP  , 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::PLA, &CPU::IMPL, 1, 4}, {&CPU::ADC, &CPU::IMM , 2, 2}, {&CPU::ROR, &CPU::ACUM, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::JMP, &CPU::ABS , 3, 6}, {&CPU::ADC, &CPU::ABS , 3, 4}, {&CPU::ROR, &CPU::ABS , 3, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0},
												{&CPU::BVS, &CPU::REL , 2, 2}, {&CPU::ADC, &CPU::INDY, 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::ADC, &CPU::ZPX , 2, 4}, {&CPU::ROR, &CPU::ZPX , 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::SEI, &CPU::IMPL, 1, 2}, {&CPU::ADC, &CPU::ABSY, 3, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::ADC, &CPU::ABSX, 3, 4}, {&CPU::ROR, &CPU::ABSX, 3, 7}, {&CPU::XXX, &CPU::XXXX, 0, 0}, 
												{&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::STA, &CPU::INDX, 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::STY, &CPU::ZP  , 2, 3}, {&CPU::STA, &CPU::ZP  , 2, 3}, {&CPU::STX, &CPU::ZP  , 2, 3}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::DEY, &CPU::IMPL, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::TXA, &CPU::IMPL, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::STY, &CPU::ABS , 3, 4}, {&CPU::STA, &CPU::ABS , 3, 4}, {&CPU::STX, &CPU::ABS , 3, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, 
												{&CPU::BCC, &CPU::REL , 2, 2}, {&CPU::STA, &CPU::INDY, 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::STY, &CPU::ZPX , 2, 4}, {&CPU::STA, &CPU::ZPX , 2, 4}, {&CPU::STX, &CPU::ZPY , 2, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::TYA, &CPU::IMPL, 1, 2}, {&CPU::STA, &CPU::ABSY, 3, 5}, {&CPU::TXS, &CPU::IMPL, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::STA, &CPU::ABSX, 3, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, 
												{&CPU::LDY, &CPU::IMM , 2, 2}, {&CPU::LDA, &CPU::INDX, 2, 6}, {&CPU::LDX, &CPU::IMM , 2, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::LDY, &CPU::ZP  , 2, 3}, {&CPU::LDA, &CPU::ZP  , 2, 3}, {&CPU::LDX, &CPU::ZP  , 2, 3}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::TAY, &CPU::IMPL, 1, 2}, {&CPU::LDA, &CPU::IMM , 2, 2}, {&CPU::TAX, &CPU::IMPL, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::LDY, &CPU::ABS , 3, 4}, {&CPU::LDA, &CPU::ABS , 3, 4}, {&CPU::LDX, &CPU::ABS , 3, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, 
												{&CPU::BCS, &CPU::REL , 2, 2}, {&CPU::LDA, &CPU::INDY, 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::LDY, &CPU::ZPX , 2, 4}, {&CPU::LDA, &CPU::ZPX , 2, 4}, {&CPU::LDX, &CPU::ZPY , 2, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::CLV, &CPU::IMPL, 1, 2}, {&CPU::LDA, &CPU::ABSY, 3, 4}, {&CPU::TSX, &CPU::IMPL, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::LDY, &CPU::ABSX, 3, 4}, {&CPU::LDA, &CPU::ABSX, 3, 4}, {&CPU::LDX, &CPU::ABSY, 3, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, 
												{&CPU::CPY, &CPU::IMM , 2, 2}, {&CPU::CMP, &CPU::INDX, 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::CPY, &CPU::ZP  , 2, 3}, {&CPU::CMP, &CPU::ZP  , 2, 3}, {&CPU::DEC, &CPU::ZP  , 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::INY, &CPU::IMPL, 1, 2}, {&CPU::CMP, &CPU::IMM , 2, 2}, {&CPU::DEX, &CPU::IMPL, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::CPY, &CPU::ABS , 3, 4}, {&CPU::CMP, &CPU::ABS , 3, 4}, {&CPU::DEC, &CPU::ABS , 3, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, 
												{&CPU::BNE, &CPU::REL , 2, 2}, {&CPU::CMP, &CPU::INDY, 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::CMP, &CPU::ZPX , 2, 4}, {&CPU::DEC, &CPU::ZPX , 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::CLD, &CPU::IMPL, 1, 2}, {&CPU::CMP, &CPU::ABSY, 3, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::CMP, &CPU::ABSX, 3, 4}, {&CPU::DEC, &CPU::ABSX, 3, 7}, {&CPU::XXX, &CPU::XXXX, 0, 0}, 
												{&CPU::CPX, &CPU::IMM , 2, 2}, {&CPU::SBC, &CPU::INDX, 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::CPX, &CPU::ZP  , 2, 3}, {&CPU::SBC, &CPU::ZP  , 2, 3}, {&CPU::INC, &CPU::ZP  , 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::INX, &CPU::IMPL, 1, 2}, {&CPU::SBC, &CPU::IMM , 2, 2}, {&CPU::NOP, &CPU::IMPL, 1, 2}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::CPX, &CPU::ABS , 3, 4}, {&CPU::SBC, &CPU::ABS , 3, 4}, {&CPU::INC, &CPU::ABS , 3, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0},
												{&CPU::BEQ, &CPU::REL , 2, 2}, {&CPU::SBC, &CPU::INDY, 2, 5}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::SBC, &CPU::ZPX , 2, 4}, {&CPU::INC, &CPU::ZPX , 2, 6}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::SED, &CPU::IMPL, 1, 2}, {&CPU::SBC, &CPU::ABSY, 3, 4}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::XXX, &CPU::XXXX, 0, 0}, {&CPU::SBC, &CPU::ABSX, 3, 4}, {&CPU::INC, &CPU::ABSX, 3, 7}, {&CPU::XXX, &CPU::XXXX, 0, 0} };
	
	
	//for getting one clock cycles 
	void clock(); 
	uint8_t clockCount; 



	//read and write operations/  connecting with the bus 
	void write(uint8_t data, uint16_t address);
	uint8_t read(uint16_t address);
	

private: 
	Bus* bus = nullptr; 

};


