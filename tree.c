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
        new_child->file = block;
        add_file(block);
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
        remove_file(child->file);
        free(child);
    }
    else {
        element* temp = parent->child;
        while (temp->sibling != child)
        {
            temp = temp->sibling;
        }
        parent->child = child->sibling;
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
        while (strcmp(temp->name, name) != 0)
        {
            temp = temp->sibling;
            if (temp == NULL)
                return -1;
        }
        current_directory = temp;
        return 0;
    }
}

void create_tree () 
{
    root = (element*)malloc(sizeof(element));
    strcpy(root->name, "root");
    current_directory = root;
}