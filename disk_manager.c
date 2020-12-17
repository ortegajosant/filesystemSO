#include <stdlib.h>
#include "tree.c"

#define DISK_SIZE 1024
#define BLOCK_SIZE 16

int read_block(int block, char* data)
{
    if (block >= DISK_SIZE / BLOCK_SIZE)
        return -2;

    FILE* file;
    file = fopen("./bin/disk.txt", "r");
    if(file == NULL)
        return -1;
    fseek(file, 0, SEEK_SET);

    int i = 0;
    int c;
    while (i < block)
    {
        c = fgetc(file);
        if (c == '\n') 
            i++;
    }

    fseek(file, 7, SEEK_CUR);
    for (i = 0; i < BLOCK_SIZE; i += 1)
    {
        c = fgetc(file);
        if (c == (char) 0) 
        {
            *(data + i) = '\0';
            break;
        }
        else 
            *(data + i) = c;
    }

    fclose(file);
    return i;
}


int write_block(int block, char* data)
{
    if (block >= DISK_SIZE / BLOCK_SIZE)
        return -2;

    FILE* file;
    file = fopen("./bin/disk.txt", "r+");
    if(file == NULL)
        return -1;
    fseek(file, 0, SEEK_SET);

    int i = 0;
    int c;
    while (i < block)
    {
        c = fgetc(file);
        if (c == '\n') 
            i++;
    }

    int block_beginning = ftell(file) + 7;
    fseek(file, block_beginning, SEEK_SET);
    for (int i = 0; i < BLOCK_SIZE; i++)
    {
        fputc(*(data + i), file);
    }

    fclose(file);
    return 0;
}

// int main () 
// {
//     char* data = (char*)malloc(sizeof(char) * 16);

//     READ

//     int result = read(1, data);
//     printf("%d | %s\n", result, data);

//     WRITE

//     char text[] = "1234567890abcdef";
//     memcpy(data, text, 16);
//     int result = write(0, data);
//     printf("%d\n", result);

//     return 0;
// }