#pragma once
/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Cansta P1*
* Class : class numberand name here*
* Date : 9/13/22*
*********************************************************** */
#include <vector>
#include <string>
#include "Card.h"
#include <chrono>
#include <random>
#include <iostream>

class Deck {
public:
	Deck();
	void create_stock_pile();
	void shuffle_stock();
	Card draw_from_stock();
	std::vector<Card> draw_from_discard();
	void discard(Card discarded_card);
	bool stock_is_empty();
	bool discard_is_empty();
	bool both_piles_are_empty();
	bool get_discard_is_frozen();
	Card get_top_discard_pile();
	void print_stock_pile();
	void print_top_of_discard_pile();
	void print_discard_pile();
	void discard_push_front(Card pushed_card);
	void set_discard_freeze(bool is_frozen);
	void clear_discard();
	int get_size_of_discard() const; 


	void print_top_of_stock();
	void set_discard_pile(std::vector<Card> discard_pile);
	void set_stock_pile(std::vector<Card> stock_pile);


private: 
	//While it was tempting to use a deque
	//since the datastructure not only sounds like a deck
	//but can remove and add from the front, the lack of
	//contiguity and performance mixed with the fact that 
	//implementing a pop and push at the front is trivial
	//is why I chose a vector. 
	std::vector<Card> stock_pile;
	std::vector<Card> discard_pile;
	bool discard_is_frozen = false;
};