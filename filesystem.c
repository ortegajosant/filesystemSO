#include "disk_manager.c"

void reset_pointer (char* ptr, int size) 
{
    for (int i = 0; i < size; i++)
    {
        *(ptr + i) = (char) 0;
    }
}

int read (int head, char* data, int size, int offset) 
{
    if (offset >= DISK_SIZE)
        return -1;

    char* temp_block = (char*)malloc(sizeof(char) * BLOCK_SIZE);

    head += (int) (offset / BLOCK_SIZE);
    offset = offset % BLOCK_SIZE;

    int bytes_read;
    int total_read = 0;
    while (total_read < size)
    {
        bytes_read = read_block(head, temp_block);
        if (bytes_read == 0)
            break;

        if (offset > 0) 
        {
            bytes_read -= offset;
            memcpy(data, temp_block + offset, bytes_read);
            offset = 0;
        }
        else
            memcpy(data + total_read, temp_block, bytes_read);
        
        total_read += bytes_read;
        head++;
    }

    free(temp_block);
    return total_read;
}

int write (int head, char* data, int size, int offset) 
{
    if (offset >= DISK_SIZE)
        return -1;

    char* temp_block = (char*)malloc(sizeof(char) * BLOCK_SIZE);

    head += (int) (offset / BLOCK_SIZE);
    offset = offset % BLOCK_SIZE;

    int bytes_write;
    int total_write = 0;
    while (total_write < size)
    {
        if (offset > 0)
            bytes_write = BLOCK_SIZE - offset;
        else if (size - total_write < BLOCK_SIZE)
            bytes_write = size - total_write;
        else
            bytes_write = BLOCK_SIZE;

        if (offset > 0)
        {
            memcpy(temp_block + offset, data, bytes_write);
            offset = 0;
        }
        else
            memcpy(temp_block, data + total_write, bytes_write);
        write_block(head, temp_block);

        reset_pointer(temp_block, BLOCK_SIZE);
        total_write += bytes_write;
        head++;
    }

    free(temp_block);
    return total_write;
}

int main() 
{
    char* data = (char*)malloc(sizeof(char) * 36);

    // READ

    // int result = read(0, data, 36, 0);
    // printf("READ: %s | %d \n", data, result);

    // WRITE

    // char text[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    // memcpy(data, text, 36);
    // int result = write(3, data, 36, 1);
    // printf("%d\n", result);

    return 0;
}