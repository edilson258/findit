#include <stdio.h>
#include <stdlib.h>

#include "include/findit.h"
#include "include/index.h"
#include "include/lexer.h"
#include "include/utils.h"
#include "include/td-idf.h"

void search(char* query, DirFileTermFrequency* dir_file_term_frequency) {
  TokenList* query_tokens;
  tokenizer(append_dot(query), &query_tokens);

  FileTermFrequency* files = dir_file_term_frequency->file_term_frequency;

  while (files != NULL) {
    TokenList* tokens_tmp = query_tokens;
    while (tokens_tmp != NULL) {
      int docs_with_term = calc_docs_with_term(dir_file_term_frequency, tokens_tmp->token);
      files->doc_rank += tf(tokens_tmp->token, files) * idf(dir_file_term_frequency->docs_amt, docs_with_term);
      printf("Rank of %s is %f\n", files->file_path, files->doc_rank);
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
