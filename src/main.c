#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


/*  
    ------------------------------------------------------
    | Endereços base dos periféricos que vamos utilizar  |
    ------------------------------------------------------
*/
#define STM32_RCC_BASE  0x40023800
#define STM32_GPIOC_BASE 0x40020800


/*  
    ------------------------------------------------------
    | Offset dos registradores que vamos utilizar        |
    ------------------------------------------------------
*/
#define STM32_RCC_AHB1ENR_OFFSET    0x30

#define STM32_GPIOC_MODER_OFFSET    0x00
#define STM32_GPIOC_OTYPER_OFFSET   0x04
#define STM32_GPIOC_PUPDR_OFFSET    0x0c
#define STM32_GPIOC_ODR_OFFSET      0x14
#define STM32_GPIOC_BSRR_OFFSET     0x18


/*  
    ------------------------------------------------------
    | Registradores                                      |
    ------------------------------------------------------
*/
#define STM32_RCC_AHB1ENR       (STM32_RCC_BASE + STM32_RCC_AHB1ENR_OFFSET)
#define STM32_GPIOC_MODER       (STM32_GPIOC_BASE + STM32_GPIOC_MODER_OFFSET)
#define STM32_GPIOC_OTYPER      (STM32_GPIOC_BASE + STM32_GPIOC_OTYPER_OFFSET)
#define STM32_GPIOC_PUPDR       (STM32_GPIOC_BASE + STM32_GPIOC_PUPDR_OFFSET)
#define STM32_GPIOC_ODR         (STM32_GPIOC_BASE + STM32_GPIOC_ODR_OFFSET)
#define STM32_GPIOC_BSRR        (STM32_GPIOC_BASE + STM32_GPIOC_BSRR_OFFSET)


/*  
    ------------------------------------------------------
    | Ativando o clock da porta C de entrada/saída       |
    ------------------------------------------------------
*/
#define RCC_AHB1ENR_GPIOCEN     (1 << 2) // xxxx xxxx xxxx x1xx


/*  
    ------------------------------------------------------
    | Configurando o modo de acesso ao registrador MODER |
    ------------------------------------------------------
*/
#define GPIO_MODER_INPUT        (0)                         // 0 - Entrada
#define GPIO_MODER_OUTPUT       (1)                         // 1 - Saída
#define GPIO_MODER_ALTERNATE    (2)                         // 10 - Função Alternativa
#define GPIO_MODER_ANALOG       (3)                         // 11 - Função Analógica

#define GPIO_MODER_SHIFT(n) (n << 1)                        // n * 2 (acessa os bits correspondentes ao pino 'n')
#define GPIO_MODER_MASK(n)  (3 << GPIO_MODER_SHIFT(n))      // cria a máscara correspondente ao pino 'n'


/*  
    ------------------------------------------------------
    | Configurando o modo de acesso ao registrador OTYPER |
    ------------------------------------------------------
*/
#define GPIO_OTYPER_PP          (0)                     // Push Pull
#define GPIO_OTYPER_OD          (1)                     // Open Drain

#define GPIO_OTYPER_SHIFT(n)    (n)                     // acesso ao bit correspondente ao pino 'n'
#define GPIO_OTYPER_MASK(n)     (1 << n)                // cria a máscara correspondente ao pino 'n'


/*  
    ------------------------------------------------------
    | Configurando o modo de acesso ao registrador PUPDR |
    ------------------------------------------------------
*/
#define GPIO_PUPDR_NONE           (0)                       // Não faz uso dos resistores internos                     
#define GPIO_PUPDR_PULLUP         (1)                       // Resistores internos de Pull-Up
#define GPIO_PUPDR_PULLDOWN       (2)                       // Resistores internos de Pull-Down

#define GPIO_PUPDR_SHIFT(n) (n << 1)                        // (n * 2) -> acessa os bits correspondentes ao pino 'n'
#define GPIO_PUPDR_MASK(n)  (3 << GPIO_PUPDR_SHIFT(n))      // cria a máscara correspondente ao pino 'n'


