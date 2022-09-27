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
	bool create_meld(Card first, Card second, Card third);
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
	void clear_hand_and_meld();

	void print_vector(std::vector<Card> vector_to_print);
	void print_meld(int meld_pos);
	int get_score_from_meld(int meld_pos);

	void sort_melds(std::vector<std::vector<Card>> &melds_to_sort);
	std::vector<Card> get_wild_cards_from_vector(std::vector<Card> arbitrary_card_vect);
	bool meld_of_card_exists(Card card_to_search);
	
	int get_absolute_pos_from_relative_meld(std::vector<Card> arbitrary_meld_vect);


	virtual bool play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) = 0;
	//virtual void strategy();
	virtual bool draw(Deck &draw_decks) = 0;
	virtual void meld(std::vector<std::vector<Card>> enemy_melds) = 0;
	virtual void discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) = 0;
	virtual void print_player_type() = 0;
	virtual bool choose_to_go_out() = 0;
	virtual std::string get_player_type() = 0;
	virtual void strategy(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) = 0;
	
	bool get_go_out_decision() const; 
	void set_go_out_decision(bool go_out_decision); 
	
	bool go_out();

	int get_dangerous_amount_of_cards(std::vector<std::vector<Card>> enemy_melds);
	bool is_dangerous_card(Card potential_danger_card, std::vector<std::vector<Card>> enemy_melds);

private:
	int score;
	Hand player_hand;
	bool has_decided_to_go_out;
};

int validate_option_based_input(int lower_bound, int upper_bound);
int validate_option_based_input(int lower_bound, int upper_bound, bool special_option);