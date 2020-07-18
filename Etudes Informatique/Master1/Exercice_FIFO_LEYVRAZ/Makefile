CC=gcc
CFLAGS= -W -Wall -O2 -pthread
LDFLAGS= -lpthread
EXEC= lecteur_redacteur_fifo 

all: $(EXEC)

lecteur_redacteur_fifo: lecteur_redacteur_fifo.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
clean:
	rm *.o

clean_all:
	rm *.o lecteur_redacteur_fifo
