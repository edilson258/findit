#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/file-system.h"

typedef struct {
  char* term;
  int frequency;
} TermFrequency;

typedef struct {
  TermFrequency** termFrequencies;
  int termFrequenciesLength;
} FileTermFrequencies;

FileTermFrequencies* initFileTermFrequencies(void) {
  FileTermFrequencies* fileTermFrequencies;
  fileTermFrequencies = (FileTermFrequencies*)malloc(sizeof(FileTermFrequencies));
  fileTermFrequencies->termFrequencies = (TermFrequency**)malloc(sizeof(TermFrequency**));
  return fileTermFrequencies;
}

int main(void) {
  char* filePath = "samples/file.txt";
  char* buffer = fileToBuffer(&filePath);

  int buf_cursor = 0;
  int token_start = 0;

  char break_chars[] = " ,.;?!\n\t";

  while (buffer[buf_cursor] != '\0') {
    if(strchr(break_chars, buffer[buf_cursor]) != NULL) {
      int token_size = (buf_cursor - token_start);
      if(token_size < 1) {
        buf_cursor++;
        token_start = buf_cursor;
        continue;
      };

      char* token = malloc(sizeof(char) * (token_size + 1));
      int token_cursor = 0;

      for (int i = token_start; i < buf_cursor; ++i) {
        token[token_cursor] = buffer[i];
        token_cursor++;
      }
      token[token_cursor] = '\0';
      printf("%s\n", token);

      buf_cursor++;
      token_start = buf_cursor;
      continue;
    }
    buf_cursor++;
  }

  return 0;
}
