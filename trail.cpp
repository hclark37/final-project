#include "trail.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

trail::trail(string filename) : first(NULL) { 
	fileName = filename; //save the file name to be used in other parts like add() 
	ifstream fin(fileName);
	//add error checking
	string line;
	string outputs[3]; //parts of each node to fill 
	int choice1[4];
	int choice2[4];

	while(getline(fin, line)) { //continuously read from file
		outputs[0] = line;
		getline(fin, line);
		outputs[1] = line;
		getline(fin, line); 
		outputs[2] = line;
		for (int i = 0; i < 4; i++) {
			getline(fin, line);
			choice1[i] = stoi(line);
		}
		for (int i = 0; i < 4; i++) {
			getline(fin, line);
			choice2[i] = stoi(line);
		}
		addNode(choice1, choice2, outputs); //add a node to create linked list from file on run 
	}
	randomize(); //randomize node order 

	totalTurns = 20; //initial turn count, stats
	shopFrequency = 7;
	turnCounter = 0;

	fin.close();
}

void trail::addNode(const int* choice1, const int* choice2, const string* outputs) {
	Node *new_node = newNode(choice1, choice2, outputs);  
	new_node->next = first;  //push new node to front 
	first = new_node;
}

Node *trail::newNode(const int* choice1, const int* choice2, const string* outputs) {
	return new Node(choice1, choice2, outputs); 
}

void trail::randomize() { //reorder all the nodes 
	vector<Node*> nodes; //original ordered list of nodes 
	vector<Node*> new_nodes; //reordered, random node vector 
	Node *node = first;
	while (node != NULL) {  //while you're not at the end of the list 
		nodes.push_back(node); //add node to new list 
		node = node->next; //go to next 
	}
	srand((unsigned)time(NULL));
	while (nodes.size() != 0) { //while there is still stuff left in nodes 
		int random = rand() % nodes.size(); //get random between start and end of the nodes[] vector 
		new_nodes.push_back(nodes[random]); //add that node you grabbed to new_nodes 
		nodes.erase(nodes.begin() + random); //remove that node, thereby decreasing the nodes.size() 
	}
	for (int i = 0; i < new_nodes.size(); i++) { //reorder the list 
		if (i == (new_nodes.size() - 1)) { //if it's the end node, make it go to null at end 
			new_nodes[i]->next = NULL;
		} else {
			new_nodes[i]->next = new_nodes[i+1];
		}
	}
	first = new_nodes[0]; //make new first node 
	current = first;
}

string trail::checkStatus(int* stats) {
	turnCounter++; //increment turn counter for when player is suppoed to win 
	/*for (int i = 0; i < 4; i++) {
	  cout << stats[i] << " ";
	  }*/
	// cout << stats[0] << " " << stats[1] << " " << stats[2] << " " << stats[3] << endl;
	// for debugging 
	for (int i = 0; i < 4; ++i) {
		if (stats[i] <= 0) { //if any individual stat is less than 0 means loss 
			return deathMessages[2 * i];
		} 
		if (stats[i] >= 100) { //if greater than 100 means loss
			return deathMessages[(2 * i) + 1];
		}
	}
	if (turnCounter == totalTurns) { //win if get to end without losing
		return win(stats);
	}

	return "";
}

string trail::win(int* stats) {
	int finalscore = 0; 
	string finale; 
	for (int i = 0;i < 4;i++) { //add score sum 
		finalscore += (int)stats[i];
	}

	finale += "Final score: "; // build score string 
	finale += to_string(finalscore);
	finale += "\n";

	if (finalscore >= 300) { //score conditions for each one. 0 is best, 4 is worst 
		finale += endings[0];
	} else if (finalscore >= 200) {
		finale += endings[1];
	} else if (finalscore >= 100) {
		finale += endings[2];
	} else {
		finale += endings[3];
	}
	return finale; 
}

