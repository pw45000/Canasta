/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Cansta P1*
* Class : class numberand name here*
* Date : 9/13/22*
*********************************************************** */
#include "Deck.h"


Deck::Deck() {
	
	create_stock_pile();

	shuffle_stock();

	Card first_discard = draw("Stock");
	discard_pile.push_back(first_discard);
	//If the card is a red three, draw another card.
	if (first_discard.get_card_string() == "3H" || first_discard.get_card_string() =="3D")
		discard_pile.push_back(draw("Stock"));
}


void Deck::create_stock_pile()
{
	for (int decks = 0; decks < 2; decks++)
		for (int suite = 0; suite < 4; suite++) {
			for (int face = 2; face < 15; face++) {
				stock_pile.push_back(Card(suite, face));
			}
		}
	//add jokers to the deck manually, since they're not
	//part of a standard deck.
	stock_pile.push_back(Card('J', '1', "J1", 50));
	stock_pile.push_back(Card('J', '2', "J2", 50));
	stock_pile.push_back(Card('J', '3', "J3", 50));
	stock_pile.push_back(Card('J', '1', "J4", 50));

}

void Deck::shuffle_stock()
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::shuffle(stock_pile.begin(), stock_pile.end(), std::default_random_engine(seed));

}

Card Deck::draw(std::string pile_to_draw)
{
	Card card_drawn;
	if (pile_to_draw == "Stock") {
		card_drawn = *(stock_pile.begin());
	   stock_pile.erase(stock_pile.begin());
		return card_drawn;
	}
	else if (pile_to_draw == "Discard") {
		card_drawn = *(discard_pile.begin());
		discard_pile.erase(discard_pile.begin());
		return card_drawn;
	}
	else {
		return card_drawn;
	}
}

std::vector<Card> Deck::pick_up_discard()
{
	//might switch this to merge with draw depending on the UI of the program. 
	std::vector<Card> picked_discard = discard_pile;
	discard_pile.clear();
	return discard_pile;
}




