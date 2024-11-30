#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <string>

#ifndef TRAIL_H
#define TRAIL_H

using namespace std;

class Node {

	friend class trail;

	public:
		Node(const int*, const int*, const string*);     
		string getData() const; // gets event occurring
		string choice(bool, int*); //changes stats and returns choice event
	private:
		string strings[3];
		int choice1[4];
		int choice2[4];
		Node *next;
};

class trail {
 public:
	trail();  
	void addNode(const int*, const int*, const string*);
	void randomize(); //store pointers in vector, shuffle vector, change pointers in nodes
	string checkStatus(int*); //checks for death; checkStatus == "" means survival
	string win(int*);
	void Play(int* stats);
	string choice(bool, int*);
 private:
	Node *newNode(const int* choice1, const int* choice2, const string* outputs);
	Node *first;
	Node *current;
	int turnCounter;
	string deathMessages[9] = {"test", "test2", "test3", "test4", "test5", "test6", "test7", "test8", "test9"};
	string endings[4] = {"1test", "2test", "3test", "4test"};
};


#endif
