#include "lexer.h"
#include "findit.h"

char* append_dot(char* buffer);
void display_raw_tokens(TokenList** root);
void display_file_term_freq(FileTermFrequency** root);
int calc_docs_with_term(DirFileTermFrequency* dir, char* t);
void usage(void);
