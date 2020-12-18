#include <math.h>
#include "parser.c"

void reset_pointer(char *ptr, int size)
{
    for (int i = 0; i < size; i++)
    {
        *(ptr + i) = (char)0;
    }
}

int read_(inode *head, char *data, int size, int offset)
{
    if (offset >= DISK_SIZE)
        return -1;

    char *temp_block = (char *)malloc(sizeof(char) * BLOCK_SIZE);

    int block_offset = (int)(offset / BLOCK_SIZE);
    for (int i = 0; i < block_offset; i++)
    {
        head = head->next_inode;
    }
    offset = offset % BLOCK_SIZE;

    int bytes_read;
    int total_read = 0;
    while (total_read < size && head != NULL)
    {
        bytes_read = read_block(head->block, temp_block);
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
        head = head->next_inode;
    }

    free(temp_block);
    return total_read;
}

int write_(inode *head, char *data, int size, int offset)
{
    inode *main_head = head;
    if (offset >= DISK_SIZE)
        return -1;

    char *cleaner = (char *)malloc(sizeof(char) * BLOCK_SIZE);
    reset_pointer(cleaner, BLOCK_SIZE);
    while (head != NULL)
    {
        write_block(head->block, cleaner);
        head = head->next_inode;
    }

    char *temp_block = (char *)malloc(sizeof(char) * BLOCK_SIZE);

    int block_offset = (int)(offset / BLOCK_SIZE);

    int blocks_needed = ceil((double)(size + offset) / (double)BLOCK_SIZE);
    blocks_needed -= len_node(main_head);
    if (blocks_needed > 0)
    {
        int *new_block = free_blocks(blocks_needed);
        for (int i = 0; i < blocks_needed; i++)
        {
            add_inode(main_head, *(new_block + i));
        }
        free(new_block);
    }

    offset = offset % BLOCK_SIZE;
    head = main_head;
    for (int i = 0; i < block_offset; i++)
    {
        head = head->next_inode;
    }

    int bytes_write;
    int total_write = 0;
    while (total_write < size)
    {
        if (size - total_write < BLOCK_SIZE)
            bytes_write = size - total_write;
        else if (offset > BLOCK_SIZE - size && size - total_write < BLOCK_SIZE)
            bytes_write = size - (offset - (BLOCK_SIZE - size));
        else if (offset > 0)
        {
            if (offset < BLOCK_SIZE)
                bytes_write = BLOCK_SIZE - offset;
            else
                bytes_write = 0;
        }
        else
            bytes_write = BLOCK_SIZE;

        if (offset > 0)
        {
            if (offset < BLOCK_SIZE)
                memcpy(temp_block + offset, data, bytes_write);
            offset -= BLOCK_SIZE;
        }
        else
            memcpy(temp_block, data + total_write, bytes_write);
        write_block(head->block, temp_block);

        reset_pointer(temp_block, BLOCK_SIZE);
        total_write += bytes_write;
        head = head->next_inode;
    }
    int count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next_inode;
    }
    for (int i = 0; i < count; i++)
    {
        remove_inode(main_head);
    }
    free(temp_block);
    return total_write;
}

// int main()
// {
//     create_tree();

//     add_child(current_directory, true, "a");
//     add_child(current_directory, true, "b");
//     add_child(current_directory, true, "c");
//     locate(false, "b");
//     add_child(current_directory, false, "b_1.txt");
//     add_child(current_directory, false, "b_2.txt");
//     add_child(current_directory, false, "b_3.txt");

//     save_tree();

//     delete_tree(root);
//     free(root);

//     return 0;
// }