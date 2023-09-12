#ifndef FINDIT_H
#define FINDIT_H

typedef struct TermFrequency {
  char* term;
  int frequency;
  struct TermFrequency* next;
} TermFrequency;

typedef struct {
  char* file_path;
  TermFrequency* term_frequencies;
} FileTermFrequencies;

TermFrequency* init_term_frequency(char** term);
FileTermFrequencies* init_file_term_frequencies(char** file_path);
void add_term_frequency(FileTermFrequencies** file_term_frequencies, char** term);

#endif
