#pragma once
#include "Deck.h"
#include "Card.h"
#include "Hand.h"
class Player {

public:
	Player();
	int get_score();
	bool has_canasta();
	bool hand_empty();
	void add_to_hand(Card card_to_be_added);
	void create_special_meld(Card card_to_be_added);
	Hand get_player_hand();


	virtual void play();
	//virtual void strategy();
	virtual bool draw(Deck &draw_decks);
	virtual void meld();
	virtual void discard();
private:
	int score;
	Hand player_hand;
};

int validate_option_based_input(int lower_bound, int upper_bound);
