#pragma once
#include <string>
#include <vector>
#include "Deck.h"
#include "Card.h"
#include <iostream>

//To extract a card, the iterator looks verbose. 
//A typedef will hope to fix this.
typedef  std::vector<Card>::const_iterator card_itr;

class Hand {
public:
	Hand();
	Hand(std::vector<Card> debug_hand);
	bool create_meld(Card first, Card second, Card third);
	bool create_meld(Card red_three);
	bool is_meldable(Card discard_head);
	bool transfer_wild_card(Card transfer, int wild_origin, int meld_number);
	bool lay_off(Card addition, int meld_number);
	bool remove_from_hand(Card discard);
	bool is_canasta(int meld_number);
	bool is_not_duplicate_meld(char rank);
	bool hand_empty();
	bool has_canasta();
	int calculate_meld_points(int meld_number);
	void print_hand(); 
	void print_melds();
	void add_to_hand(Card card_to_add);
	void add_to_hand(std::vector<Card> card_to_add);
	void purge_red_threes();
	int get_size_of_hand();
	int get_size_of_meld();
	Card get_card_from_hand(int pos);
	void print_all_wilds_of_meld(int meld);
	int count_all_wilds_of_meld(int meld);
	Card get_card_from_meld(int meld_pos, int card_pos);


	private:
	std::vector<std::vector<Card>> meld_container;
	std::vector<Card> hand_container;
};