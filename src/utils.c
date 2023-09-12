#include <stdlib.h>
#include <string.h>

#include "include/lexer.h"

char* append_dot(char* buffer) {
  int buffer_len = strlen(buffer);
  if(buffer[buffer_len - 1] != '.') {
    char* buffer_with_dot = (char*)malloc(sizeof(char) * (buffer_len + 2));
    strcpy(buffer_with_dot, buffer);
    strcat(buffer_with_dot, ".");
    return buffer_with_dot;
  }
  return buffer;
}

void display_raw_tokens(TokenList** root) {
  TokenList* tmp = *root;

  while (tmp != NULL) {
    printf("%s\n", tmp->token);
    tmp = tmp->next;
  }
}
