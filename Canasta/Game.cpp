/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Cansta P1*
* Class : class numberand name here*
* Date : 9/13/22*
*********************************************************** */

#include <iostream>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include <random>
#include <algorithm>
int main()
{
	Deck maindeck;

	std::vector<Card> a;
	auto x = (Card(0, 7));
	auto y = (Card(0, 7));
   auto z = (Card(0, 7));
	//auto add = Card('J', '1', "J1", 50);
	auto add = Card(0, 7);


	auto x1 = (Card(0, 7));
	auto y2 = (Card(0, 7));
	auto z2 = (Card(0, 7));

	Hand my_test_hand;

	/*
	for (int i = 0; i < 15; i++) {
		my_test_hand.append_hand((maindeck.draw("Stock")));
	}
	*/
	
	bool issucc = my_test_hand.create_meld(x, y, z);
	bool issucc2 = my_test_hand.create_meld(x1, y2, z2);
	bool issucc3 = my_test_hand.lay_off(add, 2, add.isWild());
	bool issucc4 = my_test_hand.transfer_wild_card(add, 2, 1);
}
