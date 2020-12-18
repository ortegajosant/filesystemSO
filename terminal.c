#include "key_handler.c"

void fill_model(element *folder, GtkTreeStore *treestore, GtkTreeIter toplevel)
{
    GtkTreeIter child;
    while (folder != NULL)
    {
        gtk_tree_store_append(treestore, &child, &toplevel);
        gtk_tree_store_set(treestore, &child, COLUMN, folder->name, -1);
        if (folder->file == -1)
        {
            fill_model(folder->child, treestore, child);
        }
        folder = folder->sibling;
    }
}

GtkTreeModel *create_and_fill_model()
{
    GtkTreeStore *treestore;
    GtkTreeIter toplevel, child, child2;

    treestore = gtk_tree_store_new(NUM_COLS,
                                   G_TYPE_STRING);
    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel,
                       COLUMN, root->name,
                       -1);
    fill_model(root->child, treestore, toplevel);

    return GTK_TREE_MODEL(treestore);
}

GtkWidget *create_visualization()
{
    GtkTreeViewColumn *col;
    GtkCellRenderer *renderer;
    GtkTreeModel *model;

    tree_view = gtk_tree_view_new();

    col = gtk_tree_view_column_new();
    gtk_tree_view_column_set_title(col, "FILE SYSTEM");
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), col);

    renderer = gtk_cell_renderer_text_new();
    gtk_tree_view_column_pack_start(col, renderer, TRUE);
    gtk_tree_view_column_add_attribute(col, renderer,
                                       "text", COLUMN);

    model = create_and_fill_model();
    gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), model);
    g_object_unref(model);

    return tree_view;
}

void update_view()
{
    GtkWidget *window_sub;
    GtkWidget *tree_update;
    window_sub = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *console_top = gtk_grid_new();

    gtk_window_set_title(GTK_WINDOW(window_sub), "FileSystemTerm");
    gtk_window_set_default_size(GTK_WINDOW(window_sub), 480, 320); // does not  matter this size
    gtk_container_add(GTK_CONTAINER(window_sub), console_top);
    gtk_window_set_resizable(GTK_WINDOW(window_sub), FALSE); //because of this
    g_signal_connect(G_OBJECT(window_sub), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_grid_set_row_homogeneous(GTK_GRID(console_top), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(console_top), TRUE);

    create_visualization();
    gtk_grid_attach(GTK_GRID(console_top), tree_view, 0, 1, 1, 1);

    gtk_widget_show_all(window_sub);

    gtk_main();
}

GtkWidget *createConsoleBox(GtkWidget *window)
{
    // Env variables
    load_tree();
    strcpy(path_label, "/");
    add_name_to_path(path_label, root->name);

    // GUI Widgets
    textArea = gtk_text_view_new();
    scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    textEntry = gtk_entry_new();
    console = gtk_grid_new();
    GtkWidget *console_top = gtk_grid_new();
    GtkWidget *console_bottom = gtk_grid_new();
    button_cmd = gtk_button_new_with_label("Ejecutar");

    g_signal_connect(button_cmd, "clicked",
                     G_CALLBACK(get_key_function), NULL);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textArea), FALSE);

    gtk_grid_set_row_homogeneous(GTK_GRID(console), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(console), TRUE);
    gtk_grid_set_row_homogeneous(GTK_GRID(console_bottom), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(console_bottom), TRUE);

    gtk_container_add(GTK_CONTAINER(scrolledwindow), textArea);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textArea), GTK_WRAP_WORD);

    // Buffer initialization
    window_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textArea));
    gtk_text_buffer_get_iter_at_offset(window_buffer, &text_iter, 0);
    gtk_grid_attach(GTK_GRID(console_top), textEntry, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(console_top), button_cmd, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(console_bottom), scrolledwindow, 0, 1, 2, 10);
    gtk_grid_attach(GTK_GRID(console), console_top, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(console), console_bottom, 0, 1, 1, 10);

    print_console(path_label, "", true);

    return console;
}

void gtk_main_initialiciation(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "FileSystemTerm");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480); // does not  matter this size
    gtk_container_add(GTK_CONTAINER(window), createConsoleBox(window));
    gtk_widget_show_all(window);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE); //because of this
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    cmd_entry = (char *)malloc(128);
}

int main(int argc, char *argv[])
{
    gtk_main_initialiciation(argc, argv);
    gtk_main();
    return 0;
}