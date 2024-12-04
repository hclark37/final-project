//Harrison Clark, Parker Dawes
//CS202 Final 
//The data structure included in our project is a custom linked list implementation. It uses a set of nodes that store multiple different data types, and it utilizes object-oriented programming to create a lot of separate functions that exist under a class of the overarching list. 

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include "trail.h"

using namespace std;

int main(int argc,char* argv[]) {
	if (argc != 2) {
		cerr << "Usage ./trail input.txt" << endl;
		return 1;
	}
	
	int stats[] = {50, 50, 50, 50}; //create initial stat file s 
	string inputFile = argv[1]; //save iput
	
	trail theTrail(inputFile); //declare a new trail object 

    	theTrail.titleScreen(stats); //call title screen function 

	return 0;
	
}
