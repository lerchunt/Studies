CC=gcc
CFLAGS=-Wfatal-errors -Wall -g

OBJ = lexer.o parser.o type.o list.o ast.o main.o 
FLEXFILES = lexer.l 
YACCFILES = parser.y 
TARGET = min-ml

all: $(TARGET) 

lexer.l: parser.h ast.h
parser.y: ast.h

%.c: %.l
	flex -o $@ $<

%.c: %.y
	bison -t -d -o $@ $<

%.h: %.c
	@touch $@

%.o: %.c  
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
		$(CC) -o $@ $(OBJ) $(CFLAGS)

.PHONY: clean cleanest
clean:
	rm -rf *.o lexer.c lexer.h minml parser.c parser.h
cleanest: clean
	rm min-ml

