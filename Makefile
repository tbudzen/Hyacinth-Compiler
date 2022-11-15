CC 	= g++-6

FLAGS 	= -std=c++17 --pedantic -Wall -Wextra

all: 	kompilator

kompilator: parser.o lexer.o codeGenerator.o compiler.o
	$(CC) $(FLAGS) -o kompilator codeGenerator.o parser.o lexer.o compiler.o

codeGenerator.o: codeGenerator.cpp
	$(CC) $(FLAGS) -c codeGenerator.cpp

compiler.o: compiler.cpp
	$(CC) $(FLAGS) -c compiler.cpp

lexer.o: lexer.c	
	$(CC) $(FLAGS) -c lexer.c

parser.o: parser.tab.c
	$(CC) $(FLAGS) -c parser.tab.c -o parser.o

lexer.c: lexer.l
	flex -o lexer.c lexer.l

parser.tab.c: parser.y
	bison --no-lines -d parser.y

clean:
	rm -f *.o *~ *.c *.tab.c *.tab.h kompilator
