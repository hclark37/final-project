#include "trail.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void trail::addNode(const int &choice1[], const int &choice2[], const string &outputs[]) {
	Node *new_node = newNode(choices1, choices2, outputs); 
	new_node->next = first;  
	first = new_node;
}

Node *trail::newNode(const int &choice1[], const int &choice2[], const string &outputs[]) {
	return new Node(choices1, choices2, outputs);
}

void trail::addNode(const int &choice1[], const int &choice2[], const string &outputs[]) {
	Node *new_node = newNode(choices1, choices2, outputs); 
	new_node->next = first;  
	first = new_node;
}

Node *trail::newNode(const int &choice1[], const int &choice2[], const string &outputs[]) {
	return new Node(choices1, choices2, outputs);
}
void trail::randomize() {

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

}

string Node::choice(bool, int[] &) const {

}
