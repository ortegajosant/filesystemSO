#include "disk_manager.c"
#include <json-c/json.h>

// char word[20];

// void clean_word() 
// {
//     for (int i = 0; i < 20; i++)
//     {
//         word[i] = '\0';
//     }
// }

// void write_tree (char* buffer, int* iter, element* parent) 
// {
//     strcpy(buffer + *iter, "{");
//     *iter = *iter + 1;

//     strcpy(word, parent->name);
//     strcpy(buffer + *iter, word);
//     *iter = *iter + strlen(word);
//     strcpy(buffer + *iter, ":");
//     *iter = *iter + 1;
//     clean_word();

//     strcpy(buffer + *iter, "}");
//     *iter = *iter + 1;
// }

void save_tree () 
{
    // FILE* file;
    // file = fopen("bin/filesystem.json","w");

    // char* buffer = (char*)malloc(sizeof(char) * 1024);
    // int* iter = (int*)malloc(sizeof(int));
    // *iter = 0;

    // write_tree(buffer, iter, root);
    // fputs(buffer, file);

    // free(buffer);
    // free(iter);

    json_object* root = json_object_new_object();
    json_object* disk = json_object_new_array();
    
    json_object_object_add(root, "root", disk);

    // fclose(file);
}