#include <iostream>
#include <vector>
#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include <random>
#include <algorithm>
#include "Game.h"

int main() {
	/*
	
	Deck maindeck;

	std::vector<Card> a;
	auto x = (Card(0, 7));
	auto y = (Card(0, 7));
   auto z = (Card(0, 7));
	//auto add = Card('J', '1', "J1", 50);
	auto add = Card(0, 2);
	auto red_three = Card(0, 3);
	auto black_three = Card(2, 3);


	auto x1 = (Card(0, 7));
	auto y2 = (Card(0, 7));
	auto z2 = (Card(0, 7));

	a.push_back(x);
	a.push_back(y);
	a.push_back(z);
	a.push_back(x1);
	a.push_back(y2);
	a.push_back(z2);
	a.push_back(add);


	Hand my_test_hand(a);
	
	
	bool issucc = my_test_hand.create_meld(x, y, z);
	bool issucc2 = my_test_hand.create_meld(x1, y2, z2);
	bool issucc3 = my_test_hand.lay_off(add, 1);
	bool issucc4 = my_test_hand.transfer_wild_card(add, 1, 0);
	bool canMeld = my_test_hand.is_meldable(black_three);
	*/
	
	
	//auto add = Card('J', '1', "J1", 50);
	//std::cout << add.isWild() << std::endl;;

	//Game Canasta;
	//Canasta.main_menu();

	Round x;
	x.load_game();


}