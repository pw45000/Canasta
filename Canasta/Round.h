#pragma once
#include "Game.h"
#include "Deck.h"
#include "Player.h"
class Round {
public: 
	Round();
	Round(Human player1, Human player2);
	Round(Human player1, Computer player2);
	Round(const Round& other_round);
	~Round(); 
	void save();
	void take_turn();
	void ask_for_help();
	void quit();
	int coin_toss();
private: 
	Deck stock_and_discard;
	int player_1_score;
	int player_2_score;
	std::string next_player;
	std::vector<Player*> players;
};