#ifndef LEXER_H
#define LEXER_H

typedef struct TokenList {
  char* token;
  struct TokenList* next;
} TokenList;

void tokenizer(char* buffer,  TokenList** token_list);

#endif
