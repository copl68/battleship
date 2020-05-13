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
	clearBitmap(fb->bitmap, blank);
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

//Determines if a position will be in bounds of the framebuffer
bool inBounds(int pos){
	return (pos >= 0 && pos < 8);
}

//Randomly sets a piece of given length onto a given screen
void setPiece(int screen[8][8], int len){
	int xpos = rand() % 8;
	int ypos = rand() % 8;
	int dir = rand() % 3; 

	//Dir meanings
	//0 - Up
	//1 - Down
	//2 - Right
	//3 - Left
	
	int rows[8];
	int cols[8];

	if(dir <= 1){
	//Handles vertical ships
		if(dir == 0){ dir = -1;}
		for(int i = 0; i < len; i++){
			if(!(inBounds(xpos + (i*dir))) || (screen[xpos + (i*dir)][ypos] != 0)){
				setPiece(screen, len);
				return;			
			}
			else{
				//Adds to these arrays so that part of a ship is not placed when the space is invalid
				rows[i] = (xpos + (i*dir));
				cols[i] = ypos;
			}
		}
	}
	else if(dir >= 2){
	//Handles horizontal ships
		if(dir == 2){ dir = 1;}
		if(dir == 3){ dir = -1;}
		for(int i = 0; i < len; i++){
			if(!(inBounds(ypos + (i*dir))) || (screen[xpos][ypos + (i*dir)] != 0)){
				setPiece(screen, len);
				return;
			}
			else{
				//Adds to these arrays so that part of a ship is not placed when the space is invalid
				rows[i] = xpos;
				cols[i] = (ypos + (i*dir));
			}
		}
	}

	//Adds the entire ship once we know the entire ship can fit there
	for(int i = 0; i < len; i++){
		screen[rows[i]][cols[i]] = blue;
	}
}

int main(int argc, char* argv[]){
	signal(SIGINT, interrupt_handler);
	int sockfd;
	red = getColor(255,0,0);
	green = getColor(0,255,0);
	blue = getColor(0,0,255);
	blank = getColor(0,0,0);
	fb = getFBDevice();
	
	srand(time(0));
	int myScreen[8][8];
	int yourScreen[8][8];
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			myScreen[i][j] = blank;
			yourScreen[i][j] = blank;
		}
	}
	
	//Run server version before client version to connect properly
	if(argc == 2){
		//Sevrer
		sockfd = CreateServer(argv);
		setPiece(myScreen, 2);
		setPiece(myScreen, 3);
		setPiece(myScreen, 5);
		displayScreen(myScreen);
		sleep(2);
		displayScreen(yourScreen);
	}
	else if(argc == 3){
		//Client
		sockfd = CreateClient(argv);
		setPiece(myScreen, 2);
		setPiece(myScreen, 3);
		setPiece(myScreen, 5);
		displayScreen(myScreen);
	}
	else{
		fprintf(stderr, "\nInvalid Use...\nServer use: ./final <port>\nClient use: ./final <port> <server_name>\n\n");
		exit(0);
	}	

}
