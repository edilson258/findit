#ifndef FILESYSTEM_H
#define FILESYSTEM_H

typedef struct DirEntry {
  char* path;
  struct DirEntry* next;
} DirEntry;

char* file_to_buffer(char** file_path);
DirEntry* init_dir_entry(char* file_path);
void scan_dir(char* dir_path, DirEntry** dir_entry);

#endif
