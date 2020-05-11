/*
 *
 * Add Comments
 *
 */


#include "sockets.h"

int main(int argc, char* argv[]){
	int sockfd;
	//Run server version before client version to connect properly
	if(argc == 2){
		sockfd = CreateServer(argv);
	}
	else if(argc == 3){
		sockfd = CreateClient(argv);
	}
	else{
		fprintf(stderr, "\nInvalid Use...\nServer use: ./final <port>\nClient use: ./final <port> <server_name>\n\n");
		exit(0);
	}	

}
