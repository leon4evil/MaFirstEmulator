#include   //input
#include   //graphics
#include "chip8emulatorcore.h"

chip8 mychip8;

int main(int argc, char **argv){
		
	
	setupGraphics();	//set up render(graphics) system
	setupInput();		//setup input system


	// Initialize the Chip8 system and load the game into the memory
	mychip8.initialize();
	mychip8.loadgame('pong');

	// Emulation loop
	for(;;){

		//emulate one cycle
		myChip8.emulateCycle();

		//if the draw flag is set, update the screen
		if(myChip8.drawFlag)
      	drawGraphics();

     	// Store key press state (Press and Release)
    	myChip8.setKeys();

    	if(delay_timer>0){//timer will makes the emulator run at 60Hz
    		usleep(16666);
    		delay_timer--;
    	}

	}

	return 0;
}