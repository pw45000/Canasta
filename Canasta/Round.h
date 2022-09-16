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
	Round(std::vector<Player*> players, int round_number);
	Round(const Round& other_round);
	~Round(); 
	int coin_toss();
	void main_round();
	void initial_draw();
	int get_next_player() const;
	void set_next_player(int next_player);
	void output_round_info();

private: 
	Deck stock_and_discard;
	int round_number;
	int player_1_score;
	int player_2_score;
	int next_player;
	std::vector<Player*> players;
};