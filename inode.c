#include <stdio.h>

#define DISK_SIZE 1024
#define BLOCK_SIZE 16

typedef struct inode{
    int block;
    struct inode* next_inode;
    struct inode* next_file;
} inode;

inode* inode_head = NULL;

void add_inode (inode* head, int block) 
{
    inode* new_block = (inode*)malloc(sizeof(inode));
    new_block->block = block;

    inode* temp = head;
    while (temp->next_inode != NULL)
    {
        temp = temp->next_inode;
    }
    temp->next_inode = new_block;
}

void remove_inode (inode* head) 
{
    if (head->next_inode == NULL)
    {
        free(head);
    }
    else
    {
        inode* temp = head;
        while (temp->next_inode->next_inode != NULL)
        {
            temp = temp->next_inode;
        }
        inode* to_delete = temp->next_inode;
        temp->next_inode = NULL;
        free(to_delete);
    }
}

inode* find_inode (int block) 
{
    inode* temp = inode_head;
    while (temp->block != block)
    {
        temp = temp->next_file;
    }
    return temp;
}

int len_node (inode* inodo) 
{
    if (inodo == NULL)
        return 0;
    else
    {
        inode* temp = inodo;
        int count = 1;
        while (temp->next_inode != NULL)
        {
            temp = temp->next_inode;
            count++;
        }
        return count;
    }
}

inode* add_file (int block) 
{
    inode* new_file = (inode*)malloc(sizeof(inode));
    new_file->block = block;

    if (inode_head == NULL)
        inode_head = new_file;
    else 
    {
        inode* temp = inode_head;
        while (temp->next_file != NULL)
        {
            temp = temp->next_file;
        }
        temp->next_file = new_file;
    }
}

inode* remove_file (int block) 
{
    if (inode_head->block == block) 
    {
        inode* temp = inode_head;
        inode_head = inode_head->next_file;
        int n = len_node(temp);
        for (int i = 0; i < n; i++)
        {
            remove_inode(temp);
        }
    }
    else 
    {
        inode* temp = inode_head;
        while (temp->next_file->block != block)
        {
            temp = temp->next_file;
        }
        inode* to_delete = temp->next_file;
        temp->next_file = temp->next_file->next_file;
        int n = len_node(to_delete);
        for (int i = 0; i < n; i++)
        {
            remove_inode(to_delete);
        }
    }
}

int* free_blocks (int size) 
{
    int* blocks = (int*)malloc(sizeof(int) * size);

    FILE* file;
    file = fopen("./bin/disk.txt", "r");
    if(file == NULL)
        return NULL;
    fseek(file, 0, SEEK_SET);

    int i = 0;
    int n = DISK_SIZE / BLOCK_SIZE;
    bool free;
    for (int j = 0; j < n; j++)
    {
        if (i >= size)
        {
            break;
        }
        fseek(file, 7, SEEK_CUR);
        free = true;
        int k;
        for (k = 0; k < BLOCK_SIZE; k++)
        {
            if (fgetc(file) != '\0') 
            {
                free = false;
                k++;
                break;
            }
        }

        inode* temp_1 = inode_head;
        inode* temp_2;
        while (temp_1 != NULL)
        {
            temp_2 = temp_1;
            while (temp_2 != NULL)
            {
                if (temp_2->block == j)
                {
                    free = false;
                    break;
                }
                temp_2 = temp_2->next_inode;
            }
            temp_1 = temp_1->next_file;
        }
        
        if (free) 
        {
            *(blocks + i) = j;
            i++;
        }
        
        fseek(file, BLOCK_SIZE - k + 9, SEEK_CUR);
    }

    fclose(file);
    return blocks;
}