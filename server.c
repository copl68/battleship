/**
 * Name: Cole Plum
 * Date: 5/3/2020
 * File: server.c
 * Description: Takes care of socket connection functions such as creating sockets, connecting them, sending, and receiveing. 
 **/
#include "server.h"

//Creates a socket and binds it to our address to create the server. It then waits for and accepts a connection
int CreateServer(int argc, char* argv[]){
	int sockfd, portno, clien;
	struct sockaddr_in serv_addr, cli_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){ fprintf(stderr, "Error: Cannot create socket\n"); exit(1);}
	bzero((char*) &serv_addr, sizeof(serv_addr));
	if(argc == 1){
		portno = 8080;
	}
	else if(argc == 2){
		portno = atoi(argv[1]);
	}
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0){
		fprintf(stderr, "Error: Could not bind\n"); exit(1);
	}
	listen(sockfd, 5);
	clien = sizeof(cli_addr);
	int newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clien);
	if(newsockfd < 0){ fprintf(stderr, "Error: Could not accept\n"); exit(1);}
	return newsockfd;
}

//Receives a message from the client
void ReceiveServer(char buffer[], int newsockfd){
	bzero(buffer, BUFFER_SIZE);
	int n = recv(newsockfd, buffer, BUFFER_SIZE-1, 0);
	if(n < 0){ fprintf(stderr, "Error: Cannot read from socket\n"); exit(1);}

}

//Sends a message back to the client
void SendServer(int newsockfd, char buffer[]){
	int n = send(newsockfd, buffer, BUFFER_SIZE, 0);
	if(n < 0){
		fprintf(stderr, "Error: Could not send message"); exit(1);
	}
}

