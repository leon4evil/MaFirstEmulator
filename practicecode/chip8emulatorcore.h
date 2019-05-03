#include <iostream>
using namespace std;

unsigned short opcode;	   //Literally the opcode
unsigned char memory[4096]; //Total Memory

unsigned char V[16] //Registers

unsigned short I;  //Index register
unsigned short pc; //Program counter

unsigned char gfx[64*32];  //pinxels in screen (2048)

unsigned char delay_timer; //counts down to zero when not set to zero
unsigned char sound_timer; //The system’s buzzer sounds whenever the sound timer reaches zero.



unsigned char stack[16]; //used to remember program counter location before performing a jump
unsigned char sp;       //stack pointer


unsigned char keypad[16]; //sytem has 16 keys use this to keep state of keys






