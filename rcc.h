#ifndef __RCC_H__
#define __RCC_H__
#include <stm32f3x.h> 
#include <stdint.h>

#define RCC_BASE (AHB1_BASE + 0x1000)

typedef struct {
    volatile uint32_t CR;         // RCC clock control register
    volatile uint32_t CFGR;       // RCC clock configuration register
    volatile uint32_t CIR;        // RCC clock interrupt register
    volatile uint32_t APB2RSTR;   
    volatile uint32_t APB1RSTR;   
    volatile uint32_t AHBENR;  
    volatile uint32_t APB2ENR;  
    volatile uint32_t APB1ENR; 
    volatile uint32_t BDCR;
    volatile uint32_t CSR;        // RCC clock control & status register  
    volatile uint32_t AHBRSTR;    // RCC AHB peripheral reset register
    volatile uint32_t CFGR2;      // RCC clock configuration register 2
    volatile uint32_t CFGR3;      // RCC clock configuration register 3
} RCC_TypeDef;

#define GPIOD_ENABLE (1<<20)
#define GPIOA_ENABLE (1<<17)
#define GPIOB_ENABLE (1<<18)
#define GPIOC_ENABLE (1<<19)    
#define GPIOE_ENABLE (1<<21)
#define GPIOF_ENABLE (1<<22)
#define GPIOG_ENABLE (1<<23)
#define GPIOH_ENABLE (1<<16)

#define RCC ((RCC_TypeDef *) RCC_BASE)
#endif