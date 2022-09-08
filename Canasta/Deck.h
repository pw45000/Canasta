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


class Deck {
public:
	Deck();
	void create_stock_pile();
	void shuffle_stock();
	Card draw(std::string pile_to_draw);
private: 
	//While it was tempting to use a deque
	//since the datastructure not only sounds like a deck
	//but can remove and add from the front, the lack of
	//contiguity and performance mixed with the fact that 
	//implementing a pop and push at the front is trivial
	//is why I chose a vector. 
	std::vector<Card> stock_pile;
	std::vector<Card> discard_pile;
};