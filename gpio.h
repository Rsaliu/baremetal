#ifndef __GPIO_H__
#define __GPIO_H__

#include <stm32f3x.h>
#include <stdint.h>

#define GPIOA_OFFSET (0x0000)
#define GPIOB_OFFSET (0x0400)
#define GPIOC_OFFSET (0x0800)
#define GPIOD_OFFSET (0x0C00)
#define GPIOE_OFFSET (0x1000)
#define GPIOF_OFFSET (0x1400)
#define GPIOG_OFFSET (0x1800)
#define GPIOH_OFFSET (0x1C00)


#define GPIOA_BASE (AHB2_BASE + GPIOA_OFFSET)
#define GPIOB_BASE (AHB2_BASE + GPIOB_OFFSET)
#define GPIOC_BASE (AHB2_BASE + GPIOC_OFFSET)
#define GPIOD_BASE (AHB2_BASE + GPIOD_OFFSET)
#define GPIOE_BASE (AHB2_BASE + GPIOE_OFFSET)
#define GPIOF_BASE (AHB2_BASE + GPIOF_OFFSET)
#define GPIOG_BASE (AHB2_BASE + GPIOG_OFFSET)
#define GPIOH_BASE (AHB2_BASE + GPIOH_OFFSET)


typedef struct {
    volatile uint32_t MODER;   // GPIO port mode register
    volatile uint32_t OTYPER;  // GPIO port output type register
    volatile uint32_t OSPEEDR; // GPIO port output speed register
    volatile uint32_t PUPDR;   // GPIO port pull-up/pull-down register
    volatile uint32_t IDR;     // GPIO port input data register
    volatile uint32_t ODR;     // GPIO port output data register
    volatile uint32_t BSRR;    // GPIO port bit set/reset register
    volatile uint32_t LCKR;    // GPIO port configuration lock register
    volatile uint32_t AFRL;    // GPIO alternate function low register
    volatile uint32_t AFRH;    // GPIO alternate function high register
    volatile uint32_t BRR; 
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *) GPIOC_BASE) 
#define GPIOD ((GPIO_TypeDef *) GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *) GPIOE_BASE)
#define GPIOF ((GPIO_TypeDef *) GPIOF_BASE)
#define GPIOG ((GPIO_TypeDef *) GPIOG_BASE)
#define GPIOH ((GPIO_TypeDef *) GPIOH_BASE)


// functionalities
void gpio_init(GPIO_TypeDef *gpio, uint32_t mode, uint32_t pin);
void gpio_set(GPIO_TypeDef *gpio, uint32_t pin);
void gpio_clear(GPIO_TypeDef *gpio, uint32_t pin);
void gpio_toggle(GPIO_TypeDef *gpio, uint32_t pin);
void gpio_write(GPIO_TypeDef *gpio, uint32_t pin, uint32_t value);
int gpio_read(GPIO_TypeDef *gpio, uint32_t pin);
void gpio_set_mode(GPIO_TypeDef *gpio, uint32_t mode, uint32_t pin);
void gpio_set_output_type(GPIO_TypeDef *gpio, uint32_t type, uint32_t pin);
void gpio_set_speed(GPIO_TypeDef *gpio, uint32_t speed, uint32_t pin);
void gpio_set_pull(GPIO_TypeDef *gpio, uint32_t pull, uint32_t pin);
void gpio_set_alternate_function(GPIO_TypeDef *gpio, uint32_t af, uint32_t pin);

#endif