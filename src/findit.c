#include <stdlib.h>

#include "include/findit.h"

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
