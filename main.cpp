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
