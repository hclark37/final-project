#include "list.h"
#include <iostream>
#include <fstream>

using namespace std;

trail::trail() {

}

void trail::addNode(const int[] &, const int[] &, const string[] &) {

}

void trail::randomize() {

}

string trail::checkStatus(int[] stats &) {
	for (int i = 0;i < 4;i++) {
		if (stats[i] <= 0) {
			return deathMessages[i];
		} else if (stats[i] >= 100) {
			return deathMessages[i + 4];
		}
	}
	return "";
}

string trail::win(int[] &) {

}

Node::Node(const int[] &, const int[] &, const string[] &) {

}

string Node::getData() const {

}

string Node::choice(bool, int[] &) const {

}
