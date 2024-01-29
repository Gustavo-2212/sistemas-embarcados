#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE   (128U * 1024U)
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END

extern uint32_t _start_data;            /* Inicio da secao .data */
extern uint32_t _end_data;              /* Fim da secao .data */
extern uint32_t _start_bss;             /* Inicio da secao .bss */
extern uint32_t _end_bss;               /* Fim da secao .bss */
extern uint32_t _address_data;          /* Endereco de carga na FLASH da secao .data */

void reset_handler(void);
void nmi_handler(void)                      __attribute__((weak, alias("default_handler")));
void memmanage_handler(void)                __attribute__((weak, alias("default_handler")));
void hardfault_handler(void)                __attribute__((weak, alias("default_handler")));
void busfault_handler(void)                 __attribute__((weak, alias("default_handler")));
void usagefault_handler(void)               __attribute__((weak, alias("default_handler")));
void svc_handler(void)                      __attribute__((weak, alias("default_handler")));
void debugmon_handler(void)                 __attribute__((weak, alias("default_handler")));
void pendsv_handler(void)                   __attribute__((weak, alias("default_handler")));
void systick_handler(void)                  __attribute__((weak, alias("default_handler")));

uint32_t vector[] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (uint32_t) reset_handler,               /* 0x0000 0004 */
    (uint32_t) nmi_handler,                 /* 0x0000 0008 */
    (uint32_t) hardfault_handler,           /* 0x0000 000c */
    (uint32_t) memmanage_handler,           /* 0x0000 0010 */
    (uint32_t) busfault_handler,            /* 0x0000 0014 */
    (uint32_t) usagefault_handler,          /* 0x0000 0018 */
    0,                                      /* 0x0000 001c   (RESERVED) */
    0,                                      /* 0x0000 0020   (RESERVED) */
    0,                                      /* 0x0000 0024   (RESERVED) */
    0,                                      /* 0x0000 0028   (RESERVED) */
    (uint32_t) svc_handler,                 /* 0x0000 002c */
    (uint32_t) debugmon_handler,            /* 0x0000 0030 */
    0,                                      /* 0x0000 0034 */
    (uint32_t) pendsv_handler,              /* 0x0000 0038   (RESERVED) */
    (uint32_t) systick_handler,             /* 0x0000 003c */
};

void reset_handler(void) {
    uint32_t i;

    /* Copia a seção .data da FLASH para a SRAM */
    uint32_t size    = (uint32_t) &_end_data - (uint32_t) &_start_data;
    uint8_t *destiny = (uint8_t*) &_start_data;
    uint8_t *source  = (uint8_t*) &_address_data;

    for(i = 0; i < size; i++) *destiny++ = *source++;

    /* Inicializa a seção .bss com 0 */
    size = (uint32_t) &_end_bss - (uint32_t) &_start_bss;
    destiny = (uint8_t*) &_start_bss;
    
    for(i = 0; i < size; i++) *destiny++ = 0;

    /* Chama a função main */
    main();
}

void default_handler(void) {
    while(1);                   // por enquanto, como tratamento apenas trava o código
}