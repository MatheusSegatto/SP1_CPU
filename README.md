# SP1_CP1

SP1 is a hypothetical processor specified for purely academic purposes. It has three registers of 8 bits (1byte) each: acc (accumulator) stat (status) and pc (program counter). The SP1 processor ISA is composed of 16 instructions. The format of the instructions is fixed, in this case 16 bits (8 bits for the opcode and 8 bits for the operand). The stat register holds carry, overflow and zero information from the acc register.

## Goal:
* Develop an emulator, in C, for the SP1 CPU.
