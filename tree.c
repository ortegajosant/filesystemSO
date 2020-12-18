#include <stdbool.h>
#include <string.h>
#include "inode.c"

typedef struct element{
    struct element* head;
    struct element* child;
    struct element* sibling;
    int file;
    char name[25];
} element;

element* root = NULL;
element* current_directory = NULL;

void add_child (element* parent, bool is_folder, char* name, int block) 
{
    element* new_child = (element*)malloc(sizeof(element));
    new_child->head = NULL;
    new_child->child = NULL;
    new_child->sibling = NULL;
    strcpy(new_child->name, name);
    
    if (is_folder) 
        new_child->file = -1;
    else
    {
        if (block < 0)
        {
            int* block_value = free_blocks(1);
            new_child->file = *block_value;
            free(block_value);
        }
        else
            new_child->file = block;
        add_file(new_child->file);
    }

    if (parent->child == NULL) 
        parent->child = new_child;
    else
    {
        element* temp = parent->child;
        while (temp->sibling != NULL)
        {
            temp = temp->sibling;
        }
        temp->sibling = new_child;
    }
}

void remove_child (element* parent, element* child) 
{
    if (parent->child == child)
    {
        parent->child = child->sibling;
        if (child->file > -1)
            remove_file(child->file);
        free(child);
    }
    else {
        element* temp = parent->child;
        while (temp->sibling != child)
        {
            temp = temp->sibling;
        }
        temp->sibling = child->sibling;
        if (child->file > -1)
            remove_file(child->file);
        free(child);
    }
}

element* retrieve (char* name) 
{
    element* temp = current_directory->child;
    while (strcmp(temp->name, name) != 0)
    {
        temp = temp->sibling;
        if (temp == NULL)
            return NULL;
    }
    return temp;
}

int locate (bool go_back, char* name) 
{
    if (go_back == true)
    {
        current_directory = current_directory->head;
        return 0;
    }
    else
    {
        element* temp = current_directory->child;
        while (temp != NULL)
        {
            if (strcmp(temp->name, name) == 0 && temp->file == -1)
            {
                current_directory = temp;
                return 0;
            }
            temp = temp->sibling;
        }
        return -1;
    }
}

void create_tree () 
{
    root = (element*)malloc(sizeof(element));
    strcpy(root->name, "root");
    root->head = NULL;
    root->child = NULL;
    root->sibling = NULL;
    root->file = -1;
    current_directory = root;
}

void delete_tree(element* head) 
{
    element* temp_1 = head->child;
    element* temp_2;
    while (temp_1 != NULL) 
    {
        temp_2 = temp_1;
        temp_1 = temp_1->sibling;
        if (temp_2->file == -1)
        {
            delete_tree(temp_2);
        }
        remove_child(head, temp_2);
    }
}