#include "trail.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

trail::trail(string filename) : first(NULL) { 

	ifstream fin(filename);
	//add error checking
	string line;
	string outputs[3];
	int choice1[4];
	int choice2[4];
	
	while(getline(fin, line)) {
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
		addNode(choice1, choice2, outputs);
	}
	randomize();

	turnCounter = 0;
}

void trail::addNode(const int* choice1, const int* choice2, const string* outputs) {
	Node *new_node = newNode(choice1, choice2, outputs); 
	new_node->next = first;  
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
	turnCounter++;
	/*for (int i = 0; i < 4; i++) {
		cout << stats[i] << " ";
	}*/
	// cout << stats[0] << " " << stats[1] << " " << stats[2] << " " << stats[3] << endl;
	// for debugging 
	for (int i = 0; i < 4; ++i) {
		if (stats[i] <= 0) {
			return deathMessages[2 * i];
		} 
		if (stats[i] >= 100) {
			return deathMessages[(2 * i) + 1];
		}
	}
	if (turnCounter == 20) {
		return win(stats);
	}
	
	return "";
}

string trail::win(int* stats) {
    int finalscore = 0;
    string finale;
    for (int i = 0;i < 4;i++) {
        finalscore += (int)stats[i];
    }

    cout << endl << "Final score: " << finalscore;

    if (finalscore >= 300) {
        return endings[0];
    } else if (finalscore >= 200) {
        return endings[1];
    } else if (finalscore >= 100) {
        return endings[2];
    } else {
        return endings[3];
    }
}

void trail::Play(int* stats) {
	system("clear");
   	bool decision;
   	current = first;
	string resolution = "";
	int value;
	string previousOutput = "";
    while (resolution == "") {
		cout << endl << endl << endl << endl << endl;
		cout << "Your stats" << endl;
		cout << "Money: " << stats[0] << endl;
		cout << "Food:   " << stats[1] << endl;
		cout << "Health: " << stats[2] << endl;
		cout << "Sanity: " << stats[3] << endl << endl;
		if (previousOutput != "") {
			cout << previousOutput << endl << endl;
		}
      	cout << current->getData() << endl;
		cout << "Enter 1 for choice 1 and 2 for choice 2: ";     
		while (cin >> value) {
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
		previousOutput = choice(decision, stats);
		
		resolution = checkStatus(stats); 
		/*for (int i = 0; i < 4; i++) { 
			cout << stats[i] << " ";
		}*/
		cout << endl;

		if (resolution != "") {
			system("clear");
			cout << endl << endl << endl << endl << endl;
			cout << "Your stats" << endl;
			cout << "Health: " << stats[0] << endl;
			cout << "Food:   " << stats[1] << endl;
			cout << "Health: " << stats[2] << endl;
			cout << "Sanity: " << stats[3] << endl << endl << endl;
			cout << previousOutput << endl << endl;
			cout << resolution << endl;
			break;
		}
		
		cout << resolution;
		
		//add fix for if no next node 
		if (current->next == NULL) {
			randomize(); //part that breaks 
		}
		system("clear");
	}
	for (int i = 0; i < 4; i++) {
		stats[i] = 50;
	}
	
	cout << endl << "Would you like to continue? (yes/no): ";
	while (cin >> resolution) {
		if (resolution == "no") {
			break;
		}
		if (resolution == "yes") {
			randomize();
			Play(stats);
			return;
		}
	}
	randomize();
	titleScreen(stats);
	return;
}

Node::Node(const int* choice1, const int* choice2, const string* events) {
	for (int i = 0; i < 3; ++i) {
		strings[i] = events[i]; 
    }
    for (int i = 0; i < 4; ++i) {
        this->choice1[i] = choice1[i];
        this->choice2[i] = choice2[i];
    }
    next = NULL; 
}

string Node::getData() const {
	return strings[0];
}

string trail::choice(bool decision, int* stats) {
	string outcome;
	outcome = current->choice(decision, stats);
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
	
	
	
}

void trail::titleScreen(int* stats) {
	int value;
	system("clear");
	cout << endl << endl << endl << endl << endl << "Parker and Harrison's Game" << endl << endl << endl << "1. Play" << endl << "2. Add Events" << endl << "3. Quit" << endl << endl << endl << "Enter your choice: ";
	while (cin >> value) {
		switch(value) {
			case 1:
				Play(stats);
				return;
			case 2:
				
				break;
						
		}
		if (value == 3) {
			return;
		}
		
	}
	return;
	
}
