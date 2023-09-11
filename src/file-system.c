#include <stdio.h>
#include <stdlib.h>

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
