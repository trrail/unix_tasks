#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>



int main(int argc, char *argv[]) {
    int block_size = 4096;
    char *input_file_path = NULL;
    char *output_file_path = NULL;

    int index;
    while ((index = getopt(argc, argv, ":b:")) != -1) {
        if (index == 'b') {
            block_size = atoi(optarg);
        }
    }

    if (optind < argc) {
        input_file_path = argv[optind++];
    }
    else {
        printf("Missimg file path");
        return -1;
    }

    int input_fd = STDIN_FILENO;
    int output_fd = 0;
    output_file_path = argv[optind++];
    if (output_file_path == NULL) {
        output_fd = open(input_file_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    }
    else {
        input_fd = open(input_file_path, O_RDONLY, 0);
        output_fd = open(output_file_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
    }

    char *buffer = (char *)malloc(block_size);
    if (buffer == NULL) {
        printf("Error allocate buffer");
        return -1;
    }

    int z_block_count = 0;
    while (true) {
        int read_count = read(input_fd, buffer, block_size);

        if (read_count == -1) {
            printf("Read file error");
            exit(1);
        }
        else if (read_count == 0) break; // End of file

        bool is_zero = true;
        for (int i = 0; i < read_count; i++) {
            if (buffer[i] != 0) {
                is_zero = false;
                break;
            }
        }
        if (is_zero) {
            z_block_count++;
            continue;
        }

        if (z_block_count != 0) {
            lseek(output_fd, z_block_count * block_size, SEEK_CUR);
            z_block_count = 0;
        }

        write(output_fd, buffer, read_count);
    }

    if (z_block_count != 0) {
        lseek(output_fd, z_block_count * block_size, SEEK_CUR);
    }
    if (input_fd != 0) {
        close(input_fd);
    }

    return close(output_fd);
}
