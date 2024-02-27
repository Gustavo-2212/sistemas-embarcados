#include <stdlib.h>

#include "config.h"

char version[] = {'V', '1', '.', '0'};

int main(int argc, char **argv) {

    while(1);

    return EXIT_SUCCESS;
}

// Compilar até, imediatamente antes, a etapa de Linkagem
// > arm-none-eabi-gcc main.c -c -O0 -mcpu=cortex-m4 -mthumb -Wall

// Verificar as seções do arquivo objeto criado
// > arm-none-eabi-objdump -h main.o

// Verificar as seções de um arquivo objeto realocável
// > arm-none-eabi-objdump -s main.o
// > arm-none-eabi-objdump -S main.o
// > arm-none-eabi-objdump -s -j .data main.o

// Verificar uma seção específica
// > arm-none-eabi-objdump -d -j .text main.o
