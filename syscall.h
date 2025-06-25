#ifndef __SYSCALL_H__
#define __SYSCALL_H__
#include <sys/stat.h>

__attribute__((weak)) void _exit(int status);

__attribute__((weak)) int _open(const char *path, int flags, ...);

__attribute__((weak)) int _close(int fd);
__attribute__((weak)) int _lseek(int fd, int ptr, int dir);

int __attribute__((weak)) _fstat(int fd, struct stat *st);
__attribute__((weak)) int _isatty(int fd);

int _read(int fd, char *ptr, int len);
int _write(int fd, char *ptr, int len);

caddr_t _sbrk(int incr);

#endif // __SYSCALL_H__