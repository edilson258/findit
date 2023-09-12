#include <stdlib.h>

#include "include/findit.h"

TermFrequency* init_term_frequency(char** term) {
  TermFrequency* term_frequency = (TermFrequency*)malloc(sizeof(TermFrequency));
  term_frequency->term = *term;
  term_frequency->frequency = 1;
  return term_frequency;
}

FileTermFrequency* init_file_term_frequency(char** file_path) {
  FileTermFrequency* file_term_frequency;
  file_term_frequency = (FileTermFrequency*)malloc(sizeof(FileTermFrequency));
  file_term_frequency->file_path = *file_path;
  file_term_frequency->doc_rank = 0;
  file_term_frequency->term_frequency = NULL;
  file_term_frequency->next = NULL;
  return file_term_frequency;
}

DirFileTermFrequency* init_dir_file_term_frequency(char** dir_path) {
  DirFileTermFrequency* dir_file_term_frequency = (DirFileTermFrequency*)malloc(sizeof(DirFileTermFrequency));
  dir_file_term_frequency->dir_path = *dir_path;
  dir_file_term_frequency->file_term_frequency = NULL;
  return dir_file_term_frequency;
}

void add_term_frequency(FileTermFrequency** file_term_frequency, char** term) {
  if((*file_term_frequency)->term_frequency == NULL) {
    (*file_term_frequency)->term_frequency = (TermFrequency*)malloc(sizeof(TermFrequency*));
    (*file_term_frequency)->term_frequency = init_term_frequency(term);
    return;
  }

  TermFrequency* tmp = (*file_term_frequency)->term_frequency;
  while (tmp->next != NULL) {
    if(strcmp(tmp->term, *term) == 0) {
      tmp->frequency += 1;
      return;
    }
    tmp = tmp->next;
  }

  tmp->next = init_term_frequency(term);
}

void add_dir_file_term_frequency(DirFileTermFrequency** dir_file_term_frequency, FileTermFrequency** file_term_frequency) {
  if((*dir_file_term_frequency)->file_term_frequency == NULL) {
    (*dir_file_term_frequency)->file_term_frequency = *file_term_frequency;
    return;
  }

  FileTermFrequency* tmp = (*dir_file_term_frequency)->file_term_frequency;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = *file_term_frequency;
}
