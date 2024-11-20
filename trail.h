#ifndef TRAIL_H
#define TRAIL_H

class Node {

	friend class trail;

	public:
		Node(const int &);     
		string getData() const;
		string choice(bool) const; //return strings[1 + (int)bool]
	private:
		string strings[3];
		int choice1[4];
		int choice2[4];
		Node *next;
};

class trail {
 public:
	trail();   
	void randomize(); //store pointers in vector, shuffle vector, change pointers in nodes
	string checkStatus(int[] &); //checks for death; checkStatus == "" means death
	string win(int[] &);
 private:
	Node *newNode(const int &); 
	Node *first;
	Node *current;
	int turnCounter;
	string deathMessages[8];
	string endings[4];
};


#endif
