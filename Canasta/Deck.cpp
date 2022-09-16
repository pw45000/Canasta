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

	Card first_discard = draw_from_stock();
	discard_pile.push_back(first_discard);
	//If the card is a red three, draw another card.
	if (first_discard.get_card_string() == "3H" || first_discard.get_card_string() =="3D" || first_discard.isWild())
		discard_pile.push_back(draw_from_stock());
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

Card Deck::draw_from_stock()
{
	Card card_drawn;
	//dereference the .begin() iterator. 
	//while I could've used the 0 index,
	//this seems to be a lot more intuitive.
	card_drawn = *(stock_pile.begin());
	stock_pile.erase(stock_pile.begin());
	return card_drawn;
}


std::vector<Card> Deck::draw_from_discard() {
	//might switch this to merge with draw depending on the UI of the program. 
	std::vector<Card> picked_discard = discard_pile;
	discard_pile.clear();
	return discard_pile;
}

void Deck::discard(Card discarded_card)
{
	if (discarded_card.get_card_string() == "3S" || discarded_card.get_card_string() == "3C") {
		discard_is_frozen = true;
	}
	else if (discard_is_frozen && discarded_card.isNatural()) {
		discard_is_frozen = false;
	}
	
	discard_pile.push_back(discarded_card);


}

bool Deck::stock_is_empty()
{
	return stock_pile.size() == 0;
}

bool Deck::discard_is_empty()
{
	return discard_pile.size() == 0;
}

bool Deck::get_discard_is_frozen()
{
	return discard_is_frozen;
}

Card Deck::get_top_discard_pile()
{
	return *discard_pile.begin();
}

void Deck::set_discard_freeze(bool is_frozen)
{
	discard_is_frozen = is_frozen;
}




