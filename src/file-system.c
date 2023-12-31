#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "include/file-system.h"

char* file_to_buffer(char** file_path) {
  char* buffer = NULL;
  FILE* fp = NULL;
  long buf_size = 0;

  fp = fopen(*file_path, "r");

  if(fp == NULL) {
    perror("Failed to open file");
  }

  fseek(fp, 0, SEEK_END);
  buf_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  buffer = malloc(sizeof(char) * (buf_size));
  fread(buffer, sizeof(char), buf_size - 1, fp);
  buffer[buf_size] = '\0';

  fclose(fp);
  return buffer;
}

char* join_paths(char* dir_path, char* file_name) {
  int dir_path_len = strlen(dir_path);
  int file_name_len = strlen(file_name);

  char* full_path = (char*)malloc(sizeof(char) * (dir_path_len + file_name_len + 2));

  strcpy(full_path, dir_path);
  strcat(full_path, "/");
  strcat(full_path, file_name);

  return full_path;
}

DirEntry* init_dir_entry(char* file_path) {
  DirEntry* dir_entry = (DirEntry*)malloc(sizeof(DirEntry));
  dir_entry->path = file_path;
  dir_entry->next = NULL;
  return dir_entry;
}

void add_dir_entry(DirEntry** dir_entry, char* file_path) {
  if(*dir_entry == NULL) {
    *dir_entry = init_dir_entry(file_path);
    return;
  }

  DirEntry* tmp = *dir_entry;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = init_dir_entry(file_path);
}

int is_txt_file(char* file_name) {
  int str_len = strlen(file_name) - 1;
  if(
      file_name[str_len - 3] == '.' &&
      file_name[str_len - 2] == 't' &&
      file_name[str_len - 1] == 'x' &&
      file_name[str_len]     == 't'
    ) {
    return 1;
  }
  return 0;
}

void scan_dir(char** dir_path, DirEntry** dir_entry) {
  DIR* dp = opendir(*dir_path);
  if(dp == NULL) {
    perror("Failed to open dir");
  }
  struct dirent* entry;

  while((entry = readdir(dp))) {
    if(entry->d_type == DT_REG && is_txt_file(entry->d_name)) {
      char* file_path = join_paths(*dir_path, entry->d_name);
      add_dir_entry(dir_entry, file_path);
    } else if (entry->d_type == DT_DIR) {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
        continue;
      }
      char* entry_dir_path = join_paths(*dir_path, entry->d_name);
      scan_dir(&entry_dir_path, dir_entry);
    }
  }
}
