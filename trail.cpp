#include "trail.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

trail::trail() : first(NULL) { 
	ifstream fin("input.txt");
	
	string outputs[3];
	int choices1[4];
	int choices2[4];
	
	while(getline(fin, line)) {
		outputs[0] = line;
		getline(fin, line);
		outputs[1] = line;
		getline(fin, line);
		outputs[2] = line;
		for (int i = 0; i < 4; i++) {
			getline(fin, line);
			choices1[i] = stoi(line);
		}
		for (int i = 0; i < 4; i++) {
			getline(fin, line);
			choices2[i] = stoi(line);
		}
		addNode(choices1, choices2, outputs);
	}
	
}

void trail::addNode(const int &choice1[], const int &choice2[], const string &outputs[]) {
	Node *new_node = newNode(choices1, choices2, outputs); 
	new_node->next = first;  
	first = new_node;
}

Node *trail::newNode(const int &choice1[], const int &choice2[], const string &outputs[]) {
	return new Node(choices1, choices2, outputs);
}
void trail::randomize() { //reorder all the nodes 
	vector<*Node> nodes; //original ordered list of nodes 
	vector<*Node> new_nodes; //reordered, random node vector 
	Node *node = first;
	while (node->next != NULL) {  //while you're not at the end of the list 
		nodes.push_back(node); //add node to new list 
		node = node->next; //go to next 
	}
	while (nodes.size() != 0) { //while there is still stuff left in nodes 
		int random = nodes[rand() % nodes.size()]; //get random between start and end of the nodes[] vector 
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
}
string trail::checkStatus(int[] stats &) {
	turnCounter++;
	for (int i = 0;i < 4;i++) {
		if (stats[i] <= 0) {
			return deathMessages[i];
		} else if (stats[i] >= 100) {
			return deathMessages[i + 4];
		}
	}
	if (turnCounter == 20) {
		return win(stats);
	}
	return "";
}

string trail::win(int[] &) {
	int finalscore = 0;
	string finale;
	for (int i = 0;i < 4;i++) {
		finalscore += int[i];
	}
	if (finalscore >= 300) {
		finale += "You are thriving.\n Final score: ";
		finale += finalscore;
	} else if (finalscore >= 200) {
		finale += "You are made it to your destination with little problem.\n Final score: ";
		finale += finalscore;
	} else if (finalscore >= 100) {
		finale += "You are hurting a bit from the long journey. \n Final score: ";
		finale += finalscore;
	} else {
		finale += "You made it... somehow...\n Final score: ";
		finale += finalscore;
	}
	return finale;
}

Node::Node(const int[] &, const int[] &, const string[] &) {
	
}

string Node::getData() const {
	return strings[0];
}

string Node::choice(bool decision, int[] stats &) const {
	int event = 1 + (int)decision; // finds which decision is made

	// Adds the choice stats to player stats
	if (event == 1) {
		for (int i = 0;i < 4;i++) {
			stats[i] += choices1[i];
		}
    	} else {
        	for (int i = 0;i < 4;i++) {
            	stats[i] += choices2[i];
        	}
    	}

	// Returns outcome string of choice
	return strings[event];
}