void trail::Play(int* stats) {
	system("clear"); //clear screen 
	bool decision;
	current = first;
	string resolution = "";
	int value;
	string previousOutput = "";
	while (resolution == "") { //statement to print the output necessary for new question-- only if you haven't lost or won.
		cout << endl << endl << endl << endl << endl; //formatting 
		cout << "Your stats" << endl; 
		cout << "Money: " << stats[0] << endl;
		cout << "Food:   " << stats[1] << endl;
		cout << "Health: " << stats[2] << endl;
		cout << "Sanity: " << stats[3] << endl << endl;
		if (previousOutput != "") {
			cout << previousOutput << endl << endl;
		}
		cout << current->getData() << endl; //prints the event 
		cout << "Enter 1 for choice 1 and 2 for choice 2: ";     
		while (cin >> value) { //error check input
			if (value == 1) {
				break;
			} else if (value == 2) {
				break;
			}
			cout << "Please enter a valid choice: ";
		}

		if (value == 1) {
			decision = false;
		} else if (value == 2) {
			decision = true;
		}
		
		previousOutput = choice(decision, stats); //save the next choice outcome. choice also modifies stats[]	
		resolution = checkStatus(stats);  //checks to see if you win or lose- will not be "" if you did. 

		if (resolution != "") { //print this if you lose.
			system("clear");
			cout << endl << endl << endl << endl << endl;
			cout << "Your stats" << endl;
			cout << "Money: " << stats[0] << endl;
			cout << "Food:   " << stats[1] << endl;
			cout << "Health: " << stats[2] << endl;
			cout << "Sanity: " << stats[3] << endl << endl << endl;
			cout << previousOutput << endl << endl;
			cout << resolution << endl;
			break;
		}

		if ((shopFrequency - 1) == (turnCounter % shopFrequency)) { //random shop chance 
			shop(stats); //call shop function, once exited, print like normal. 
			resolution = checkStatus(stats);
			if (resolution != "") {
				system("clear");
				cout << endl << endl << endl << endl << endl;
				cout << "Your stats" << endl;
				cout << "Money: " << stats[0] << endl;
				cout << "Food:   " << stats[1] << endl;
				cout << "Health: " << stats[2] << endl;
				cout << "Sanity: " << stats[3] << endl << endl << endl;
				cout << previousOutput << endl << endl;
				cout << resolution << endl;
				break;
			}
		}

		//add fix for if no next node 
		if (current->next == NULL) {
			randomize(); //part that breaks 
		}
		system("clear");
	}
	for (int i = 0; i < 4; i++) { //when the game is over, reset stats
		stats[i] = 50;
	}
	turnCounter = 0; 
	randomize(); //re-randomize order of nodes

	cout << endl << "Would you like to continue? (yes/no): ";
	while (cin >> resolution) {
		if (resolution == "yes") {
			Play(stats);
			return;
		} else if (resolution == "no") {
			break;
		}
	}
	titleScreen(stats); //call this again so that it reshows the beginning. if you just returned, it'd only go into the while loop, not printing the title screen
	return;
}

Node::Node(const int* choice1, const int* choice2, const string* events) {
	for (int i = 0; i < 3; ++i) {
		strings[i] = events[i]; 
	}
	for (int i = 0; i < 4; ++i) { //set data of node 
		this->choice1[i] = choice1[i]; 
		this->choice2[i] = choice2[i];
	}
	next = NULL; //
}

string Node::getData() const {
	return strings[0]; //so that you can get this private data from the function 
}

string trail::choice(bool decision, int* stats) {
	string outcome;
	outcome = current->choice(decision, stats); //information to return as string - calls node version of choice
	current = current->next; // changes the current Node to the next one
	return outcome;
}

string Node::choice(bool decision, int* stats) {
	// Adds the choice stats to player stats
	if (decision) {
		for (int i = 0; i < 4; i++) {
			stats[i] += choice2[i];
		}
	} else {
		for (int i = 0; i < 4; i++) {
			stats[i] += choice1[i];
		}
	}

	return strings[(int)decision + 1]; // outputs the event choice
}

void trail::shop(int* stats) {
	int value;

	system("clear");
	cout << endl << endl << endl << endl << endl;
	cout << "Your stats" << endl;
	cout << "Money:  " << stats[0] << endl;
	cout << "Food:   " << stats[1] << endl;
	cout << "Health: " << stats[2] << endl;
	cout << "Sanity: " << stats[3] << endl << endl << endl;

	cout << "Would you like to buy anything from the Dawes & Clark Shop?: " << endl;
	cout << "1. A Pristine CFA Sandwich" << endl;
	cout << "2. A Cinderella Band-Aid" << endl;
	cout << "3. A Fidget Spinner" << endl;
	cout << "4. Save your money" << endl << endl;

	while (true) {
		cout << "Enter your choice (1-4): ";
		cin >> value;
		if (!cin.fail()) break;
	}

	while (true) { // stat changes based on decision in shop. 
		switch(value) {
			case 1:
				stats[0] -= 10;
				stats[1] += 15;
				break;
			case 2:
				stats[0] -= 10;
				stats[2] += 15;
				break;
			case 3:
				stats[0] -= 10;
				stats[3] += 15;
				break;
			case 4:
				stats[0] += 5;
		}
		if (value >= 1 && value <= 4) {
			return;
		}
		cout << "Please enter a valid choice (1-4): ";
		cin >> value;
	}
}

