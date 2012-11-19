#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

struct Parser * parser_new(FILE * fd) {
  struct Parser * tmp = malloc(sizeof(struct Parser));
  tmp->fd = fd;

  return tmp;
}

void parser_destroy(struct Parser * parser) {
  fclose(parser->fd);
  free(parser);
}

char * parser_next_word(struct Parser * parser) {
  char c;
  char * word;
  int word_length = 0;

  while ( c = fgetc(parser->fd), c != EOF || c == ' ' ) {
    if ( c < 48 || (c > 57 && c < 65) || ( c > 90 && c < 97) || c > 122) {
      break;
    }

    word_length++;
  }

  word = malloc(word_length + 1);


  return word;
}

