#pragma once
#include "Game.h"
#include "Deck.h"
class Round {
public: 
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
};