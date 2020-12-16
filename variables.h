#include <gtk/gtk.h>

#define MAX_CMD_LENGTH 4
#define MAX_WORD_LENGTH 50

GtkWidget *window; //main window
GtkWidget *textArea;
GtkWidget *scrolledwindow;
GtkWidget *textEntry;
GtkWidget *console;
GtkWidget *path_label;
GtkWidget *button_cmd;

//
char cmd_entry[100];
char cmd_buffer[MAX_CMD_LENGTH][MAX_WORD_LENGTH];
char delim[] = " ";