#include <iostream>
#include <fstream>
#include "trail.h"

using namespace std;

int main(int argc,char* argv[]) {
	if (argc != 2) {
		cerr << "Usage ./trail input.txt" << endl;
		return 1;
	}
	
	int stats[4] = {50, 50, 50, 50};

	trail theTrail;

    	theTrail.Play(stats);

	return 0;
}
