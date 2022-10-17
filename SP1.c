#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char byte;
#define LOAD_MEM 0
#define LOAD_VAL 1
#define STORE 2
#define ADD 3
#define SUB 4
#define MUL 5
#define DIV 6
#define INC 7
#define DEC 8
#define AND 9
#define OR 10
#define NOT 11
#define JMP 12
#define JZ 13
#define JNZ 14
#define HLT 15

typedef struct
{
    byte opcode;
    byte operand;
} instruction;

int main(int argc, char const *argv[])
{
    FILE *file = fopen("test.bin", "rb");

    byte mem[256];
    byte temp;
    instruction program[256];
    int pc = 0, acc = 0, status = 0;

    while (fread(&program[pc].opcode, sizeof(char), 1, file) != 0)
    {
        fread(&program[pc].operand, sizeof(char), 1, file); // lê o binário de um arquivo e armazena em um vetor program[i].opcode e program[i].operand
        pc = pc + 1;
    }
    ///*
    pc = 0;

    while (program[pc].opcode != HLT)
    {
        switch (program[pc].opcode)
        {
        case LOAD_MEM:
            acc = mem[program[pc].operand];
            pc = pc + 1;
            break;

        case LOAD_VAL:
            acc = program[pc].operand;
            pc = pc + 1;
            break;

        case STORE:
            mem[program[pc].operand] = acc;
            pc = pc + 1;
            break;

        case ADD:
            acc = acc + mem[program[pc].operand];
            if (acc >= 256)
            {
                status = 2;
                acc = acc & 255;
            }
            if (acc == 0)
            {
                // SET ZERO FLAG
                status = 1;
            }
            else
            {
                status = 0;
            }
            pc = pc + 1;
            break;

        case SUB:
            acc = acc - mem[program[pc].operand];
            if (acc == 0)
            {
                status = 1;
            }

            pc = pc + 1;
            break;

        case MUL:
            acc = acc * mem[program[pc].operand];
            if (acc >= 256)
            {
                // SET STATUS OVERFLOW
                status = 4;
                acc = acc & 255;
            }
            if (acc == 0)
            {
                // SET ZERO FLAG
                status = 1;
            }
            else if (acc < 256)
            {
                // UNSET ZERO FLAG
                status = 0;
            }
            pc = pc + 1;
            break;

        case DIV:
            acc = acc / mem[program[pc].operand];
            pc = pc + 1;
            break;

        case INC:
            acc = acc + 1;
            if (acc >= 256)
            {
                // SET STATUS CARRY
                status = 2;
                acc = acc & 255;
            }
            if (acc == 0)
            {
                // SET ZERO FLAG 00000OCZ
                status = 1;
            }
            else if (acc < 256)
            {
                // UNSET ZERO FLAG
                status = 0;
            }
            pc = pc + 1;
            break;

        case DEC:
            acc = acc - 1;
            pc = pc + 1;
            break;
        case AND:
            acc = acc & mem[program[pc].operand];
            pc = pc + 1;
            break;
        case OR:
            acc = acc | mem[program[pc].operand];
            pc = pc + 1;
            break;
        case NOT:
            acc = ~acc;
            pc = pc + 1;
            break;

        case JMP:
            pc = program[pc].operand;
            break;

        case JZ:
            if (status & 4)
            {
                pc = program[pc].operand;
            }
        case JNZ:
            if (status != 4)
            {
                pc = program[pc].operand;
            }

            break;
        }
        if (acc == 0)
        {
            status = 1;
        }
        else if (status != 2 && status != 4)
        {
            status = 0;
        }

        // pc = pc + 1; <-- Colocar em todos menos no jump
    }
    //*/
    printf("ACC:%d\nSTATUS:%d\n", acc, status);
    // printf("opcode: %d\noperand: %d\nPC: %d", program[1].opcode, program[1].operand, pc);
    return 0;
}
