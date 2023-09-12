#ifndef FINDIT_H
#define FINDIT_H

typedef struct TermFrequency {
  char* term;
  int frequency;
  struct TermFrequency* next;
} TermFrequency;

typedef struct FileTermFrequency {
  char* file_path;
  float doc_rank;
  TermFrequency* term_frequency;
  struct FileTermFrequency* next;
} FileTermFrequency;

typedef struct {
  char* dir_path;
  FileTermFrequency* file_term_frequency;
} DirFileTermFrequency;

TermFrequency* init_term_frequency(char** term);
FileTermFrequency* init_file_term_frequency(char** file_path);
DirFileTermFrequency* init_dir_file_term_frequency(char** dir_path);
void add_term_frequency(FileTermFrequency** file_term_frequency, char** term);
void add_dir_file_term_frequency(DirFileTermFrequency** dir_file_term_frequency, FileTermFrequency** file_term_frequency);

#endif
