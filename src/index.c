#include <stdio.h>

#include "include/findit.h"
#include "include/file-system.h"
#include "include/lexer.h"

DirFileTermFrequency* index_dir(char** dir_path) {
  DirFileTermFrequency* dir_file_term_frequency = init_dir_file_term_frequency(dir_path);

  DirEntry* dir_entry_root = NULL;
  scan_dir(dir_path, &dir_entry_root);

  while (dir_entry_root != NULL) {
    char* buffer = file_to_buffer(&dir_entry_root->path);

    TokenList* token_list_root = NULL;
    tokenizer(buffer, &token_list_root);

    free(buffer);

    FileTermFrequency* file_term_frequency = init_file_term_frequency(&dir_entry_root->path);

    TokenList* token_list_tmp = token_list_root;
    while (token_list_tmp != NULL) {
      add_term_frequency(&file_term_frequency, &token_list_tmp->token);
      token_list_tmp = token_list_tmp->next;
    }

    add_dir_file_term_frequency(&dir_file_term_frequency, &file_term_frequency);
    dir_file_term_frequency->docs_amt += 1;

    dir_entry_root = dir_entry_root->next;
  }

  return dir_file_term_frequency;
}
