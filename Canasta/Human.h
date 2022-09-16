#pragma once
#include "Player.h"
class Human : public Player {
public: 
	void play(Deck& draw_decks) override ;
	bool draw(Deck &draw_decks) override;
	void meld() ;
	void discard();
	void print_player_type() override;
};