CC = clang
CFLAGS = -pedantic -Wall

all: server client

server: server.c
	$(CC) $(CFLAGS) -o server server.c

client: client.c
	$(CC) $(FLAGS) -o client client.c

clean:
	rm -rf *.o 