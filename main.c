#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int main (int argc, char * argv[]) {
  FILE * fd;
  struct Parser * parser;
  char * word, * line;

  if (argc != 2) {
    fprintf(stderr, "usage: word_parser <file>\n");
    return 0;
  }

  fd = fopen(argv[1], "r");
  if (fd != NULL) {
    parser = parser_new(fd);


    while ( (word = parser_next_word(parser)) != NULL ) {
      printf("%s\n", word);
      free(word);
    }

  	rewind(fd);

		/* read each line, point `line` at the memory malloc'd in parser_next_line.
		   `line` may be an empty line*/
  	while ( (line = parser_next_line(parser)) != NULL) {
    	printf("line: [%s]\n", line);
    	free(line);
  	}

  	parser_destroy(parser);
	} else {
		fprintf(stderr, "Unable to open %s\n", argv[1]);
	}

  return 0;
}
