#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#define MAX_CMD_LENGTH 4
#define MAX_WORD_LENGTH 512

// Graphic variables
GtkWidget *window; //main window
GtkWidget *textArea;
GtkWidget *scrolledwindow;
GtkWidget *textEntry;
GtkWidget *console;
GtkWidget *button_cmd;
GtkWidget *tree_view;
GtkTextBuffer *window_buffer;
GtkTextIter text_iter;

char path_label[1024];

// Variables
char *cmd_entry;

char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH];
char delim[] = " ";

enum
{
    COLUMN = 0,
    NUM_COLS
};