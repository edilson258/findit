#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/lexer.h"
#include "include/findit.h"

char* append_dot(char* buffer) {
  int buffer_len = strlen(buffer);
  if(buffer[buffer_len - 1] != '.') {
    char* buffer_with_dot = (char*)malloc(sizeof(char) * (buffer_len + 2));
    strcpy(buffer_with_dot, buffer);
    strcat(buffer_with_dot, ".");
    return buffer_with_dot;
  }
  return buffer;
}

void display_raw_tokens(TokenList** root) {
  TokenList* tmp = *root;

  while (tmp != NULL) {
    printf("%s\n", tmp->token);
    tmp = tmp->next;
  }
}

void display_file_term_freq(FileTermFrequency** root) {
  TermFrequency* tmp = (*root)->term_frequency;

  while (tmp != NULL) {
    printf("%s => %d\n", tmp->term, tmp->frequency);
    tmp = tmp->next;
  }
}

int calc_docs_with_term(DirFileTermFrequency* dir, char* t) {
  int docs_with_term = 0;
  FileTermFrequency* tmp = dir->file_term_frequency;
  while (tmp != NULL) {
    TermFrequency* tf_tmp = tmp->term_frequency;
    while (tf_tmp != NULL) {
      if(strcmp(tf_tmp->term, t) == 0) {
        docs_with_term += 1;
        break;
      }
      tf_tmp = tf_tmp->next;
    }
    tmp = tmp->next;
  }

  return docs_with_term;
}

void usage(void) {
  printf("Usage: findit <dir> <query>\n");
  printf("\tdir: the folder where to search\n");
  printf("\tquery: the search query\n");
}
