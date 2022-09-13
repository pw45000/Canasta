#pragma once
#include "Deck.h"
#include "Card.h"
#include "Hand.h"
class Player {

public:
	Player();
	//virtual void play();
	//virtual void strategy();
	//virtual void draw();
	//virtual void meld();
	//virtual void discard();
private:
	int score;
	bool has_canasta;
	bool hand_empty;
	Hand player_hand;
};