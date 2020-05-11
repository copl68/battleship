final: final.o sockets.o
	gcc final.o sockets.o -o final
final.o: main.c sockets.h
	gcc -c main.c -o final.o
sockets.o: sockets.c sockets.h
	gcc -c sockets.c
clean: 
	rm -f final *.o
