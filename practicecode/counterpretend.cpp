#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;


int main(){
	
	//implement timer counter
	//This will count down a given (by user)number  every second 

	int number = 600;

	while(number>=0){

		cout<<number<<endl;
		number--;
		usleep(16666);
	}

	return 0;
}