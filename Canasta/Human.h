#pragma once
#include "Player.h"
class Human : public Player {
public: 
	void play() ;
	bool draw(Deck draw_decks) ;
	void meld() ;
	void discard() ;
};