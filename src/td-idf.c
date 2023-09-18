#include <math.h>
#include <stdlib.h>

#include "include/findit.h"

double tf(char* t, FileTermFrequency* d) {
  double curr_term_frequency = 0;
  double all_terms_frequencies = 0;

  TermFrequency* tmp = d->term_frequency;
  while (tmp != NULL) {
    if(strcmp(tmp->term, t) == 0) {
      curr_term_frequency = tmp->frequency;
    } else {
      all_terms_frequencies += tmp->frequency;
    }
    tmp = tmp->next;
  }

  if(curr_term_frequency <= 0) return 0;

  return curr_term_frequency / all_terms_frequencies;
}

double idf(int docs_amt, int docs_with_term) {
  if(docs_with_term <= 0) return 0;
  return log((double)docs_amt / docs_with_term);
}
