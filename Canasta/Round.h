#pragma once
#include "Game.h"
#include "Deck.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"
class Round {
public: 
	Round();
	Round(Human player1, Human player2);
	Round(Human player1, Computer player2);
	Round(std::vector<Player*> players);
	Round(const Round& other_round);
	~Round(); 
	int coin_toss();
	void main_round();
	void initial_draw();

private: 
	Deck stock_and_discard;
	int player_1_score;
	int player_2_score;
	std::string next_player;
	std::vector<Player*> players;
};