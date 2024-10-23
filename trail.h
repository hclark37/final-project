#ifndef TRAIL_H
#define TRAIL_H

class Node {

	friend class trail;

	public:
		Node(const int[] &, const int[] &, const string[] &); 
		string getData() const;
		string choice(bool choice, int[] &) const; //return strings[1 + (int)bool]
	private:
		string strings[3];
		int choice1[4];
		int choice2[4];
		Node *next;
};

class trail {
 public:
	list();
	void addNode(const int[] &, const int[] &, const string[] &);
	void randomize(); //store pointers in vector, shuffle vector, change pointers in nodes
	string checkStatus(int[] &); //checks for death; checkStatus == "" means death
	string win(int[] &);
 private:
	
	Node *newNode(const int[] &, const int[] &, const string[] &); 
	Node *first;
	Node *current;
	string deathMessages[8];
	string endings[4];
};


#endif
