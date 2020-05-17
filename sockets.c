/**
 * Name: Cole Plum & Mina Rulis
 * Date: 5/11/2020
 * File: sockets.c
 * Description: Takes care of socket connection functions such as creating sockets, connecting them, sending, and receiveing. 
 **/
#include "sockets.h"

//Creates a socket and connects it to our address to create a client
int CreateClient(char* argv[]){
	int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockfd < 0){ fprintf(stderr, "Error opening socket\n"); exit(0);}
	
	struct hostent *server = gethostbyname(argv[2]);
	if(server == NULL){fprintf(stderr, "Error: no such host\n"); exit(0);}
	
	int portno = atoi(argv[1]);	
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);
	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		fprintf(stderr, "Error connecting\n"); exit(0);
	}
	return sockfd;
}

//Creates a socket and binds it to our address to create the server. It then waits for and accepts a connection
int CreateServer(char* argv[]){
	int sockfd, portno, clien;
	struct sockaddr_in serv_addr, cli_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){ fprintf(stderr, "Error: Cannot create socket\n"); exit(1);}
	bzero((char*) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
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
void RecvMsg(int newsockfd, char buffer[]){
	bzero(buffer, BUFFER_SIZE);
	printf("Receiving (buffer before): %s\n", buffer);
	int n = recv(newsockfd, buffer, BUFFER_SIZE-1, 0);
	printf("Receiving (buffer after): %s\n", buffer);
	if(n < 0){ fprintf(stderr, "Error: Cannot read from socket\n"); exit(1);}
}

//Sends a message back to the client
void SendMsg(int newsockfd, char buffer[]){
	int n = send(newsockfd, buffer, BUFFER_SIZE, 0);
	printf("Sending: %s\n", buffer);
	bzero(buffer, BUFFER_SIZE);
	if(n < 0){
		fprintf(stderr, "Error: Could not send message"); exit(1);
	}
}

