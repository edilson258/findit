#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "include/file-system.h"

typedef struct TermFrequency {
  char* term;
  int frequency;
  struct TermFrequency* next;
} TermFrequency;

typedef struct {
  char* file_path;
  TermFrequency* term_frequencies;
} FileTermFrequencies;

TermFrequency* init_term_frequency(char** term) {
  TermFrequency* term_frequency = (TermFrequency*)malloc(sizeof(TermFrequency));
  term_frequency->term = *term;
  term_frequency->frequency = 0;
  return term_frequency;
}

FileTermFrequencies* init_file_term_frequencies(char** file_path) {
  FileTermFrequencies* file_term_frequencies;
  file_term_frequencies = (FileTermFrequencies*)malloc(sizeof(FileTermFrequencies));
  file_term_frequencies->file_path = *file_path;
  file_term_frequencies->term_frequencies =  NULL;
  return file_term_frequencies;
}

void add_term_frequency(FileTermFrequencies** file_term_frequencies, char** term) {
  if((*file_term_frequencies)->term_frequencies == NULL) {
    (*file_term_frequencies)->term_frequencies = (TermFrequency*)malloc(sizeof(TermFrequency*));
    (*file_term_frequencies)->term_frequencies = init_term_frequency(term);
    return;
  }

  TermFrequency* tmp = (*file_term_frequencies)->term_frequencies;
  while (tmp->next != NULL) {
    if(strcmp(tmp->term, *term) == 0) {
      tmp->frequency += 1;
      return;
    }
    tmp = tmp->next;
  }

  tmp->next = init_term_frequency(term);
}

void display_list(FileTermFrequencies** file_term_frequencies) {
  TermFrequency* tmp = (*file_term_frequencies)->term_frequencies;

  while (tmp != NULL) {
    printf("%s -> %d\n", tmp->term, tmp->frequency);
    tmp = tmp->next;
  }
}

int main(void) {
  char* file_path = "samples/file.txt";
  char* buffer = file_to_buffer(&file_path);

  FileTermFrequencies* file_term_frequencies;
  file_term_frequencies = init_file_term_frequencies(&file_path);

  int buf_cursor = 0;
  int token_start = 0;

  char break_chars[] = " ,.;?!()\n\t";

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

      add_term_frequency(&file_term_frequencies, &token);


      buf_cursor++;
      token_start = buf_cursor;
      continue;
    }
    buf_cursor++;
  }
  display_list(&file_term_frequencies);
  return 0;
}
