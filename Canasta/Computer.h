#pragma once
#include "Player.h"
class Computer : public Player {
public: 
	void play() ;
	void discard() ;
	void meld() ;
	bool draw(Deck draw_decks) ;
private:
	int please;
};