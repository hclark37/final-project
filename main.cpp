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
	
	int stats[] = {50, 50, 50, 50};
	string inputFile = argv[1];
	
	trail theTrail(inputFile);

    	theTrail.titleScreen(stats);

	return 0;
}
