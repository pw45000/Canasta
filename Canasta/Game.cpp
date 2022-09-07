// Debugging
//

#include <iostream>
#include <vector>
#include "Card.h"
int main()
{
	std::vector<Card> x;
	
	for (int decks = 0; decks <2; decks++)
	for (int suite = 0; suite < 4; suite++) {
		for (int face = 2; face < 15; face++) {
			x.push_back(Card(suite, face));
		}
	}
	x.push_back(Card('J', '1', "J1", 50));
	x.push_back(Card('J', '2', "J2", 50));
	x.push_back(Card('J', '3', "J3", 50));
	x.push_back(Card('J', '1', "J4", 50));
}
