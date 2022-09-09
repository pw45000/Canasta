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
	Hand(std::vector<Card> debug_hand);
	bool create_meld(Card first, Card second, Card third);
	bool transfer_wild_card(Card transfer, int wild_origin, int meld_number);
	bool lay_off(Card addition, int meld_number, bool isWild);
	card_itr find_card (std::string card_name) const;
	void append_hand(Card card_drawn);
	private:
	std::vector<std::vector<Card>> hand_container;
};