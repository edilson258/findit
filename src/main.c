#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/file-system.h"
#include "include/utils.h"
#include "include/lexer.h"

int main(void) {
  char* file_path = "samples/file.txt";
  char* buffer = file_to_buffer(&file_path);
  char* buffer_with_dot = append_dot(buffer);

  TokenList* token_list = NULL;
  tokenizer(buffer_with_dot, &token_list);

  free(buffer);
  free(buffer_with_dot);

  display_raw_tokens(&token_list);

  return 0;
}
