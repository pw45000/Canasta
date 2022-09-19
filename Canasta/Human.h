#pragma once
class Human;
class Player;
#include "Player.h"



class Human : public Player {
public: 
	void play(Deck& draw_decks) override ;
	bool draw(Deck &draw_decks) override;
	void meld() override;
	void discard();
	void print_player_type() override;

	std::vector<Card> validate_comma_input();
};