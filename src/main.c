#include <stdio.h>

#include "include/index.h"
#include "include/search.h"

int main(void) {
  char* dir_path = "samples";
  DirFileTermFrequency* dir_file_term_frequency = index_dir(&dir_path);

  char* q = "cpu";
  SearchOutput* result = search(&dir_file_term_frequency, &q);

  while (result != NULL) {
    printf("%s => %f\n", result->path, result->rank);
    result = result->next;
  }

  return 0;
}
