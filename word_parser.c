#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int main (int argc, char * argv[]) {
  FILE * fd;
  struct Parser parser;
  char * word;

  if (argc != 2) {
    fprintf(stderr, "usage: word_parser <file>\n");
    return 0;
  }

  fd = fopen(argv[1], "r");
  if (fd != NULL) {
    parser = parser_new(fd);

    while ( word = parser_next_word(parser) ) {
      printf("%s\n", word);
    }
  }

  parser_destroy(parser);

  return 0;
}
