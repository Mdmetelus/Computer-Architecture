#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"

#define DATA_LEN 6
#define SP 7

// #define LDI 0b10000010
// #define NOP 0b00000000
// #define PRN 0b01000111
// #define HLT 0b00000001
// #define STR 0b00001000 // store the next value to reg

// reading whats in ram
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char mar) {
  return cpu->ram[mar];
}

// write to the ram
void cpu_ram_write(struct cpu *cpu, unsigned char mar, unsigned char mdr)
{
  cpu->ram[mdr] = mdr;
}


    void cpu_push(struct cpu *cpu, unsigned char val)
{
  // decrement
  cpu->registers[SP]--;
  
  cpu_ram_write(cpu, cpu->registers[SP], val);
}

unsigned char cpu_pop(struct cpu *cpu) {
  unsigned char val = cpu_ram_read(cpu, cpu->registers[SP]);
  // Increment 
  cpu->registers[SP]++;
  return val;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *filename) {

  FILE *fp = fopen(filename, "r");

  if (fp == NULL)
  {
    // fprintf(stderr, "Error: unable to open file %s\n", file);
    // exit(1);
    fprintf(stderr, "Error cannot open this file:  %s\n", filename);
    exit(2);
  }
  char line[8192]; 
  int address = 0;

  while (fgets(line, sizeof(line), fp) != NULL)
  {
    char *endptr; 
    
    unsigned char byte = strtoul(line, &endptr, 2);

    if (endptr == line)
    {
      continue;
    }
    cpu->ram[address++] = byte;
  }
  fclose(fp);
}

/**
 * ALU
 */
// void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
// {
//   switch (op) {
//     case ALU_MUL:
//       // TODO
//       cpu->registers[regA] *= regB;
//       break;
//     case ALU_ADD:
//       cpu->registers[regA] = regA + regB;
//       break;
//     case ALU_NOP:
//       // No operation. Do nothing at this instruction
//       cpu->registers[regA] += regB;
//       break;
//     case ALU_NOT:
//       break;

//     // TODO: implement more ALU ops
//     case ALU_POP:
      
//       break;
//     case ALU_PRA:
      
//       break;
//     case ALU_PRN:
//       break;
//     case ALU_PUSH:
      
//       break;
//     case ALU_RET:
      
//       break;
//     default:
//       break;
//   }
// }

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1;

  unsigned char command, operand1, operand2;

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
    unsigned char command = cpu->ram[cpu->PC];

    // unsigned int combined_operands = command >> 6;

    // unsigned int operand1;
    // unsigned int operand2;
    // if (combined_operands == 2)
    // {
    //   operand1 = cpu->ram[cpu->PC + 1];
    //   operand2 = cpu->ram[cpu->PC + 2];
    // }
    // else if (combined_operands == 1)
    // {
    //   operand1 = cpu->ram[cpu->PC + 1];
    // }
    command = cpu_ram_read(cpu, cpu->PC);

    operand1 = cpu_ram_read(cpu, cpu->PC + 1);
    operand2 = cpu_ram_read(cpu, cpu->PC + 2);

    switch (command)
    {
      // LDI
    case LDI:
      
      cpu->registers[operand1] = operand2;
      
      cpu->PC += 3;
      break;
      // PRN
    case PRN:
      printf("%d\n", cpu->registers[operand1]);
      cpu->PC += 2;
      break;
      // MUL
    case MUL:
      cpu->registers[operand1] *= operand2;
      cpu->PC += 3;
      break;
    case PUSH:
      cpu_push(cpu, cpu->registers[operand1]);
      cpu->PC += 2;
      break;
    case POP:
      cpu->registers[operand1] = cpu_pop(cpu);
      cpu->PC += 2;
      break;
    case HLT:
      running = 0;
      cpu->PC += 1;
      break;
    default:
      printf("Cannot complete this command\n");
      exit(1);
      break;
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
