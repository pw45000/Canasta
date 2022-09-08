#pragma once
#include <string>
#include <vector>
#include "Deck.h"
#include "Card.h"


//To extract a card, the iterator looks verbose. 
//A typedef will hope to fix this.
typedef  std::vector<Card>::const_iterator card_itr;

class Hand {
public:
	Hand();
	void create_meld(Card first, Card second, Card third);
	void transfer_meld(Card transfer);
	card_itr find_card (std::string card_name) const;
	private:
	std::vector<std::vector<Card>> hand;
};