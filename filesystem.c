#include "disk_manager.c"

void reset_pointer (char* ptr, int size) 
{
    for (int i = 0; i < size; i++)
    {
        *(ptr + i) = (char) 0;
    }
}

int read (inode* head, char* data, int size, int offset) 
{
    if (offset >= DISK_SIZE)
        return -1;

    char* temp_block = (char*)malloc(sizeof(char) * BLOCK_SIZE);

    int block_offset = (int) (offset / BLOCK_SIZE);
    for (int i = 0; i < block_offset; i++)
    {
        head = head->next_inode;
    }
    offset = offset % BLOCK_SIZE;

    int bytes_read;
    int total_read = 0;
    while (total_read < size)
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
    // char* data = (char*)malloc(sizeof(char) * 36);

    // READ

    // int result = read(0, data, 36, 0);
    // printf("READ: %s | %d \n", data, result);

    // WRITE

    // char text[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    // memcpy(data, text, 36);
    // int result = write(3, data, 36, 1);
    // printf("%d\n", result);

    // create_tree();
    // add_child(current_directory, false, "a.txt");
    // add_child(current_directory, false, "b.txt");
    // add_child(current_directory, true, "c");
    // add_child(current_directory, false, "d.txt");
    // locate(false, "c");
    // add_child(current_directory, false, "e.txt");
    // add_child(current_directory, false, "f.txt");
    // locate(true, "");
    // printf("%s\n", root->child->sibling->sibling->child->sibling->name);

    // add_file(0);
    // add_file(1);
    // inode* temp = find_inode(0);
    // add_inode(temp, 3);
    // temp = find_inode(1);
    // add_inode(temp, 2);
    // printf("%d %d | %d %d\n", 
    //         inode_head->block,
    //         inode_head->next_inode->block,
    //         inode_head->next_file->block,
    //         inode_head->next_file->next_inode->block);

    // Simulacion arbol y i-nodos

    create_tree();
    add_child(current_directory, false, "test.txt", 0);
    inode* test = find_inode(0);
    add_inode(test, 5);
    add_inode(test, 3);

    // Simulacion de lectura junto a las estructuras

    char* data = (char*)malloc(sizeof(char) * 36);
    inode* inodo = find_inode(retrieve("test.txt")->file);

    int result = read(inodo, data, 36, 0);
    printf("READ: %s | %d \n", data, result);

    return 0;
}