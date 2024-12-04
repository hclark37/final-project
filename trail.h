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
	// Private variables are the events and choices at each node and next points to the next node
	private:
		string strings[3];
		int choice1[4];
		int choice2[4];
		Node *next;
};

class trail {
 public:
	trail(string);  // Sets up the linked list and initial variables of the class
	void addNode(const int*, const int*, const string*); // Adds nodes to the linked list
	void randomize(); //store pointers in vector, shuffle vector, change pointers in nodes
	string checkStatus(int*); //checks for death; checkStatus == "" means survival
	string win(int*); // If the players go through all the turns, then this happens
	void Play(int*); // Main function to play the game
	string choice(bool, int*); // This selects the stats used to add to total stats
	void shop(int*); // A quick interjection to help the player out
	void titleScreen(int*); // Main screen that goes to play, add evnets, settings and to quit
	void Add(int*); // Add event to file
	void settings(int*); // Can change turn total and shop frequency here
	
 private:
	Node *newNode(const int* choice1, const int* choice2, const string* outputs);
	Node *first;
	Node *current;
	string fileName; // help pass the file
	int turnCounter; // Count until it hits the turn total
	int totalTurns; // total turns
	int shopFrequency;
	string deathMessages[8] = {"You became too poor and couldn't pay for basic survival needs.", "You became rich enough that you were robbed.", "You starved.", "You ate too much.", "You were too ill to carry on.", "Your body over stimulated itself.", "Being too paranoid, you drove yourself into insanity.", "Being too relaxed, you were jumped."}; // Death messages
    	string endings[4] = {"You came out better off after your journey!!", "You benefited from this journey!", "You struggled a little but complete your journey.", "You barely came out of this journey alive but survived."}; // Winning endings
};


#endif
