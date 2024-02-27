#include <stdint.h>

/*
    +---------------------------------------------------------------+
    |Diretivas relacionadas aos limites da memério volátil SRAM;    |
    |Diretiva relacionada ao limite da STACK.                       |
    +---------------------------------------------------------------+
*/
#define SRAM_START  0x20000000U
#define SRAM_SIZE   (128U * 1024U)
#define SRAM_END    ((SRAM_START) + (SRAM_SIZE))

#define STACK_START SRAM_END


/*
    +---------------------------------------------------------------+
    |Variáveis externas relacionadas ao tamanho e limites das seções|
    |.data (SRAM e FLASH) e .bss (SRAM).                            |
    +---------------------------------------------------------------+
*/
extern uint32_t _sdata;            /* Inicio da seção .data */
extern uint32_t _edata;             /* Fim da secão .data */
extern uint32_t _la_data;          /* Endereço de carga da FLASH da seção .data */

extern uint32_t _sbss;             /* Início da secão .bss */
extern uint32_t _ebss;             /* Fim da seção .bss */

int main(void);

/*
    +--------------------------------------------------------+
    |Protótipos das funções para tratamento das interrupções.|
    +--------------------------------------------------------+
*/
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
void wwdg_handler(void)                     __attribute__((weak, alias("default_handler")));
void exti16_handler(void)                   __attribute__((weak, alias("default_handler")));
void exti21_handler(void)                   __attribute__((weak, alias("default_handler")));
void exti22_handler(void)                   __attribute__((weak, alias("default_handler")));
void flash_handler(void)                    __attribute__((weak, alias("default_handler")));
void rcc_handler(void)                      __attribute__((weak, alias("default_handler")));
void exti0_handler(void)                    __attribute__((weak, alias("default_handler")));
void exti1_handler(void)                    __attribute__((weak, alias("default_handler")));
void exti2_handler(void)                    __attribute__((weak, alias("default_handler")));
void exti3_handler(void)                    __attribute__((weak, alias("default_handler")));
void exti4_handler(void)                    __attribute__((weak, alias("default_handler")));
void dma1_stream0_handler(void)             __attribute__((weak, alias("default_handler")));
void dma1_stream1_handler(void)             __attribute__((weak, alias("default_handler")));
void dma1_stream2_handler(void)             __attribute__((weak, alias("default_handler")));
void dma1_stream3_handler(void)             __attribute__((weak, alias("default_handler")));
void dma1_stream4_handler(void)             __attribute__((weak, alias("default_handler")));
void dma1_stream5_handler(void)             __attribute__((weak, alias("default_handler")));
void dma1_stream6_handler(void)             __attribute__((weak, alias("default_handler")));
void adc_handler(void)                      __attribute__((weak, alias("default_handler")));
void exti9_5_handler(void)                  __attribute__((weak, alias("default_handler")));
void tim1_brk_tim9_handler(void)            __attribute__((weak, alias("default_handler")));
void tim1_up_tim10_handler(void)            __attribute__((weak, alias("default_handler")));
void tim1_trg_com_tim11_handler(void)       __attribute__((weak, alias("default_handler")));
void tim1_cc_handler(void)                  __attribute__((weak, alias("default_handler")));
void tim2_handler(void)                     __attribute__((weak, alias("default_handler")));
void tim3_handler(void)                     __attribute__((weak, alias("default_handler")));
void tim4_handler(void)                     __attribute__((weak, alias("default_handler")));
void i2c1_ev_handler(void)                  __attribute__((weak, alias("default_handler")));
void i2c1_er_handler(void)                  __attribute__((weak, alias("default_handler")));
void i2c2_ev_handler(void)                  __attribute__((weak, alias("default_handler")));
void i2c2_er_handler(void)                  __attribute__((weak, alias("default_handler")));
void spi1_handler(void)                     __attribute__((weak, alias("default_handler")));
void spi2_handler(void)                     __attribute__((weak, alias("default_handler")));
void usart1_handler(void)                   __attribute__((weak, alias("default_handler")));
void usart2_handler(void)                   __attribute__((weak, alias("default_handler")));
void exti15_10_handler(void)                __attribute__((weak, alias("default_handler")));
void exti17_handler(void)                   __attribute__((weak, alias("default_handler")));
void exti18_handler(void)                   __attribute__((weak, alias("default_handler")));
void dma1_stream7_handler(void)             __attribute__((weak, alias("default_handler")));
void sdio_handler(void)                     __attribute__((weak, alias("default_handler")));
void tim5_handler(void)                     __attribute__((weak, alias("default_handler")));
void spi3_handler(void)                     __attribute__((weak, alias("default_handler")));
void dma2_stream0_handler(void)             __attribute__((weak, alias("default_handler")));
void dma2_stream1_handler(void)             __attribute__((weak, alias("default_handler")));
void dma2_stream2_handler(void)             __attribute__((weak, alias("default_handler")));
void dma2_stream3_handler(void)             __attribute__((weak, alias("default_handler")));
void dma2_stream4_handler(void)             __attribute__((weak, alias("default_handler")));
void otgfs_handler(void)                    __attribute__((weak, alias("default_handler")));
void dma2_stream5_handler(void)             __attribute__((weak, alias("default_handler")));
void dma2_stream6_handler(void)             __attribute__((weak, alias("default_handler")));
void dma2_stream7_handler(void)             __attribute__((weak, alias("default_handler")));
void usart6_handler(void)                   __attribute__((weak, alias("default_handler")));
void i2c3_ev_handler(void)                  __attribute__((weak, alias("default_handler")));
void i2c3_er_handler(void)                  __attribute__((weak, alias("default_handler")));
void fpu_handler(void)                      __attribute__((weak, alias("default_handler")));
void spi4_handler(void)                     __attribute__((weak, alias("default_handler")));
void spi5_handler(void)                     __attribute__((weak, alias("default_handler")));


