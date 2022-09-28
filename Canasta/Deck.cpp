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

	Card first_discard;
	//If the card is a red three, draw another card.
	do {
		first_discard = draw_from_stock();
		discard_push_front(first_discard);
	}
	while (first_discard.is_red_three() || first_discard.isWild());
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
	stock_pile.push_back(Card('J', '4', "J4", 50));

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
	std::vector<Card> copy_of_discard = discard_pile;
	discard_pile.clear();

	Card first_discard;

	return copy_of_discard;
}




void Deck::discard(Card discarded_card)
{
	if (discarded_card.get_card_string() == "3S" || discarded_card.get_card_string() == "3C") {
		discard_is_frozen = true;
	}
	else if (discard_is_frozen && discarded_card.isNatural()) {
		discard_is_frozen = false;
	}
	
	discard_push_front(discarded_card);


}

bool Deck::stock_is_empty()
{
	return stock_pile.size() == 0;
}

bool Deck::discard_is_empty()
{
	return discard_pile.size() == 0;
}

bool Deck::both_piles_are_empty()
{
	return (stock_is_empty() && discard_is_empty());
}

bool Deck::get_discard_is_frozen()
{
	if (discard_pile.size() != 0) {
		return discard_is_frozen || get_top_discard_pile().isSpecial();
	}
	else
		return discard_is_frozen;
}

Card Deck::get_top_discard_pile()
{
	if (discard_pile.size() != 0)
		return *discard_pile.begin();
	else
		return Card();
}

void Deck::print_stock_pile()
{
	for (Card card : stock_pile)
		std::cout << card.get_card_string() << " ";
	std::cout << std::endl;
}

//learn to f11....
void Deck::print_top_of_discard_pile()
{
	if (discard_is_empty()==false)
		std::cout << discard_pile.at(0).get_card_string() << std::endl;
	else {
		std::cout << std::endl;
	}
}

void Deck::print_discard_pile()
{
	for (Card card : discard_pile)
		std::cout << card.get_card_string() << " ";
	std::cout << std::endl;
}

void Deck::discard_push_front(Card pushed_card)
{
	discard_pile.insert(discard_pile.begin(), pushed_card);
}


void Deck::set_discard_freeze(bool is_frozen)
{
	discard_is_frozen = is_frozen;
}

void Deck::clear_discard()
{
	discard_pile.clear();
}

int Deck::get_size_of_discard() const
{
	return discard_pile.size();
}

void Deck::print_top_of_stock()
{
	if (stock_pile.size() > 0)
		std::cout << stock_pile.at(0).get_card_string() << std::endl;
}

void Deck::set_discard_pile(std::vector<Card> discard_pile)
{
	this->discard_pile = discard_pile;
}

void Deck::set_stock_pile(std::vector<Card> stock_pile)
{
	this->stock_pile = stock_pile;
}




