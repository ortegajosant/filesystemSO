#include "variables.h"

GtkWidget *createConsoleBox(GtkWidget *window)
{
    textArea = gtk_text_view_new();
    scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    textEntry = gtk_entry_new();
    console = gtk_grid_new();
    path_label = gtk_label_new("/prueba");
    GtkWidget *console_top = gtk_grid_new();

    gtk_grid_set_row_homogeneous(GTK_GRID(console), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(console), TRUE);
    
    gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea);
    gtk_grid_attach(GTK_GRID(console_top), path_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(console_top), textEntry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(console), scrolledwindow, 0, 2, 1, 8);
    gtk_grid_attach(GTK_GRID(console), console_top, 0, 1, 1, 1);

    return console;
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "FileSystem");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480); // does not  matter this size
    gtk_container_add(GTK_CONTAINER(window), createConsoleBox(window));
    gtk_widget_show_all(window);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE); //because of this
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_main();
    return 0;
}