#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>

extern int  errno;
extern char _sdata, _edata, _sbss, _ebss;
extern char _end;
static char* heap_end;

void* _sbrk(ptrdiff_t incr) {
    if (heap_end == 0) heap_end = &_end;
    char* prev = heap_end;
    char* new_end = heap_end + incr;
    heap_end = new_end;
    return (void*)prev;
}

int _close(int file)               { errno = EBADF; return -1; }
int _fstat(int file, struct stat* st) { st->st_mode = S_IFCHR; return 0; }
int _isatty(int file)              { return 1; }
off_t _lseek(int file, off_t ptr, int dir) { errno = ESPIPE; return (off_t)-1; }
int _read(int file, void* ptr, size_t len) { errno = EBADF; return -1; }
void _exit(int status)             { while (1) {} }
int _kill(int pid, int sig)        { errno = EINVAL; return -1; }
int _getpid(void)                  { return 1; }
