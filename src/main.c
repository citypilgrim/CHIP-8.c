#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern void DisassembleChip8Op(uint8_t *codebuffer, int pc);

int main(int argc, char **argv) {
  FILE *f = fopen(argv[1], "rb");
  if (f == NULL) {
    printf("error: Couldn't open %s\n", argv[1]);
    exit(1);
  }

  // Get the file size
  fseek(f, 0L, SEEK_END);       /* move file pointer to end of file */
  int fsize = ftell(f);         /* get current position of file pointer within the file in bytes */
  fseek(f, 0L, SEEK_SET);       /* go back to the start of the file */

  // CHIP-8 convention puts programs in memory at 0x200
  //  They will all have hardcoded addresses expecting that

  /* reads entire rom into buffer */
  unsigned char *buffer = malloc(fsize + 0x200); /* allocate space in memory */
  fread(buffer + 0x200, fsize, 1, f); /* reads file into buffer */
  fclose(f);

  int pc = 0x200;
  while (pc < (fsize + 0x200)) {
    DisassembleChip8Op(buffer, pc);
    pc += 2;                    /* chip8 opcode is 2 bytes long  */
    printf("\n");
  }
  return 0;
}
