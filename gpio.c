#include "gpio.h"
#include "rcc.h"


void gpio_init(GPIO_TypeDef *gpio, uint32_t mode, uint32_t pin){
    // Enable the GPIO clock
    if (gpio == GPIOA) {
        RCC->AHBENR |= GPIOA_ENABLE;
    } else if (gpio == GPIOB) {
        RCC->AHBENR |= GPIOB_ENABLE;
    } else if (gpio == GPIOC) {
        RCC->AHBENR |= GPIOC_ENABLE;
    } else if (gpio == GPIOD) {
        RCC->AHBENR |= GPIOD_ENABLE;
    } else if (gpio == GPIOE) {
        RCC->AHBENR |= GPIOE_ENABLE;
    } else if (gpio == GPIOF) {
        RCC->AHBENR |= GPIOF_ENABLE;
    } else if (gpio == GPIOG) {
        RCC->AHBENR |= GPIOG_ENABLE;
    } else if (gpio == GPIOH) {
        RCC->AHBENR |= GPIOH_ENABLE;
    }

    // Set the mode for the specified pin
    gpio->MODER &= ~(0x3 << (pin * 2)); // Clear mode bits
    gpio->MODER |= (mode << (pin * 2)); // Set new mode
}
void gpio_set(GPIO_TypeDef *gpio, uint32_t pin){
    // Set the specified pin
    gpio->BSRR = (1 << pin);
}
void gpio_clear(GPIO_TypeDef *gpio, uint32_t pin){
    // Clear the specified pin
    gpio->BSRR = (1 << (pin + 16)); // Set the bit in the reset register
}
void gpio_toggle(GPIO_TypeDef *gpio, uint32_t pin){
    // Toggle the specified pin
    gpio->ODR ^= (1 << pin);
}
void gpio_write(GPIO_TypeDef *gpio, uint32_t pin, uint32_t value){
    // Write a value to the specified pin
    if (value) {
        gpio_set(gpio, pin);
    } else {
        gpio_clear(gpio, pin);
    }
}
int gpio_read(GPIO_TypeDef *gpio, uint32_t pin){
    // Read the value of the specified pin
    return (gpio->IDR & (1 << pin)) ? 1 : 0;
}
void gpio_set_mode(GPIO_TypeDef *gpio, uint32_t mode, uint32_t pin){
    // Set the mode for the specified pin
    gpio->MODER &= ~(0x3 << (pin * 2)); // Clear mode bits
    gpio->MODER |= (mode << (pin * 2)); // Set new mode
}
void gpio_set_output_type(GPIO_TypeDef *gpio, uint32_t type, uint32_t pin){
    // Set the output type for the specified pin
    if (type) {
        gpio->OTYPER |= (1 << pin); // Set to open-drain
    } else {
        gpio->OTYPER &= ~(1 << pin); // Set to push-pull
    }
}
void gpio_set_speed(GPIO_TypeDef *gpio, uint32_t speed, uint32_t pin){
    // Set the output speed for the specified pin
    gpio->OSPEEDR &= ~(0x3 << (pin * 2)); // Clear speed bits
    gpio->OSPEEDR |= (speed << (pin * 2)); // Set new speed
}
void gpio_set_pull(GPIO_TypeDef *gpio, uint32_t pull, uint32_t pin){
    // Set the pull-up/pull-down configuration for the specified pin
    gpio->PUPDR &= ~(0x3 << (pin * 2)); // Clear pull bits
    gpio->PUPDR |= (pull << (pin * 2)); // Set new pull configuration
}
void gpio_set_alternate_function(GPIO_TypeDef *gpio, uint32_t af, uint32_t pin){
    // Set the alternate function for the specified pin
    if (pin < 8) {
        gpio->AFRL &= ~(0xF << (pin * 4)); // Clear AF bits
        gpio->AFRL |= (af << (pin * 4)); // Set new AF
    } else {
        gpio->AFRH &= ~(0xF << ((pin - 8) * 4)); // Clear AF bits
        gpio->AFRH |= (af << ((pin - 8) * 4)); // Set new AF
    }
}