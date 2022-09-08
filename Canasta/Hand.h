#pragma once
#include <string>
#include <vector>
#include "Deck.h"
#include "Card.h"


class Hand {
public:
	Hand();

private:
	std::vector<std::vector<Card>> hand;
};