#include <iostream>
using namespace std;

class chip8{
	
	private:
		unsigned short opcode;	   //Literally the opcode
		unsigned char memory[4096]; //Total Memory

		unsigned char V[16]; //Registers

		unsigned short I;  //Index register
		unsigned short pc; //Program counter

		unsigned char gfx[64*32];  //pixels in screen (2048)

		unsigned char delay_timer; //counts down to zero when not set to zero
		unsigned char sound_timer; //The system’s buzzer sounds whenever the sound timer reaches zero.


		unsigned char stack[16]; //used to remember program counter location before performing a jump
		unsigned char sp;       //stack pointer

		unsigned char drawflag;


	public:

		chip8(){

		}

		void initialize(){
			// Initialize registers and memory once
			pc = 0x200; //program counter
			opcode = 0;//reset current opcode
			I = 0; //reset index register
			sp = 0; //reset stack pointer

			//clear display
			for(int i = 0; i<16;i++){  //clear stack
				stack[i]=0;
			}
			
			for(int i = 0; i<16;i++){  // Clear registers V0-VF
				V[i]=0;
			}

			for (int i = 0; i<80;i++){//load fontset (guys says it starts at 0x80 onwards 
				memory[i]=chip8_fontset[i];//but it seems more backwards)
			}

			for(int i - 0; i<bufferSize;){ //load program (game) into memory 
				memory[512+i] = buffer[i]; //starts at location 0x200 == 512
			}



		}

		void loadgame(){

		}

		void setkeys(){

		}

		void emulateCycle(){

			// Fetch Opcode  (we do this cause opcode is 2 bytes length)
			opcode =  memory[pc] << 8 |  memory[pc+1];
  			
  			// Decode Opcode
			switch(opcode & 0xF000){ 
				//sum cases

// 0NNN	Call		Calls RCA 1802 program at address NNN. Not necessary for most ROMs.
// 00E0	Display	disp_clear()	Clears the screen.
// 00EE	Flow	return;	Returns from a subroutine.
			case 0X1000:// 1NNN	Flow	goto NNN;	Jumps to address NNN.
				pc = opcode & 0FFF;


			case 0x2000: // 2NNN Flow Calls subroutine at NNN.
				
				stack[sp] =pc;
				sp++;  

				pc = opcode & 0x0FFF;
				break;

// 3XNN	Cond	if(Vx==NN)	Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
// 4XNN	Cond	if(Vx!=NN)	Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)
// 5XY0	Cond	if(Vx==Vy)	Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block)
// 6XNN	Const	Vx = NN	Sets VX to NN.
// 7XNN	Const	Vx += NN	Adds NN to VX. (Carry flag is not changed)
// 8XY0	Assign	Vx=Vy	Sets VX to the value of VY.
// 8XY1	BitOp	Vx=Vx|Vy	Sets VX to VX or VY. (Bitwise OR operation)
// 8XY2	BitOp	Vx=Vx&Vy	Sets VX to VX and VY. (Bitwise AND operation)
// 8XY3	BitOp	Vx=Vx^Vy	Sets VX to VX xor VY.
// 8XY4	Math	Vx += Vy	Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't.
// 8XY5	Math	Vx -= Vy	VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
// 8XY6	BitOp	Vx>>=1	Stores the least significant bit of VX in VF and then shifts VX to the right by 1.[2]
// 8XY7	Math	Vx=Vy-Vx	Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
// 8XYE	BitOp	Vx<<=1	Stores the most significant bit of VX in VF and then shifts VX to the left by 1.[3]
//9XY0	Cond	if(Vx!=Vy)	Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block)





				case 0xA000:  // ANNN: Sets I to the address NNN
					// Execute Opcode
 					I = opcode & 0x0FFF;
					pc += 2;
					break;

				//sum more cases

				// BNNN	Flow	PC=V0+NNN	Jumps to the address NNN plus V0.
				case 0xB000:
				pc = (opcode & 0x0FFF) +V[0];
				break;
// CXNN	Rand	Vx=rand()&NN	Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
// DXYN	Disp	draw(Vx,Vy,N)	Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
// EX9E	KeyOp	if(key()==Vx)	Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
// EXA1	KeyOp	if(key()!=Vx)	Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
// FX07	Timer	Vx = get_delay()	Sets VX to the value of the delay timer.
// FX0A	KeyOp	Vx = get_key()	A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
// FX15	Timer	delay_timer(Vx)	Sets the delay timer to VX.
// FX18	Sound	sound_timer(Vx)	Sets the sound timer to VX.
// FX1E	MEM	I +=Vx	Adds VX to I.[4]
// FX29	MEM	I=sprite_addr[Vx]	Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
// FX33	BCD	set_BCD(Vx);
// *(I+0)=BCD(3);

// *(I+1)=BCD(2);

// *(I+2)=BCD(1);

// Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)
// FX55	MEM	reg_dump(Vx,&I)	Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
// FX65	MEM	reg_load(Vx,&I)	Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.





				default:
      				printf ("Unknown opcode: 0x%X\n", opcode);
			}

			//chack against table we will probably have to implement this
			//in this cas ANNN mieans set the I address to NNN

  			

  			// Update timers

		}



};