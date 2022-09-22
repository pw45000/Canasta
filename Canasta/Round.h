#pragma once

class Player;
class Computer; 
class Human;
class Deck;
class Card; 
class Hand;
class Game;

#include "Game.h"






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
	void sort_players_hands();
	int pre_turn_menu();
	void tally_score(); 
	void set_round_number(int round_number);


	bool load_game();
	bool load_round_number(std::string round_string);
	bool load_player(std::string player_string);
	bool load_player_score(int player, std::string round_string);
	bool string_is_card(std::string card_string);
	bool load_hand(int player, std::string hand_string);
	bool load_meld(int player, std::string meld_string);

private: 
	Deck stock_and_discard;
	int round_number;
	int player_1_score;
	int player_2_score;
	int next_player;
	std::vector<Player*> players;
};

