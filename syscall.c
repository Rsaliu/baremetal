#include <syscall.h>
#include <stdint.h>
#include <uart.h>

int _write (int fd, char * ptr, int len){
    // This is a simple implementation that writes to a UART
    // In a real application, you would replace this with actual UART write logic
    for (int i = 0; i < len; i++) {
        // Assuming uart_send is defined elsewhere to send data over UART
        uart_send(UART1, ptr[i]); // Replace UART1 with the appropriate UART instance
    }
    return len; // Return the number of bytes written
}

__attribute__((weak)) void _exit(int status) {
    while (1) ;
}

__attribute__((weak))  int _open (const char * path, int flags, ...) 
  {
    // This is a simple implementation that always fails
    // In a real application, you would replace this with actual file open logic
    return (-1);
  }
  
  __attribute__((weak)) int _close (int fd) 
  {
    return (-1);
  }
  
  __attribute__((weak)) int _lseek (int fd, int ptr, int dir) 
  {
    return (0);
  }
  
  int __attribute__((weak)) _fstat (int fd, struct stat * st) 
  {
    return (0);
  }
  
  __attribute__((weak)) int _isatty (int fd) 
  {
    return (1);
  }
  
  int _read (int fd, char * ptr, int len) 
  {
    // This is a simple implementation that reads from a UART
    // In a real application, you would replace this with actual UART read logic
    ptr[0] = uart_receive(UART1);
    return 1;
    // for (int i = 0; i < len; i++) {
    //     ptr[i] = uart_receive(UART1); // Replace UART1 with the appropriate UART instance
    //     if (ptr[i] == '\n' || ptr[i] == '\r') {
    //         ptr[i] = '\0'; // Null-terminate the string on newline or carriage return
    //         break; // Stop reading on newline or carriage return
    //     }
    // }
    // return len; // Return the number of bytes read
  }
  
  extern char _end; // Provided by linker script
  static char *heap_end;
  caddr_t _sbrk (int incr) 
  {
    extern char _estack; // top of the stack (provided by linker)
    char *prev_heap_end;

    if (heap_end == 0) {
        heap_end = &_end;
    }

    prev_heap_end = heap_end;

    if (heap_end + incr > &_estack) {
        // Heap and stack collision
        return (caddr_t)-1;
    }

    heap_end += incr;
    return (caddr_t)prev_heap_end;
  }
  