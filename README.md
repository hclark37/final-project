Final project focused on creating a game using object-oriented programming and a custom linked list implementation.

Utilizes user input to decide between two choices given an event, then modifies 0-100 based player stats based on that input. When players reach a certain threshold with their stats, they lose the game; however, if they survive enough rounds without leaving the 0-100 stat bounds, they win. 

To compile, run: g++ main.cpp trail.cpp trail.h -o game

Usage: ./game sampleinput.txt

When presented with the home screen, the user has the option to either go to a settings page, which modifies some of the functionality of the game including frequency of certain events and other gameplay parameters, a play functionality, which starts the game, and an add event functionality, which allows players to add their own custom events to the game. 

To play the game, follow the onscreen instructions by typing 1 to go to the play section. To test other functionality of the game, use a different number. 
