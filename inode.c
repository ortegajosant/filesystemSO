#include <stdio.h>

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
    inode* temp = head;
    while (temp->next_inode->next_inode != NULL)
    {
        temp = temp->next_inode;
    }
    inode* to_delete = temp->next_inode;
    temp->next_inode = NULL;
    free(to_delete);
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
        inode* temp_inode;
        inode_head = inode_head->next_file;
        while (temp != NULL)
        {
            temp_inode = temp;
            temp = temp->next_inode;
            remove_inode(temp_inode);
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
        inode* temp_inode;
        temp->next_file = temp->next_file->next_file;
        while (to_delete != NULL)
        {
            temp_inode = to_delete;
            to_delete = to_delete->next_inode;
            remove_inode(temp_inode);
        }
    }
}