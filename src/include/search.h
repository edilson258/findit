#include "findit.h"

#ifndef SEARCH_H
#define SEARCH_H

typedef struct SearchOutput {
  char* path;
  float rank;
  struct SearchOutput* next;
} SearchOutput;

SearchOutput* search(DirFileTermFrequency** dftf, char** query);

#endif
