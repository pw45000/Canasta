#pragma once
#include "Player.h"
class Computer : public Player {
public: 
	void play(Deck& draw_decks) ;
	void discard() ;
	void meld() ;
	bool draw(Deck &draw_decks) override ;
	void print_player_type() override;
private:
	int please;
};