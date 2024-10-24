#include "../includes/utils.h"

char *read_file_contents(const char *path) {
    if(!path) { // technically 0 length file names exist 
        return NULL;        
    }

    FILE *path_fp = fopen(path, "r");
    if(!path_fp) {
        return NULL;
    }

    fseek(path_fp, 0, SEEK_END);
    size_t file_size = (size_t) ftell(path_fp);
    rewind(path_fp);

    char *contents = malloc(file_size + 1);
    contents[file_size] = '\0';
    
    if(fread(contents, file_size, sizeof(char), path_fp) == file_size) {
        return NULL;
    }

    return contents;
}

