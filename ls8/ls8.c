#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

/**
 * Main
 */
// int main(int argc, char **argv)
// {
  // struct cpu cpu;
// 
  // if (argc != 2)
  // {
    // printf("Usage: ls8.c <filename>");
    // exit(1);
// }

//   
//   char *filename = argv[1];
//   cpu_init(&cpu);
//   // pass input to load
//   cpu_load(&cpu, filename);
//   cpu_run(&cpu);

//   return 0;
// }

// int main(void) 
int main(int argc, char *argv[])
{
  struct cpu cpu;

  cpu_init(&cpu);
  cpu_load(&cpu, argc, argv);
  cpu_run(&cpu);

  return 0;
}