void trail::titleScreen(int* stats) {
	int value;
	system("clear"); //clear screen to show blank 
	cout << "\n\n\n\n\nParker and Harrison's Game\n\n\n1. Play\n2. Add Events\n3. Settings\n4. Quit\n\n\nEnter your choice (1-4): ";
	while (cin >> value) { 
		switch(value) {
			case 1:
				Play(stats);
				return; //return here since every function, at its end, calls titlescreen again. when the final quit is done, every past function will recursively return 
			case 2:
				Add(stats);
				return;
			case 3:
				settings(stats);
				return;
			case 4:
				return;
		}
		cout << "Please insert a valid choice (1-4): ";
	}
}

void trail::settings(int* stats) {
	int value;
	bool title = false, continuing = true;
	system("clear");
	cout << "\n\n\n\n\nSettings";
	cout << "\n\n\n1. Total Turns\n2. Shop Frequency\n3. Exit Settings";
	cout << "\n\n\nEnter your choice (1-3): ";
	while (continuing) { 
		cin >> value;
		switch (value) {
			case 1:
				system("clear");
				cout << "\n\n\n\n\nTotal Turns";
				cout << "\n\n\n10 Turns\n20 Turns\n30 Turns";
				cout << "\n\n\nEnter your choice (10, 20, or 30): ";
				while (true) { 
					cin >> value;
					if (value == 10 || value == 20 || value == 30) {
						totalTurns = value; //set trial class total turns to value desired 
						continuing = false; //set break condition (to let you exit from settings)
						break;
					}
					cout << "Please insert a valid choice: ";
				}
				break;
			case 2:
				system("clear");
				cout << "\n\n\n\n\nShop Frequency";
				cout << "\n\n\n1. Never\n2. Rarely\n3. Often";
				cout << "\n\n\nEnter your choice (1-3): ";
				while (true) {
					cin >> value;
					switch (value) { //switch to let you choose your change, then exit settings condition set
						case 1:
							shopFrequency = 100;
							continuing = false;
							break;
						case 2:
							shopFrequency = 11;
							continuing = false;
							break;
						case 3:
							shopFrequency = 7;
							continuing = false;
					}
					if (value < 1 || value > 3) { //error check input
						cout << "Please insert a valid choice: ";
					} else break;
				}
				break;
			case 3: //continue if not a valid choice
				title = true;
				continuing = false;
		}
	}
	if (title) {
		titleScreen(stats); //if you choose to exit 
	} else settings(stats); //else, recurr 
}

void trail::Add(int* stats) {
	string choice, line;
	int number;
	ofstream output(fileName, std::ios::app); //std::ios::app lets you append to a file. 
	
	system("clear");
	//repeatedly take a line of input, then append to file 
	cin.ignore();
	cout << "Event output (string): ";
	getline(cin, line);
	output << line << endl;
	cout << "Choice 1 output (string): ";
	getline(cin, line);
	output << line << endl;
	cout << "Choice 2 output (string): ";
	getline(cin, line);
	output << line << endl;
	cout << "Choice 1 stats (integers)" << endl;
	cout << "Money:  ";
	cin >> number;
	output << number << endl;
	cout << "Food:   ";
	cin >> number;
	output << number << endl;
	cout << "Health: ";
	cin >> number;
	output << number << endl;
	cout << "Sanity: ";
	cin >> number;
	output << number << endl;
	cout << "Choice 2 stats (integers)" << endl;
	cout << "Money:  ";
	cin >> number;
	output << number << endl;
	cout << "Food:   ";
	cin >> number;
	output << number << endl;
	cout << "Health: ";
	cin >> number;
	output << number << endl;
	cout << "Sanity: ";
	cin >> number;
	output << number << endl;
	cout << "Would you like to add another? ";
	//fout close 
	output.close();

	while (cin >> choice) {
		if (choice == "yes") {
			Add(stats);
			return;
		} else if (choice == "no") {
			//goes back to title screen- when the final return happens, they all will return at the same time 
			titleScreen(stats);
			return;
		} else {
			cout << "Please enter a valid choice (yes or no): ";
		}
	}
}
