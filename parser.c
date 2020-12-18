#include "disk_manager.c"
#include <json-c/json.h>

void add_children(json_object* directory, element* parent)
{
    element* temp_e = parent->child;
    json_object *child, *name, *is_folder, *contents, *block;
    while (temp_e != NULL)
    {
        json_object* child = json_object_new_object();
        name = json_object_new_string(temp_e->name);
        contents = json_object_new_array();
        if (temp_e->file != -1) 
        {
            is_folder = json_object_new_boolean(false);
            inode* node = find_inode(temp_e->file);
            while (node != NULL)
            {
                block = json_object_new_int(node->block);
                json_object_array_add(contents, block);
                node = node->next_inode;
            }
        }
        else 
        {
            is_folder = json_object_new_boolean(true);
            add_children(contents, temp_e);
        }
        json_object_object_add(child, "name", name);
        json_object_object_add(child, "is_folder", is_folder);
        json_object_object_add(child, "contents", contents);
        json_object_array_add(directory, child);
        temp_e = temp_e->sibling;
    }
}

void save_tree () 
{
    FILE* file;
    file = fopen("bin/filesystem.json","w");

    json_object* filesystem = json_object_new_object();
    json_object* disk = json_object_new_array();
    add_children(disk, root);
    json_object_object_add(filesystem, "root", disk);

    const char* json = json_object_to_json_string(filesystem);
    fputs(json, file);

    json_object_put(filesystem);
    fclose(file);
}

void parse_children(json_object* directory)
{
    size_t n_elements = json_object_array_length(directory);
    json_object *child, *name, *is_folder, *contents, *block;
    for (int i = 0; i < n_elements; i++)
    {
        child = json_object_array_get_idx(directory, i);
        json_object_object_get_ex(child, "name", &name);
        json_object_object_get_ex(child, "is_folder", &is_folder);
        json_object_object_get_ex(child, "contents", &contents);
        if (json_object_get_boolean(is_folder) == false) 
        {
            int n_blocks = json_object_array_length(contents);
            block = json_object_array_get_idx(contents, 0);
            add_child(current_directory, false, 
                        json_object_get_string(name), json_object_get_int(block));
            inode* node = find_inode(json_object_get_int(block));
            for (int j = 1; j < n_blocks; j++)
            {
                block = json_object_array_get_idx(contents, j);
                add_inode(node, json_object_get_int(block));
            }
        }
        else 
        {
            add_child(current_directory, true, 
                        json_object_get_string(name), -1);
            locate(false, json_object_get_string(name));
            parse_children(contents);
            locate(true, "");
        }
    }
}

void load_tree()
{
    FILE* file;
    file = fopen("bin/filesystem.json","r");

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* json = (char*)malloc(sizeof(char) * size);
    fread(json, 1, size, file);
    fclose(file);

    json_object* filesystem = json_tokener_parse(json);
    json_object* disk;
    json_object_object_get_ex(filesystem, "root", &disk);
    create_tree();
    parse_children(disk);
}