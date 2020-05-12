/*
 *
 * Add Comments
 *
 */

#include "sockets.h"

int red;
int green;
int blue;
int blank;
pi_framebuffer_t* fb;

//Displays the array passed to it onto the framebuffer
void displayScreen(int screen[8][8]){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			setPixel(fb->bitmap, i, j, screen[i][j]);
		}
	}
}

//Quits the program and cleans up any memory when the user types CTRL+C
void interrupt_handler(int sig){
	clearBitmap(fb->bitmap, blank);
	freeFrameBuffer(fb);
	exit(0);
}

int main(int argc, char* argv[]){
	signal(SIGINT, interrupt_handler);
	int sockfd;
	red = getColor(255,0,0);
	green = getColor(0,255,0);
	blue = getColor(0,0,255);
	blank = getColor(0,0,0);
	fb = getFBDevice();
	int myScreen[8][8];
	int yourScreen[8][8];
	
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
