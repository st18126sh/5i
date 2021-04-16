.PHONY: all
all: ser cli

ser: server.o
	gcc -o ser server.o

cli: client.o
	gcc -o cli client.o

ser.o: server.c
	gcc -c server.c

cli.o: client.c
	gcc -c client.c

.PHONY: clean

clean:
	rm -f ser cli server.o client.o *~

.PHONY: exe

exe: ser cli
	./ser &
	./cli &
	./cli &
