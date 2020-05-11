/**
 * Name: Cole Plum
 * Date: 5.3.2020
 * File: Server.h
 * Description: The header file which imports the necessary libraries and declares the functions
 **/
#include <netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define BUFFER_SIZE 200

//Method descriptions in server.c

int CreateClient(char* argv[]);

int CreateServer(char* argv[]);

void ReceiveServer(char buffer[], int newsockfd);
