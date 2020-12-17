#include <stdio.h>

#define DISK_SIZE 1024
#define BLOCK_SIZE 16

void create_disk () 
{
    FILE* file;
    file = fopen("./bin/disk.txt", "w");
    for (int i = 0; i < DISK_SIZE; i += BLOCK_SIZE)
    {
        fprintf(file, "<block>");
        for (int j = 0; j < BLOCK_SIZE; j++)
        {
            fputc((char) 0, file);
        }
        fprintf(file, "</block>\n");
    }
    fclose(file);
}

int main() {
    create_disk();
    return 0;
}