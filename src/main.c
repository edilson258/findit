#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/file-system.h"
#include "include/findit.h"
#include "include/utils.h"
#include "include/lexer.h"

int main(void) {

  char* dir_path = "samples";
  DirEntry* dir_entries = NULL;

  scan_dir(dir_path, &dir_entries);
  DirFileTermFrequency* dftf = init_dir_file_term_frequency(&dir_path);

  while (dir_entries != NULL) {
    char* buffer = file_to_buffer(&dir_entries->path);

    TokenList* root = NULL;
    tokenizer(buffer, &root);

    free(buffer);

    FileTermFrequency* ftf = init_file_term_frequency(&dir_entries->path);

    TokenList* tmp = root;
    while (tmp != NULL) {
      add_term_frequency(&ftf, &tmp->token);
      tmp = tmp->next;
    }

    add_dir_file_term_frequency(&dftf, &ftf);

    dir_entries = dir_entries->next;
  }

  FileTermFrequency* tmp = dftf->file_term_frequency;

  while (tmp != NULL) {
    display_file_term_freq(&tmp);
    tmp = tmp->next;
  }
  return 0;
}
