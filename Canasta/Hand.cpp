#include "Hand.h"

void Hand::create_meld(Card first, Card second, Card third)
{
	std::vector<Card> potential_meld = { first, second, third };
	if (first.get_card_face() == second.get_card_face() == third.get_card_face()) {
		hand.push_back(potential_meld);
	}

	else {
		int card_pos;
		Card wild_Card;
		for (card_pos = 0; card_pos < 2; card_pos++) {
			if (potential_meld.at(card_pos).isWild()) {
				wild_Card = potential_meld.at(card_pos);
				potential_meld.erase(potential_meld.begin() + card_pos);
			}
		}
		if (potential_meld.size() == 3)
			return;
		else if (potential_meld.at(0).get_card_face() == potential_meld.at(1).get_card_face()) {
			potential_meld.push_back(wild_Card);
			hand.push_back(potential_meld);
		}
		else {
			return;
		}



	}

}

card_itr Hand::find_card(std::string card_name) const {
	//at is used here since it has memory safety compared to the subscript operator.
	card_itr card_position = std::find(std::begin(hand.at(0)), std::end(hand.at(0)),card_name);
	return card_position;
}
//https://stackoverflow.com/questions/47432494/how-to-find-an-element-in-a-vector-of-vectors