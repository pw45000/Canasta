/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */
#include "Deck.h"

/* *********************************************************************
Function Name: Deck
Purpose: The default deck constructor. It creates the stock pile and discard pile, and continues drawing from 
			the stock pile until a red three is not found and adds said drawn card to the discard pile.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: create_stock_pile()
Purpose: Creates the stock pile by creating two decks of 52 cards (4 suits of 13 cards), and adds each card to
			the stock pile, manually adding in jokers.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
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
/* *********************************************************************
Function Name: shuffle_stock()
Purpose: Shuffles the stock pile using a seed based on the OS.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Deck::shuffle_stock()
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::shuffle(stock_pile.begin(), stock_pile.end(), std::default_random_engine(seed));

}

/* *********************************************************************
Function Name: draw_from_stock()
Purpose: Draws a single card from stock.
Parameters: none
Return Value: Card representing the card drawn.
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: draw_from_discard()
Purpose: Draws the entire discard pile and returns it.
Parameters: none
Return Value: Vector of Cards representing the picked up discard pile.
Assistance Received: none
********************************************************************* */
std::vector<Card> Deck::draw_from_discard() {
	std::vector<Card> copy_of_discard = discard_pile;
	discard_pile.clear();

	Card first_discard;

	return copy_of_discard;
}



/* *********************************************************************
Function Name: discard()
Purpose: Draws the entire discard pile and returns it.
Parameters: 
			  discarded_card, which is a Card that represents the card being
			  sent to the discard pile.
Return Value: none
Assistance Received: none
********************************************************************* */
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

/* *********************************************************************
Function Name: stock_is_empty()
Purpose: Returns if the stock pile is empty or not.
Parameters: none
Return Value: bool representing if the stock pile is empty.
Assistance Received: none
********************************************************************* */
bool Deck::stock_is_empty() const
{
	return stock_pile.size() == 0;
}

/* *********************************************************************
Function Name: discard_is_empty()
Purpose: Returns if the discard pile is empty or not.
Parameters: none
Return Value: bool representing if the discard pile is empty.
Assistance Received: none
********************************************************************* */
bool Deck::discard_is_empty() const
{
	return discard_pile.size() == 0;
}

/* *********************************************************************
Function Name: both_piles_are_empty()
Purpose: Returns if both the discard and stock pile is empty.
Parameters: none
Return Value: bool representing if both the discard pile and stock pile are empty.
Assistance Received: none
********************************************************************* */
bool Deck::both_piles_are_empty () const
{
	return (stock_is_empty() && discard_is_empty());
}

/* *********************************************************************
Function Name: get_discard_is_frozen()
Purpose: Returns if the discard pile is frozen.
Parameters: none
Return Value: bool representing if both the discard pile is frozen.
Assistance Received: none
********************************************************************* */
bool Deck::get_discard_is_frozen() const
{
	if (discard_pile.size() != 0) {
		return discard_is_frozen || get_top_discard_pile().isSpecial();
	}
	else
		return discard_is_frozen;
}

/* *********************************************************************
Function Name: get_top_discard_pile()
Purpose: Returns if the discard pile is frozen.
Parameters: none
Return Value: Card representing the top of the discard pile.
Assistance Received: none
********************************************************************* */
Card Deck::get_top_discard_pile() const
{
	if (discard_pile.size() != 0)
		return *discard_pile.begin();
	else
		return Card();
}

/* *********************************************************************
Function Name: print_stock_pile()
Purpose: Prints the contents of the stock pile.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Deck::print_stock_pile() const
{
	for (Card card : stock_pile)
		std::cout << card.get_card_string() << " ";
	std::cout << std::endl;
}

/* *********************************************************************
Function Name: print_top_of_discard_pile()
Purpose: Prints the top of the discard pile if it isn't empty.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Deck::print_top_of_discard_pile() const
{
	if (discard_is_empty()==false)
		std::cout << discard_pile.at(0).get_card_string() << std::endl;
	else {
		std::cout << std::endl;
	}
}
/* *********************************************************************
Function Name: print_discard_pile()
Purpose: Prints the contents of the entire discard pile.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Deck::print_discard_pile() const
{
	for (Card card : discard_pile)
		std::cout << card.get_card_string() << " ";
	std::cout << std::endl;
}

/* *********************************************************************
Function Name: discard_push_front()
Purpose: Pushes a card that has been discarded to the front of the discard pile.
Parameters: 
			  pushed_card, a Card representing a card added to the discard pile.
Return Value: none
Assistance Received: none
********************************************************************* */
void Deck::discard_push_front(Card pushed_card)
{
	discard_pile.insert(discard_pile.begin(), pushed_card);
}

/* *********************************************************************
Function Name: set_discard_freeze()
Purpose: Sets if the discard pile is frozen or not. 
Parameters:
			  is_frozen, a bool representing if the discard pile is frozen.
Return Value: none
Assistance Received: none
********************************************************************* */
void Deck::set_discard_freeze(bool is_frozen)
{
	discard_is_frozen = is_frozen;
}

/* *********************************************************************
Function Name: clear_discard()
Purpose: Empties the discard pile.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Deck::clear_discard()
{
	discard_pile.clear();
}

/* *********************************************************************
Function Name: get_size_of_discard
Purpose: Empties the discard pile.
Parameters: none
Return Value: int, representing the size of the discard pile.
Assistance Received: none
********************************************************************* */
int Deck::get_size_of_discard() const
{
	return discard_pile.size();
}

/* *********************************************************************
Function Name: print_top_of_stock
Purpose: Prints the top of stock.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Deck::print_top_of_stock() const
{
	if (stock_pile.size() > 0)
		std::cout << stock_pile.at(0).get_card_string() << std::endl;
}

/* *********************************************************************
Function Name: set_discard_pile
Purpose: Sets the discard_pile data member to the passed vector of Cards parameter.
Parameters: 
			  discard_pile, a vector of cards representing the discard pile.
Return Value: none
Assistance Received: none
********************************************************************* */
void Deck::set_discard_pile(std::vector<Card> discard_pile)
{
	this->discard_pile = discard_pile;
}

/* *********************************************************************
Function Name: set_stock_pile
Purpose: Sets the stock_pile data member to the passed vector of Cards parameter.
Parameters:
			  stock_pile, a vector of cards representing the stock pile.
Return Value: none
Assistance Received: none
********************************************************************* */
void Deck::set_stock_pile(std::vector<Card> stock_pile)
{
	this->stock_pile = stock_pile;
}




