#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "parser.h"

struct Parser * parser_new(FILE * fd) {
	if (!fd)
		return NULL;

  struct Parser * tmp = malloc(sizeof(struct Parser));
  tmp->fd = fd;

  return tmp;
}

void parser_destroy(struct Parser * parser) {
	if (!parser)
		return;

  fclose(parser->fd);
  free(parser);
}

char * parser_next_word(struct Parser * parser) {
	if (!parser)
		return NULL;

  char c;
  char * word;
  int word_length = 0;

  do { c = fgetc(parser->fd); } while ( c != EOF && !isalnum(c) );
  fseek(parser->fd, -1, SEEK_CUR); /* rewind 1 char */

  do {
    c = fgetc(parser->fd);
    if ( !isalnum(c) ) { break; }
    word_length++;
  } while (c != EOF);

  if (word_length == 0) { return NULL; }

  fseek(parser->fd, -(word_length + 1), SEEK_CUR);
  word = calloc(1,word_length + 1);
  fread(word, sizeof(char), word_length, parser->fd);

  return word;
}

char * parser_next_line(struct Parser * parser) {
	if (!parser)
		return NULL;

  char c = ' ';
  int count = 0;
  int cur_max = 128;
  char * line = calloc(1,cur_max + 1);

  while ( (c != '\n') && (!feof(parser->fd)) ) {
    if (count == cur_max) {
      cur_max *= 2;
      line = realloc(line, cur_max);
    }
    c = fgetc(parser->fd);
    line[count++] = c;
  }

  if (count == 0 || line[0] == 0) {
    return NULL;
  }

  line[count - 1] = '\0';
  return line;
}

