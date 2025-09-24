#include <unistd.h>
#include <stdint.h>
#include "uart2.h"

int _write(int fd, const void* buf, size_t count){
    if(fd==STDOUT_FILENO || fd==STDERR_FILENO){
        uart2_write(buf,(uint32_t)count);
        return (int)count;
    }
    return -1;
}
