#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "include/file-system.h"

char* file_to_buffer(char** file_path) {
  char* buffer = NULL;
  FILE* fp = NULL;
  long contentSize = 0;

  fp = fopen(*file_path, "r");

  if(fp == NULL) {
    perror("Failed to open file");
  }

  fseek(fp, 0, SEEK_END);
  contentSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  buffer = malloc(sizeof(char) * (contentSize));
  fread(buffer, sizeof(char), contentSize - 1, fp);
  buffer[contentSize] = '\0';

  fclose(fp);
  return buffer;
}

char* join_paths(char* dir_path, char* file_name) {
  int dir_path_len = strlen(dir_path);
  int file_name_len = strlen(file_name);

  char* file_path = (char*)malloc(sizeof(char) * (dir_path_len + file_name_len + 2));

  strcpy(file_path, dir_path);
  strcat(file_path, "/");
  strcat(file_path, file_name);

  return file_path;
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

void scan_dir(char** dir_path, DirEntry** dir_entry) {
  DIR* dp = opendir(*dir_path);
  if(dp == NULL) {
    perror("Failed to open dir");
  }
  struct dirent* entry;

  while((entry = readdir(dp))) {
    if(entry->d_type == DT_REG) {
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
