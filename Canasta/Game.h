#pragma once

class Card;
class Deck;
class Hand;
class Player;
class Computer;
class Round;
class Human;


#include <iostream>
#include <vector>
#include "Hand.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "Round.h"
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>


class Game {
public: 
	Game();
	void main_menu();
	void choose_player_type();
	void main_game();
	~Game();
	Game(const Game& other_game);
	//virtual void play();
private: 
	std::vector<Player*> players;
	int round;
};

//we'll need to have this as out of class function so as to avoid dependancy on the Game class
//when we call this function in the round Class.
int validate_option_based_input(int lower_bound, int upper_bound);