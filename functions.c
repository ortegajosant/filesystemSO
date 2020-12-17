#include "variables.h"
#include <string.h>

int mkdir_(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }
    return 1;
}
int rmdir_(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }
    return 1;
}

int cd(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length > 2)
    {
        return -1;
    }
    strcat(path_label, cmd_buffer[1]);
    strcat(path_label, "/");
    return 1;
}

int touch(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }
    return 1;
}

int rm(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }
    return 1;
}

int cat(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }
    return 1;
}

int mv(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
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
    if (length != 2)
    {
        return -1;
    }
    return 1;
}

int echo(char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH], int length)
{
    if (length != 2)
    {
        return -1;
    }
    return 1;
}
