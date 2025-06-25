#include <gpio.h>
#include <rcc.h>
#include <stdint.h>
#include <uart.h>
#include <stdio.h>
extern void __libc_init_array(void);
volatile void dummy_func(){
    // Dummy function to prevent optimization
    char j;
    printf("Enter a value: \n");
    j = getchar(); // Read a character from standard input
    printf("\nDummy function called with value: %c\n", j);
}
int main(){
    // Initialize system clock, peripherals, etc.
    // This is a placeholder for actual initialization code.
    
    // Call the main application logic
    // This is where your application code would go.
    #ifdef SEMIHOSTING
        initialise_monitor_handles();
    #endif
    // For demonstration, we can just enter an infinite loop
    GPIO_TypeDef *gpio = GPIOA; // Example GPIO port
    gpio_init(gpio, 0x01, 5); // Initialize pin 5 as output (0x01 = Output mode)
    
    #ifdef UART_PRINTF
    UART_TypeDef *uart = UART1; // Example UART
    uart_init(uart, 9600); // Initialize UART1 with a baud rate of 9600
    #endif
    uint32_t counter = 0;
    char buffer[10]= {0}; // Buffer to store received characters
    //char array[10] = {0};
    dummy_func(); // Call dummy function to prevent optimization
    while(1) {
        // Application logic here
        // For example, toggle an LED or process data
        printf("enter a string: \n");
        char received_char= getchar();
        while(received_char != '\n' && received_char != 13) { // Read until newline or carriage return
            buffer[counter++] = received_char;
            if (counter >= sizeof(buffer) - 1) { // Prevent buffer overflow
                break; // Stop reading if buffer is full
            }
            received_char = getchar(); // Read next character
        }
        buffer[counter] = '\0'; // Null-terminate the string
        printf("Received: %s\n", buffer); // Print received input
        counter = 0; // Reset counter after reading input
        buffer[0] = '\0'; // Clear buffer for next input
    }
    
    return 0;
}


[[gnu::naked,gnu::noreturn]] void reset_handler(void){
    extern long _sbss,_ebss,_sdata,_edata,_sidata;
    for(long *p = &_sbss; p < &_ebss; p++) *p = 0;
    long * mdata = &_sidata;
    for(long *p = &_sdata; p < &_edata;) *p++ = *mdata++;
    //__libc_init_array();
    main();
    for(;;) (void) 0;
}

extern void _estack(void);
[[gnu::section(".vectors")]]
void (* const vector_table[16+73])(void) = {
    _estack, // Initial stack pointer
    reset_handler,             // Reset handler
    // Other handlers can be added here
};