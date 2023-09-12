#include <stdio.h>
#include <stdlib.h>

#include "include/search.h"
#include "include/findit.h"

SearchOutput* init_search_output(char** path, float rank) {
  SearchOutput* output = (SearchOutput*)malloc(sizeof(SearchOutput));
  output->path = *path;
  output->rank = rank;
  output->next = NULL;
  return output;
}

void add_search_output(SearchOutput** root, char** path, float rank) {
  if(*root == NULL) {
    *root = init_search_output(path, rank);
    return;
  }

  SearchOutput* tmp = *root;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = init_search_output(path, rank);
}

SearchOutput* search(DirFileTermFrequency** dftf, char** query) {
  SearchOutput* result = NULL;

  FileTermFrequency* ftf_tmp = (*dftf)->file_term_frequency;
  while (ftf_tmp != NULL) {

    TermFrequency* tf_tmp = ftf_tmp->term_frequency;
    while (tf_tmp != NULL) {
      if(strcmp(tf_tmp->term, *query) == 0) {
        add_search_output(&result, &ftf_tmp->file_path, tf_tmp->frequency);
        break;
      }
      tf_tmp = tf_tmp->next;
    }
    ftf_tmp = ftf_tmp->next;
  }

  return result;
}
