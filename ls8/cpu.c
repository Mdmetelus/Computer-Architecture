#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"

#define DATA_LEN 6

#define LDI 0b10000010
#define NOP 0b00000000
#define PRN 0b01000111
#define HLT 0b00000001
#define STR 0b00001000 // store the next value to reg

// reading whats in ram
int cpu_ram_read(struct cpu *cpu, unsigned char mar) {
  return cpu->ram[mar];
}

// write to the ram
void cpu_ram_write(struct cpu *cpu, unsigned char mdr) {
  char *space = malloc(cpu->ram, sizeof(cpu->ram));
  for (int i = 0; i < sizeof(cpu->ram); i++) {
    if (cpu->ram[i] == '/0') {
      cpu->ram[i] = space;
    }
    else {
      printf("There is no space available");
    }
  }
  // cpu->ram[mdr] = mdr
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *filename)
{
  char data[DATA_LEN] = {
      // From print8.ls8
      LDI, // LDI R0,8
      NOP,
      STR, 
      8,   
      PRN, 
      NOP,
      HLT // HLT
      // 0b10000010, // LDI R0,8
      // 0b00000000,
      // 0b00001000,
      // 0b01000111, // PRN R0
      // 0b00000000,
      // 0b00000001  // HLT

  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    if (data[i] == STR)
    {
      cpu->registers[address] = data[i + 1];
    }
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  // 
  for (int i = 0; i < 6; i++)
  {
    
    cpu->registers[i] = 0;
  }
  
  cpu->registers[7] = '0xF4';
  
  cpu->PC = 0;
  
  void memset(cpu->ram, 0, sizeof(cpu->ram));
}
