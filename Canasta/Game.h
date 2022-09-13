#pragma once
#include <iostream>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include "Round.h"
#include <random>
#include <algorithm>
#include <iostream>

class Game {
public: 
	Game();
	void main_menu();
	void choose_player_type();
	//virtual void play();
private: 
	std::vector<Player*> players;
	int round;
};