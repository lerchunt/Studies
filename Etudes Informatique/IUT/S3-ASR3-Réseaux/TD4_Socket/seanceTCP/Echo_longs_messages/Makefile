CC= gcc
CFLAGS= -Wall
EXEC = client serveur

all: ${EXEC}

client:	client.c
	${CC} ${CFLAGS} client.c -o client

serveur:	serveur.c
	${CC} ${CFLAGS} serveur.c -o serveur

clean:
	rm -f ${EXEC} *.o *~
