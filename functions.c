#include "variables.h"
#include "filesystem.c"
#include <string.h>

element *validate_file(char *name)
{
    if (current_directory->child != NULL)
    {
        element *temp = retrieve(name);
        if (temp != NULL && temp->file != -1)
        {
            return temp;
        }
    }

    return NULL;
}

element *validate_folder(char *name)
{
    if (current_directory->child != NULL)
    {
        element *temp = retrieve(name);
        if (temp != NULL && temp->file == -1)
        {
            return temp;
        }
    }

    return NULL;
}

void add_name_to_path(char *path, char *name)
{
    strcat(path, name);
    strcat(path, "/");
}

void remove_name_to_path(char *path)
{
    char temp_path[strlen(path)];

    strcpy(temp_path, path);

    memset(path, 0, strlen(path));

    if (current_directory == root)
    {
        strcat(path, "/");
        strcat(path, current_directory->name);
        strcat(path, "/");
    }
    else
    {
        char *ptr = strtok(temp_path, "/");
        char folder_temp[128];

        g_print("\nFolder: %s\nPTR: %s\n", folder_temp, folder_temp + 1);

        while (ptr != NULL)
        {
            strcat(path, "/");
            strcpy(folder_temp, ptr);
            ptr = strtok(NULL, "/");
            if (ptr == NULL)
                break;
            strcat(path, folder_temp);
        }
    }
}

int mkdir_(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }

    element *temp = validate_folder(cmd_buffer[1]);
    if (temp)
    {
        print_console("", "The folder already exists", true);
        return -2;
    }

    if (strcmp(cmd_buffer[1], "..") != 0)
    {
        add_child(current_directory, true, cmd_buffer[1], -1);
        save_tree();
    }

    return 1;
}
int rmdir_(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }

    element *temp = validate_folder(cmd_buffer[1]);
    if (temp == NULL)
    {
        print_console("", "The folder doesn't exists", true);
        return -2;
    }
    delete_tree(temp);
    remove_child(current_directory, temp, false);
    save_tree();
    return 1;
}

int cd(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length > 2)
    {
        return -1;
    }

    if (strcmp(cmd_buffer[1], "") == 0)
    {
        current_directory = root;
        remove_name_to_path(path_label);
    }

    else if (strcmp(cmd_buffer[1], "..") == 0)
    {
        locate(true, "");
        remove_name_to_path(path_label);
    }
    else
    {
        int temp = locate(false, cmd_buffer[1]);
        if (temp == 0)
        {
            add_name_to_path(path_label, current_directory->name);
        }
        else
        {
            return -2;
        }
    }

    return 1;
}

int touch(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }
    element *temp = validate_file(cmd_buffer[1]);
    if (temp != NULL)
    {
        print_console("", "The file already exists", true);
        return -2;
    }
    add_child(current_directory, false, cmd_buffer[1], -1);
    save_tree();
    return 1;
}

int rm(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }

    g_print("\nHHOAA\n");

    element *temp = validate_file(cmd_buffer[1]);
    if (temp == NULL)
    {
        print_console("", "The file doesn't exists", true);
        return -2;
    }

    delete_tree(temp);
    g_print("\nHHOAA\n");
    remove_child(current_directory, temp, true);
    save_tree();

    return 1;
}

int cat(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }

    element *temp = validate_file(cmd_buffer[1]);
    g_print("FIle to read: %s, temp: %s\n", cmd_buffer[1], temp->name);
    if (temp)
    {
        inode *temp_node = find_inode(temp->file);
        int length = len_node(temp_node) * BLOCK_SIZE;
        char *data = (char *)malloc(length);
        read_(temp_node, data, length, 0);
        print_console("", data, true);
        free(data);
    }

    return 1;
}

int mv(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 3)
    {
        print_console("", "The function must have 2 arguments", true);
        return -1;
    }

    if (current_directory->child)
    {
        element *temp = retrieve(cmd_buffer[1]);

        if (temp)
        {
            strcpy(temp->name, cmd_buffer[2]);
            save_tree();
        }
        else
            print_console("", "File/Folder doesn't exists", true);
    }
    else
    {
        print_console("", "File/Folder doesn't exists", true);
    }

    return 1;
}

int lsattr(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }
    return 1;
}

int chattr(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }
    return 1;
}

int ls(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length > 1)
    {
        return -1;
    }

    if (current_directory->child != NULL)
    {
        element *temp = current_directory->child;

        while (temp != NULL)
        {
            if (temp->file == -1)
            {
                print_console("", "/", false);
            }
            print_console("", temp->name, true);
            temp = temp->sibling;
        }
    }

    return 1;
}

int echo(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }

    char *ptr = strtok(cmd_buffer[1], ">");

    if (ptr != NULL)
    {
        char *data = (char *)malloc(strlen(ptr));
        strcpy(data, ptr);
        ptr = strtok(NULL, ">");
        element *temp = validate_file(ptr);

        if (temp)
        {
            inode *temp_node = find_inode(temp->file);
            g_print("FILE: %s, FILE_BLOCK:%d, BLOCK: %d\n", temp->name, temp->file, temp_node->block);
            write_(temp_node, data, strlen(data), 0);
        }

        else
            print_console("", "Couldn't write | File doesn't exists", true);
        free(data);
    }

    return 1;
}

int vs_(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }

    if (strcmp(cmd_buffer[1], "-f") != 0)
    {
        print_console("", "Parameter must be '-f'", true);
        return -2;
    }
    update_view();
    return 1;
}
