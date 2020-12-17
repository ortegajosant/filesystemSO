#include "functions.c"

void print_console(char *path, char *cmd)
{
    if (strcmp(path, "") != 0)
    {
        gtk_text_buffer_insert(window_buffer, &text_iter, path, -1);
        gtk_text_buffer_insert(window_buffer, &text_iter, " >$ ", -1);
    }

    if (strcmp(cmd, "") != 0)
    {
        gtk_text_buffer_insert(window_buffer, &text_iter, cmd, -1);
        gtk_text_buffer_insert(window_buffer, &text_iter, "\n", -1);
    }
}

void clean_buffer()
{
    for (int i = 0; i < MAX_CMD_LENGTH; i++)
    {
        memset(cmd_buffer[i], 0, MAX_WORD_LENGTH);
    }
}

/*
    This function get the text gave in cmd_source and separate 
    it as array of strings with four string as the max limit
*/
int get_cmd_buffer(char cmd_dest[MAX_CMD_LENGTH][MAX_WORD_LENGTH], char *cmd_source, char *delim)
{
    char *ptr = strtok(cmd_source, delim);

    int count = 0;
    while (ptr != NULL)
    {
        if (count >= MAX_CMD_LENGTH)
            return -1;

        strcpy(cmd_dest[count], ptr);

        count++;
        ptr = strtok(NULL, delim);
    }

    return count;
}

/*
    This function get the text in the entry widget and manage it to 
    validate the command entered by the user
*/
gboolean get_key_function(GtkWidget *widget, gpointer data)
{
    int length = strlen(gtk_entry_get_text(GTK_ENTRY(textEntry)));
    cmd_entry = realloc(cmd_entry, length);
    strcpy(cmd_entry, gtk_entry_get_text(GTK_ENTRY(textEntry)));
    print_console("", cmd_entry);
    int result = get_cmd_buffer(cmd_buffer, cmd_entry, delim);
    if (result != -1)
    {
        // Folder functions
        if (strcmp(cmd_buffer[0], "mkdir") == 0)
            mkdir_(cmd_buffer, result);
        else if (strcmp(cmd_buffer[0], "rmdir") == 0)
            rmdir_(cmd_buffer, result);
        else if (strcmp(cmd_buffer[0], "cd") == 0)
        {
            if (cd(cmd_buffer, result) != -1)
            {
                g_print("Nice");
            }
        }
        else if (strcmp(cmd_buffer[0], "mv") == 0)
            mv(cmd_buffer, result);
        // File functions
        else if (strcmp(cmd_buffer[0], "touch") == 0)
            touch(cmd_buffer, result);
        else if (strcmp(cmd_buffer[0], "rm") == 0)
            rm(cmd_buffer, result);
        else if (strcmp(cmd_buffer[0], "cat") == 0)
            cat(cmd_buffer, result);
        else if (strcmp(cmd_buffer[0], "mv") == 0)
            mv(cmd_buffer, result);
        else if (strcmp(cmd_buffer[0], "lsattr") == 0)
            lsattr(cmd_buffer, result);
        else if (strcmp(cmd_buffer[0], "chattr") == 0)
            chattr(cmd_buffer, result);
        else if (strcmp(cmd_buffer[0], "ls") == 0)
            ls(cmd_buffer, result);
        else if (strcmp(cmd_buffer[0], "echo") == 0)
            echo(cmd_buffer, result);
        else
        {
            g_print("Resultado erróneo%s\n", cmd_buffer[0]);
        }
    }

    print_console(path_label, "");
    gtk_entry_set_text(GTK_ENTRY(textEntry), "");
    clean_buffer();
}