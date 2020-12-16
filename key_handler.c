#include "variables.h"
#include <string.h>

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

    return 1;
}

/*
    This function get the text in the entry widget and manage it to 
    validate the command entered by the user
*/
gboolean get_key_function(GtkWidget *widget, gpointer data)
{

    strcpy(cmd_entry, gtk_entry_get_text(GTK_ENTRY(textEntry)));
    g_print("%s\n", cmd_entry);
    int result = get_cmd_buffer(cmd_buffer, cmd_entry, delim);
    if (result != -1)
    {
        // Folder functions
        if (strcmp(cmd_buffer[0], "mkdir") == 0)
            g_print("Hola 1");
        else if (strcmp(cmd_buffer[0], "rmdir") == 0)
            g_print("Hola 2");
        else if (strcmp(cmd_buffer[0], "cd") == 0)
            gtk_label_set_text(GTK_LABEL(path_label), "/prueba/file");
        else if (strcmp(cmd_buffer[0], "mv") == 0)
            g_print("Hola 3");
        // File functions
        else if (strcmp(cmd_buffer[0], "touch") == 0)
            g_print("Hola 3");
        else if (strcmp(cmd_buffer[0], "rm") == 0)
            g_print("Hola 3");
        else if (strcmp(cmd_buffer[0], "cat") == 0)
            g_print("Hola 3");
        else if (strcmp(cmd_buffer[0], "mv") == 0)
            g_print("Hola 3");
        else if (strcmp(cmd_buffer[0], "lsattr") == 0)
            g_print("Hola 3");
        else if (strcmp(cmd_buffer[0], "chattr") == 0)
            g_print("Hola 3");
        else if (strcmp(cmd_buffer[0], "ls") == 0)
            g_print("Hola 3");
        else if (strcmp(cmd_buffer[0], "echo") == 0)
            g_print("Hola 3");
        else
        {
            g_print("Resultado %s\n", cmd_buffer[0]);
        }
    }

    gtk_entry_set_text(GTK_ENTRY(textEntry), "");
}