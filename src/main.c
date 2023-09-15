#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int err = -1;

    if (argc < 4) {
        printf("Invalid arguments\n");
        return -1;
    }

    char *filename[2] = {
        argv[1], argv[2]
    };

    uint32_t bytes_to_copy = strtoul(argv[3], NULL, 0);
    if (bytes_to_copy == 0) {
        printf("Invalid length to copy!\n");
        return -1;
    }

    uint32_t copy_offset = 0;
    if (argc >= 5) {
        copy_offset = strtoul(argv[4], NULL, 0);
    }

    FILE *file[2];
    uint32_t filesize[2] = {0};
    uint8_t *filedata[2];

    printf("Copying file: %s, Bytes: %d, Offset: 0x%08X, creating: %s\n",
        filename[0], bytes_to_copy, copy_offset, filename[1]);

    file[0] = fopen(filename[0], "rb");

    if (!file[0]) {
        printf("\t- Error: %s not found\n", filename[0]);
        return -1;
    }

    fseek(file[0], 0, SEEK_END);
    filesize[0] = ftell(file[0]);

    rewind(file[0]);

    printf("\t- %s - file size: %d\n", filename[0], filesize[0]);

    if (filesize[0] < (bytes_to_copy + copy_offset)) {
        printf("Invalid Parameters: Copy + offset is higher than filesize!\n");
    }

    filedata[0] = malloc(filesize[0]);
    (void)fread(filedata[0], filesize[0], 1, file[0]);

    file[1] = fopen(filename[1], "w");
    fwrite(filedata[0] + copy_offset, bytes_to_copy, 1, file[1]);

    fclose(file[0]);
    fclose(file[1]);

    free(filedata[0]);

    return 0;
}