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
	trail(string);  
	void addNode(const int*, const int*, const string*);
	void randomize(); //store pointers in vector, shuffle vector, change pointers in nodes
	string checkStatus(int*); //checks for death; checkStatus == "" means survival
	string win(int*);
	void Play(int*);
	string choice(bool, int*);
	void shop(int*);
	void titleScreen(int*);
	void Add(int*);
	void settings(int*);
	
 private:
	Node *newNode(const int* choice1, const int* choice2, const string* outputs);
	Node *first;
	Node *current;
	string fileName;
	int turnCounter;
	int totalTurns;
	int shopFrequency;
	string deathMessages[8] = {"You became too poor and couldn't pay for basic survival needs.", "You became rich enough that you were robbed.", "You starved.", "You ate too much.", "You were too ill to carry on.", "Your body over stimulated itself.", "Being too paranoid, you drove yourself into insanity.", "Being too relaxed, you were jumped."};
    string endings[4] = {"You came out better off after your journey!!", "You benefited from this journey!", "You struggled a little but complete your journey.", "You barely came out of this journey alive but survived."};
};


#endif
