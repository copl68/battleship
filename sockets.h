/**
 * Name: Cole Plum & Mina Rulis
 * Date: 5.11.2020
 * File: Sockets.h
 * Description: The header file which imports the necessary libraries and declares the functions
 **/
#include<time.h>
#include<signal.h>
#include<sense/sense.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define BUFFER_SIZE 200

//Method descriptions in sockets.c

int CreateClient(char* argv[]);

int CreateServer(char* argv[]);

void RecvMsg(int newsockfd, char buffer[]);

void SendMsg(int newsockfd, char buffer[]);