/*
    +----------------------+
    |Vetor de interrupções.|
    +----------------------+
*/
uint32_t vector[] __attribute__((section(".isr_vector"))) = {
    STACK_START,                            /* STACK POINTER */
    (uint32_t) reset_handler,               /* 0x0000 0004 */
    (uint32_t) nmi_handler,                 /* 0x0000 0008 */
    (uint32_t) hardfault_handler,           /* 0x0000 000C */
    (uint32_t) memmanage_handler,           /* 0x0000 0010 */
    (uint32_t) busfault_handler,            /* 0x0000 0014 */
    (uint32_t) usagefault_handler,          /* 0x0000 0018 */
    0,                                       /* 0x0000 001C   (RESERVED) */
    0,                                       /* 0x0000 0020   (RESERVED) */
    0,                                       /* 0x0000 0024   (RESERVED) */
    0,                                       /* 0x0000 0028   (RESERVED) */
    (uint32_t) svc_handler,                 /* 0x0000 002C */
    (uint32_t) debugmon_handler,            /* 0x0000 0030 */
    0,                                       /* 0x0000 0034   (RESERVED) */
    (uint32_t) pendsv_handler,              /* 0x0000 0038 */
    (uint32_t) systick_handler,             /* 0x0000 003C */
    (uint32_t) wwdg_handler,                /* 0x0000 0040 */
    (uint32_t) exti16_handler,              /* 0x0000 0044 */
    (uint32_t) exti21_handler,              /* 0x0000 0048 */
    (uint32_t) exti22_handler,              /* 0x0000 004C */
    (uint32_t) flash_handler,               /* 0x0000 0050 */
    (uint32_t) rcc_handler,                 /* 0x0000 0054 */
    (uint32_t) exti0_handler,               /* 0x0000 0058 */
    (uint32_t) exti1_handler,               /* 0x0000 005C */
    (uint32_t) exti2_handler,               /* 0x0000 0060 */
    (uint32_t) exti3_handler,               /* 0x0000 0064 */
    (uint32_t) exti4_handler,               /* 0x0000 0068 */
    (uint32_t) dma1_stream0_handler,        /* 0x0000 006C */
    (uint32_t) dma1_stream1_handler,        /* 0x0000 0070 */
    (uint32_t) dma1_stream2_handler,        /* 0x0000 0074 */
    (uint32_t) dma1_stream3_handler,        /* 0x0000 0078 */
    (uint32_t) dma1_stream4_handler,        /* 0x0000 007C */
    (uint32_t) dma1_stream5_handler,        /* 0x0000 0080 */
    (uint32_t) dma1_stream6_handler,        /* 0x0000 0084 */
    (uint32_t) adc_handler,                 /* 0x0000 0088 */
    0,                                       /* 0x0000 008C */
    0,                                       /* 0x0000 0090 */
    0,                                       /* 0x0000 0094 */
    0,                                       /* 0x0000 0098 */
    (uint32_t) exti9_5_handler,             /* 0x0000 009C */
    (uint32_t) tim1_brk_tim9_handler,       /* 0x0000 00A0 */
    (uint32_t) tim1_up_tim10_handler,       /* 0x0000 00A4 */
    (uint32_t) tim1_trg_com_tim11_handler,  /* 0x0000 00A8 */
    (uint32_t) tim1_cc_handler,             /* 0x0000 00AC */
    (uint32_t) tim2_handler,                /* 0x0000 00B0 */
    (uint32_t) tim3_handler,                /* 0x0000 00B4 */
    (uint32_t) tim4_handler,                /* 0x0000 00B8 */
    (uint32_t) i2c1_ev_handler,             /* 0x0000 00BC */
    (uint32_t) i2c1_er_handler,             /* 0x0000 00C0 */
    (uint32_t) i2c2_ev_handler,             /* 0x0000 00C4 */
    (uint32_t) i2c2_er_handler,             /* 0x0000 00C8 */
    (uint32_t) spi1_handler,                /* 0x0000 00CC */
    (uint32_t) spi2_handler,                /* 0x0000 00D0 */
    (uint32_t) usart1_handler,              /* 0x0000 00D4 */
    (uint32_t) usart2_handler,              /* 0x0000 00D8 */
    0,                                      /* 0x0000 00DC */
    (uint32_t) exti15_10_handler,           /* 0x0000 00E0 */
    (uint32_t) exti17_handler,              /* 0x0000 00E4 */
    (uint32_t) exti18_handler,              /* 0x0000 00E8 */
    0,                                      /* 0x0000 00EC */
    0,                                      /* 0x0000 00F0 */
    0,                                      /* 0x0000 00F4 */
    0,                                      /* 0x0000 00F8 */
    (uint32_t) dma1_stream7_handler,        /* 0x0000 00FC */
    0,                                      /* 0x0000 0100 */
    (uint32_t) sdio_handler,                /* 0x0000 0104 */
    (uint32_t) tim5_handler,                /* 0x0000 0108 */
    (uint32_t) spi3_handler,                /* 0x0000 010C */
    0,                                       /* 0x0000 0110 */
    0,                                       /* 0x0000 0114 */
    0,                                       /* 0x0000 0118 */
    0,                                       /* 0x0000 011C */
    (uint32_t) dma2_stream0_handler,        /* 0x0000 0120 */
    (uint32_t) dma2_stream1_handler,        /* 0x0000 0124 */
    (uint32_t) dma2_stream2_handler,        /* 0x0000 0128 */
    (uint32_t) dma2_stream3_handler,        /* 0x0000 012C */
    (uint32_t) dma2_stream4_handler,        /* 0x0000 0130 */
    0,                                       /* 0x0000 0134 */
    0,                                       /* 0x0000 0138 */
    0,                                       /* 0x0000 013C */
    0,                                       /* 0x0000 0140 */
    0,                                       /* 0x0000 0144 */
    0,                                       /* 0x0000 0148 */
    (uint32_t) otgfs_handler,               /* 0x0000 014C */
    (uint32_t) dma2_stream5_handler,        /* 0x0000 0150 */
    (uint32_t) dma2_stream6_handler,        /* 0x0000 0154 */
    (uint32_t) dma2_stream7_handler,        /* 0x0000 0158 */
    (uint32_t) usart6_handler,              /* 0x0000 015C */
    (uint32_t) i2c3_ev_handler,             /* 0x0000 0160 */
    (uint32_t) i2c3_er_handler,             /* 0x0000 0164 */
    0,                                       /* 0x0000 0168 */
    0,                                       /* 0x0000 016C */
    0,                                       /* 0x0000 0170 */
    0,                                       /* 0x0000 0174 */
    0,                                       /* 0x0000 0178 */
    0,                                       /* 0x0000 017C */
    0,                                       /* 0x0000 0180 */
    (uint32_t) fpu_handler,                 /* 0x0000 0184 */
    0,                                       /* 0x0000 0188 */
    0,                                       /* 0x0000 018C */
    (uint32_t) spi4_handler,                /* 0x0000 0190 */
    (uint32_t) spi5_handler,                /* 0x0000 0194 */
};

/*
    +--------------------------------------------------------+
    |Implementação das funções de tratamento de interrupções.|
    +--------------------------------------------------------+
*/
void reset_handler(void) {
    uint32_t i;

    /* Copia a seção .data da FLASH para a SRAM */
    uint32_t size    = (uint32_t) &_edata - (uint32_t) &_sdata;
    uint8_t *destiny = (uint8_t*) &_sdata;
    uint8_t *source  = (uint8_t*) &_la_data;

    for(i = 0; i < size; i++)
        *destiny++ = *source++;

    /* Inicializa a seção .bss com 0 */
    size = (uint32_t) &_ebss - (uint32_t) &_sbss;
    destiny = (uint8_t*) &_sbss;
    
    for(i = 0; i < size; i++)
        *destiny++ = 0;

    /* Chama a função main */
    main();
}

void default_handler(void) {
    while(1);                   // por enquanto, como tratamento apenas trava o código
}