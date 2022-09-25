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
	void main_round(bool has_loaded_file);
	void initial_draw();
	int get_next_player() const;
	void set_next_player(int next_player);
	void output_round_info();
	void sort_players_hands();
	int pre_turn_menu();
	void tally_score(); 
	void set_round_number(int round_number);
	std::vector<Player*> get_players();

	bool load_game();
	bool load_round_number(std::string round_string);
	bool load_player(std::string player_string);
	bool load_player_score(int player, std::string round_string);
	bool string_is_card(std::string card_string);
	bool load_hand(int player, std::string hand_string);
	bool load_meld(int player, std::string meld_string);
	bool load_stock(std::string stock_string);
	bool load_discard(std::string discard_string);
	bool load_next_player(std::string next_plr_string);

	void set_stock_pile(std::vector<Card> stock_pile);
	void set_discard_pile(std::vector<Card> discard_pile);

	void save_round();


private: 
	Deck stock_and_discard;
	int round_number;
	int next_player;
	std::vector<Player*> players;
};

