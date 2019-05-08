#include <iostream>
using namespace std;


int main(){

	unsigned short opcode = 0x56FA;
	
	cout<<"opcode is supposed to be 56FA" <<endl;
	cout<<"opcode is: "<<endl;
	printf("%04X \n", opcode);

	cout<<"and operation second digit:"<<endl;
	unsigned short X = opcode & 0x0F00;
	printf("%04X \n", X);
	
	cout<<"now shifting"<<endl;
	char XX = X >> 8;

	cout<< "X is supposed to be 6"<<endl;
	cout<<"X is"<<endl;
	printf("%02X \n", XX); 
		
	cout<<"now lets cut a short to a char"<<endl;
	
	//unsigned short tempshort  = (opcode & 0x00FF)<<8 ;
	unsigned char machar = opcode;
	
//	printf("%04X \n",tempshort);
	printf("%02X \n", machar);

	return 0;

}
