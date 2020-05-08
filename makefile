final: final.o server.o
	gcc final.o server.o -o final
final.o: main.c server.h
	gcc -c main.c -o final.o
server.o: server.c server.h
	gcc -c server.c
clean: 
	rm -f final *.o
