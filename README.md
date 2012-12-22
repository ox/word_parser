# Word Parser

Word Parser is a simple tool that pulls out space-or-punctiation-delimited words or newline-delimited lines out of a text file. It's meant to be very simple to use and "Just Work" when prototyping your projects. It stemmed from the need to have space and time efficient file parsing and attempts to serve such a purpose.

## EXAMPLE

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

## DOCUMENTATION

### parser_new(FILE \*)

Takes a `FILE *` that points to an open file, and returns a pointer to `struct Parser`.

### char * parser_next_word(struct Parser \*)

Returns a pointer to a newly allocated block of memory that holds the next word read from the file descriptor passed during the creation of `struct Parser *`. Returns NULL at EOF or if the parser is not appropriate.

### char * parser_next_line(struct Parser \*)

As with `parser_next_word(struct Parser *)`, returns a `char *` pointing to a newly allocated block of memory containing the next line extracted from the file descriptor. Returns NULL if EOF or if the parser is not appropriate.

### void parser_destroy(struct Parser *)

Closes the file descriptor given to the parser and `free`'s the pointer to the parser. If you don't want to close the descriptor, `free` only the parser.

## LICENSE

The MIT License (MIT)
Copyright (c) 2012 Artem Titoulenko

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.