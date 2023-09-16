#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/findit.h"
#include "include/index.h"
#include "include/lexer.h"
#include "include/utils.h"

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

  return curr_term_frequency / all_terms_frequencies;
}

double idf(double docs_amt, double docs_with_term) {
  return log(docs_amt / docs_with_term);
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

void search(char* query, DirFileTermFrequency* dir_file_term_frequency) {
  TokenList* query_tokens;
  tokenizer(append_dot(query), &query_tokens);

  FileTermFrequency* files = dir_file_term_frequency->file_term_frequency;
  while (files != NULL) {
    TokenList* tokens_tmp = query_tokens;
    while (tokens_tmp != NULL) {
      double docs_with_term = calc_docs_with_term(dir_file_term_frequency, tokens_tmp->token);
      files->doc_rank += tf(tokens_tmp->token, files) * idf(dir_file_term_frequency->docs_amt, docs_with_term);
      tokens_tmp = tokens_tmp->next;
    }
    files = files->next;
  }

  files = dir_file_term_frequency->file_term_frequency;

  while (files != NULL) {
    printf("%s => %f\n", files->file_path, files->doc_rank);
    files = files->next;
  }
}

void usage(void) {
  printf("Usage: findit <dir> <query>\n");
  printf("\tdir: the folder where to search\n");
  printf("\tquery: the search query\n");
}

int main(int argc, char** argv) {
  if(argc <= 2) {
    usage();
    printf("ERROR: Not enough args passed\n");
    exit(1);
  }

  char* dir_path = argv[1];
  DirFileTermFrequency* dir_file_term_frequency = index_dir(&dir_path);

  char* query = argv[2];
  search(query, dir_file_term_frequency);
  return 0;
}
