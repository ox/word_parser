CC ?= gcc
CFLAGS ?= -pedantic -Wall

EXEC = word_parser
SRCS = word_parser.c
OBJS = ${SRCS:.c=.o}

all: ${EXEC}

.c.o:
	${CC} ${CFLAGS} -o $@ -c $<

${EXEC}: ${OBJS}
	${CC} ${LDFLAGS} -o ${EXEC} ${OBJS}

clean:
	rm ${EXEC}
	rm ./*.o

.PHONEY: all clean
