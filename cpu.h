#pragma once
#include <stdint.h>
#include <stdio.h>
void setIRQ(bool v);
void setNMI(bool v);

struct Registers
{
	unsigned char A;
	unsigned char X;
	unsigned char Y;
};

struct Status
{
	uint8_t status = 0x24;	//	TODO usually 0x34 on power up 
	uint8_t carry = 0;
	uint8_t zero = 0;
	uint8_t interruptDisable = 1;
	uint8_t decimal = 0;
	uint8_t overflow = 0;
	uint8_t negative = 0;
	uint8_t brk = 0;

	void setCarry(uint8_t v) {
		carry = v;
		status = (status & ~1) | carry;
	}

	void setZero(uint8_t v) {
		zero = v;
		status = (status & ~2) | (zero << 1);
	}

	void setInterruptDisable(uint8_t v) {
		interruptDisable = v;
		status = (status & ~4) | (interruptDisable << 2);
	}

	void setDecimal(uint8_t v) {
		decimal = v;
		status = (status & ~8) | (decimal << 3);
	}

	void setOverflow(uint8_t v) {
		overflow = v;
		status = (status & ~64) | (overflow << 6);
	}

	void setNegative(uint8_t v) {
		negative = v;
		status = (status & ~128) | (negative << 7);
	}

	void setBrk(uint8_t v) {
		brk = v;
		status = (status & ~16) | (brk << 4);
	}

	void setStatus(uint8_t s) {
		status = s | 0x20;
		setCarry(s & 1);
		setZero((s >> 1) & 1);
		setInterruptDisable((s >> 2) & 1);
		setDecimal((s >> 3) & 1);
		setBrk((s >> 4) & 1);
		setOverflow((s >> 6) & 1);
		setNegative((s >> 7) & 1);
	}

};

enum class ADDR_MODE {
	ACCUMULATOR,
	ABSOLUT,
	ABSOLUT_X,
	ABSOLUT_Y,
	INDIRECT,
	INDIRECT_Y,
	INDIRECT_X,
	ZEROPAGE,
	ZEROPAGE_X,
	ZEROPAGE_Y,
	IMMEDIATE
};

uint8_t CPU_executeInstruction();
void resetCPU();