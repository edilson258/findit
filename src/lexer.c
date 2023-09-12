#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/lexer.h"

TokenList* init_token(char** token) {
  TokenList* token_list = (TokenList*)malloc(sizeof(TokenList));
  token_list->token = *token;
  token_list->next = NULL;
  return token_list;
}

void add_token2list(TokenList** root, char** token) {
  if((*root) == NULL) {
    *root = init_token(token);
    return;
  }
  TokenList* tmp = *root;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = init_token(token);
}

void tokenizer(char* buffer, TokenList** root) {
  int buf_cursor = 0;
  int token_start = 0;

  char break_chars[] = " ,.;?!()\n\t";

  while (buffer[buf_cursor] != '\0') {
    if(strchr(break_chars, buffer[buf_cursor]) != NULL) {
      int token_size = (buf_cursor - token_start);
      if(token_size < 1) {
        buf_cursor++;
        token_start = buf_cursor;
        continue;
      };

      char* token = malloc(sizeof(char) * (token_size + 1));
      int token_cursor = 0;

      for (int i = token_start; i < buf_cursor; ++i) {
        token[token_cursor] = tolower(buffer[i]);
        token_cursor++;
      }
      token[token_cursor] = '\0';

      add_token2list(root, &token);

      buf_cursor++;
      token_start = buf_cursor;
      continue;
    }
    buf_cursor++;
  }
}
