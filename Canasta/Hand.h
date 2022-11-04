/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */

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
	bool lay_off(Card addition, int meld_number);
	bool transfer_wild_card(Card transfer, int wild_origin, int meld_number);


	bool remove_from_hand(Card discard);
	
	bool is_canasta(int meld_number) const;
	bool is_not_duplicate_meld(char rank) const;
	bool hand_empty() const;
	bool has_canasta() const;
	bool meld_exits_already(Card card_to_search) const;
	bool is_meldable_with_melds(Card discard_head) const;
	bool is_meldable(Card discard_head) const;


	int calculate_meld_points(int meld_number);
	
	void print_hand() const; 
	void print_melds() const;
	void add_to_hand(Card card_to_add);
	void add_to_hand(std::vector<Card> card_to_add);
	void purge_red_threes();
	
	int get_size_of_hand() const;
	int get_size_of_meld() const;
	int get_score_from_meld(int meld_pos) const;
	int get_total_score(bool has_gone_out) const;
	int size_of_non_spec_melds() const;
	std::vector<Card> get_wild_cards(int meld_pos) const;
	std::vector<Card> get_wild_cards_ignore_transfer(int meld_pos) const;
	std::vector<Card> get_wild_cards_from_hand() const;
	std::vector<std::vector<Card>> get_meld() const;
	std::vector<Card> get_hand_container() const;
	Card get_card_from_hand(int pos) const;
	Card get_card_from_meld(int meld_pos, int card_pos) const;


	void print_all_wilds_of_meld(int meld) const;
	


	
	void clear_transfer_states();
	void clear_all_data();
	
	void set_meld(std::vector<std::vector<Card>> &meld_container);
	void set_hand(std::vector<Card> &hand_container);


	void sort();


	private:
	std::vector<std::vector<Card>> meld_container;
	std::vector<Card> hand_container;
};