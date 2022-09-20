#pragma once



#include "Deck.h"
#include "Hand.h"


class Player {

public:
	Player();
	int get_score();
	bool has_canasta();
	bool hand_empty();
	void add_to_hand(Card card_to_be_added);
	void add_to_hand(std::vector<Card> cards_to_be_added);
	void create_special_meld(Card card_to_be_added);
	bool create_meld(std::vector<Card> potential_meld);
	void purge_red_threes();
	bool lay_off(Card addition, int meld_number);
	Hand get_player_hand();

	void temp_print_hand();
	bool transfer_card(Card wild_card, int wild_origin, int meld_number);


	virtual void play(Deck& draw_decks) = 0;
	//virtual void strategy();
	virtual bool draw(Deck &draw_decks) = 0;
	virtual void meld();
	virtual void discard();
	virtual void print_player_type() = 0;
private:
	int score;
	Hand player_hand;
};

int validate_option_based_input(int lower_bound, int upper_bound);
