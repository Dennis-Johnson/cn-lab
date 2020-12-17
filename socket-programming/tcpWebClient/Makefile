cc = clang
flags = -pedantic -Wall

all: client

client: client.c
	$(cc) $(flags) -o client client.c

clean: 
	rm -f *.o client
