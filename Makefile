CC ?= gcc
CFLAGS ?= -pedantic -Wall

EXEC = word_parser
SRCS = parser.c main.c
OBJS = ${SRCS:.c=.o}

all: ${EXEC}

.c.o:
	${CC} ${CFLAGS} -o $@ -c $<

${EXEC}: ${OBJS}
	${CC} ${LDFLAGS} -o ${EXEC} ${OBJS}

test: ${EXEC}
	./${EXEC} test.txt

clean:
	rm ./${EXEC}
	rm ./*.o

.PHONEY: all clean
