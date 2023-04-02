#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int fd = open("A", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int buffer_size = 4 * 1024 * 1024 + 1;

    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL)
    {
        perror("Error allocate buffer");
        return -1;
    }
    for (int i = 0; i < buffer_size; i++){
        if ((i == 0) || (i == 9999) || (i == buffer_size - 1)) {
            buffer[i] = 1;
        }
        else buffer[i] = 0;
    }
    write(fd, buffer, buffer_size);
    close(fd);
    free(buffer);

  return 0;
}
