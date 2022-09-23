#pragma once



#include "Deck.h"
#include "Hand.h"


class Player {

public:
	Player();
	int get_score();
	Hand get_player_hand();
	bool has_canasta();
	bool hand_empty();
	void add_to_hand(Card card_to_be_added);
	void add_to_hand(std::vector<Card> cards_to_be_added);
	void create_special_meld(Card card_to_be_added);
	bool create_meld(std::vector<Card> potential_meld);
	void purge_red_threes();
	
	bool lay_off(Card addition, int meld_number);
	bool transfer_card(Card wild_card, int wild_origin, int meld_number);
	bool can_go_out();
	bool remove_from_hand(Card discard_card);

	void sort_hand();
	void temp_print_hand();
	
	void clear_transfer_states();
	void clear_hand();
	void add_to_score(int score_addition);
	
	void set_player_score(int score);
	void set_meld(std::vector<std::vector<Card>> meld_container);
	void set_hand(std::vector<Card> hand_container);


	virtual bool play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) = 0;
	//virtual void strategy();
	virtual bool draw(Deck &draw_decks) = 0;
	virtual void meld();
	virtual void discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) = 0;
	virtual void print_player_type() = 0;
	virtual bool choose_to_go_out() = 0;
	virtual std::string get_player_type() = 0;
	
	
	
	bool go_out();


private:
	int score;
	Hand player_hand;
};

int validate_option_based_input(int lower_bound, int upper_bound);
