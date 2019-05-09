#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"

#define DATA_LEN 6

// #define LDI 0b10000010
// #define NOP 0b00000000
// #define PRN 0b01000111
// #define HLT 0b00000001
// #define STR 0b00001000 // store the next value to reg

// reading whats in ram
int cpu_ram_read(struct cpu *cpu, unsigned char mar) {
  return cpu->ram[mar];
}

// write to the ram
void cpu_ram_write(struct cpu *cpu, unsigned char mdr) {
  // char *space = malloc(cpu->ram, sizeof(cpu->ram));
  // for (int i = 0; i < sizeof(cpu->ram); i++) {
  //   if (cpu->ram[i] == '/0') {
  //     cpu->ram[i] = space;
  //   }
  //   else {
  //     printf("There is no space available");
  //   }
  // }
  cpu->ram[mdr] = mdr;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{

  char data[DATA_LEN] = {
      // From print8.ls8
      0b10000010, // LDI R0,8
      0b00000000,
      0b00001000,
      0b01000111, // PRN R0
      0b00000000,
      0b00000001 // HLT
  };


  // open file
  // FILE *fp = fopen(filename, "r");
  
  // if (fp == NULL)
  // {
  //   fprintf(stderr, "ls8: error opening file:  %s\n", filename);
  //   exit(2);
  // }

  // char line[9999]; 

  int address = 0;


  // while (fgets(line, sizeof(line), fp) != NULL)
  // {
  //   char *endptr; 
    
  //   unsigned char val = strtoul(line, &endptr, 2);
    
  //   if (line == endptr)
  //   {
  //     continue;
  //   }
  //   cpu->ram[address++] = val;
  // }

  for (int i = 0; i < DATA_LEN; i++)
  {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
  fclose(fp);
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      cpu->register[regA] = regA * regB;
      break;
    case ALU_ADD:
      cpu->registers[regA] = regA + regB;
      break;
    case ALU_NOP:
      // No operation. Do nothing at this instruction
      break;
    case ALU_NOT:
      break;

    // TODO: implement more ALU ops
    case ALU_POP:
      
      break;
    case ALU_PRA:
      
      break;
    case ALU_PRN:
      break;
    case ALU_PUSH:
      
      break;
    case ALU_RET:
      
      break;
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction
  // init current instructions
  unsigned char IR;
  // init operand 0 and 1
  unsigned char operand0;
  unsigned char operand1;
  unsigned char operand2;

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
    IR = cpu_ram_read(cpu, cpu->PC);

    operand1 = cpu_ram_read(cpu, cpu->PC + 1);
    operand2 = cpu_ram_read(cpu, cpu->PC + 2);

    switch (IR)
    {
      // LDI
    case LDI:
      
      cpu->registers[operand1] = operand2;
      
      cpu->PC += 3;
      break;
      // PRN
    case PRN:

      printf("Register: %d\n", cpu->registers[operand1]);
      printf("Register: %d\n", cpu->registers[operand2]);
      
      cpu->PC += 2;
      break;
      // HLT
    case HLT:
      running = 0; // stops the while loop
      // move the PC to the next instruction
      cpu->PC += 1;
      break;

      // MUL
    case MUL:
      break;
    default:
      printf("Issued an Unexpected instruction 0x%02X at 0x%02X\n", IR, cpu->PC);
      exit(1);
    }
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
  
  cpu->registers[7] = 0xF4;
  
  cpu->PC = 0;

  // RAM is set to 0
  memset(cpu->ram, 0, sizeof(cpu->ram));
}