/*  
    ------------------------------------------------------
    | Configurando o modo de acesso ao registrador BSRR  |
    ------------------------------------------------------
*/
#define GPIO_BSRR_SET(n)    (1 << n)                        // Modo de SETAR o bit correspondente ao pino 'n'
#define GPIO_BSRR_RESET(n)  (1 << (n + 16))                 // Modo de RESETAR o bit correspondente ao pino 'n'


/*  
    ------------------------------------------------------
    | Diretivas do contexto da aplicação                 |
    ------------------------------------------------------
*/
#define LED_DELAY   (5000)
#define PINO_lED    (13)

/*  
    ------------------------------------------------------
    | Tipos Privadas                                     |
    ------------------------------------------------------
*/

/*  
    ------------------------------------------------------
    | Protótipos de funções privadas                     |
    ------------------------------------------------------
*/

/*  
    ------------------------------------------------------
    | Dados privados                                     |
    ------------------------------------------------------
*/

/*  
    ------------------------------------------------------
    | Funções privadas                                   |
    ------------------------------------------------------
*/

/*  
    ------------------------------------------------------
    | Funções públicas                                   |
    ------------------------------------------------------
*/


char version[] = {'V', '1', '.', '0'};

int main(int argc, char* argv[]) {

    uint32_t i;
    uint32_t reg_tmp;

    // Ponteiros para os registradores
    uint32_t *pSTM32_RCC_AHB1ENR    = (uint32_t *) STM32_RCC_AHB1ENR;
    uint32_t *pSTM32_GPIOC_MODER    = (uint32_t *) STM32_GPIOC_MODER;
    uint32_t *pSTM32_GPIOC_OTYPER   = (uint32_t *) STM32_GPIOC_OTYPER;
    uint32_t *pSTM32_GPIOC_PUPDR    = (uint32_t *) STM32_GPIOC_PUPDR;
    uint32_t *pSTM32_GPIOC_BSRR     = (uint32_t *) STM32_GPIOC_BSRR;


    // Habilitando o clock na porta C para entrada e saída
    reg_tmp = *pSTM32_RCC_AHB1ENR;
    reg_tmp |= RCC_AHB1ENR_GPIOCEN;
    *pSTM32_RCC_AHB1ENR = reg_tmp; 


    // Configurando o modo de operação do pino que vamos utilizar, no caso o pino 13
    reg_tmp = *pSTM32_GPIOC_MODER;
    reg_tmp &= ~GPIO_MODER_MASK(PINO_lED);                              // Zera os bits que vamos manipular
    reg_tmp |= (GPIO_MODER_OUTPUT << GPIO_MODER_SHIFT(PINO_lED));       // Seta os bits de acordo com a finalidade
    *pSTM32_GPIOC_MODER = reg_tmp;


    // Configurando o modo de saída do pino
    reg_tmp = *pSTM32_GPIOC_OTYPER;
    reg_tmp &= ~GPIO_OTYPER_MASK(LED_DELAY);
    reg_tmp |= (GPIO_OTYPER_PP << GPIO_OTYPER_SHIFT(PINO_lED));
    *pSTM32_GPIOC_OTYPER = reg_tmp;


    // Configurando a possibilidade de usar os resistores internos de Pull-up e Pull-down
    reg_tmp = *pSTM32_GPIOC_PUPDR;
    reg_tmp &= ~GPIO_PUPDR_MASK(PINO_lED);
    reg_tmp |= (GPIO_PUPDR_NONE << GPIO_PUPDR_SHIFT(PINO_lED));
    *pSTM32_GPIOC_PUPDR = reg_tmp;

    while(true) {

        // Liga o Led (no nível baixo)
        *pSTM32_GPIOC_BSRR = GPIO_BSRR_RESET(PINO_lED);

        // Delay
        for(i = 0; i < LED_DELAY; i++);

        // Desliga o Led
        *pSTM32_GPIOC_BSRR = GPIO_BSRR_SET(PINO_lED);

        // Delay
        for(i = 0; i < LED_DELAY; i++);
    }

    return EXIT_FAILURE;
}
