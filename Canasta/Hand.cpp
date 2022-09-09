#include "Hand.h"
Hand::Hand() {
	hand_container.reserve(15);
	std::vector <Card> initial_hand;
	hand_container.push_back(initial_hand);
}

Hand::Hand(std::vector<Card> debug_hand)
{
	hand_container.reserve(15);
	hand_container.push_back(debug_hand);
}


bool Hand::transfer_wild_card(Card transfer, int wild_origin, int meld_target) {
	std::vector<Card> wild_origin_vector = hand_container.at(wild_origin);
	
	if (transfer.isWild()) {
		if (hand_container.at(wild_origin).size() == 3)
			return false;
		//checks if wild_card exists within it's designated meld.
		auto wild_itr = std::find(hand_container.at(wild_origin).begin(), hand_container.at(wild_origin).end(), transfer);
		//if the wild card is found and the meld isn't the minimum of a meld, transfer the wild card over.
		if (wild_itr != hand_container.at(wild_origin).end() && hand_container.at(meld_target).size()>=3) {
			hand_container.at(wild_origin).erase(wild_itr);
			hand_container.at(meld_target).push_back(transfer);
			
			return true;
		}
		else
			return false;

	}
	else
		return false;
	
}

bool Hand::lay_off(Card addition, int meld_number, bool isWild)
{
	std::vector <Card> existing_meld = hand_container.at(meld_number);
	//if the card is wild, ignore meld checking.
	if (isWild) {
		int wild_counter = 0;
		//count the amount of wild cards there is, since 
		//there cannot be more than 3. 
		for (int itr = 0; itr < existing_meld.size(); itr++)
			if (existing_meld.at(itr).isWild())
				wild_counter++;
		//However, do check how many wild hards there are. 
		if (wild_counter < 3) { 
			hand_container.at(meld_number).push_back(addition);
			return true;
		}
		else {
			return false;
		}
	}
	//If it's not, ensure that it's going to the correct meld. 
	else {
		if (addition.get_card_face() == existing_meld.at(meld_number).get_card_face()) {
			hand_container.at(meld_number).push_back(addition);
			return true;
		}
		else {
			return false;
		}
	}

}

void Hand::append_hand(Card card_drawn)
{
	hand_container.at(0).push_back(card_drawn);
}

bool Hand::create_meld(Card first, Card second, Card third)
{
	//while it might be viewed as wasteful to make another meld, it'll come in handy
	//for searching for a wild card.
	std::vector<Card> potential_meld = { first, second, third };
	if ((first.get_card_face() == second.get_card_face() && 
		second.get_card_face() == third.get_card_face())) {
		hand_container.push_back(potential_meld);
		return true;
	}

	else {
		//both variables are declared outside of the loop
		//so as to show they are needed to be used elsewhere as well.
		int card_pos; 
		Card wild_Card;
		//search the potential meld for a wild card.
		for (card_pos = 0; card_pos < 3; card_pos++) {
			if (potential_meld.at(card_pos).isWild()) {
				wild_Card = potential_meld.at(card_pos);
				//rather than search through the vector again, we can just remove
				//the wild card.
				potential_meld.erase(potential_meld.begin() + card_pos);
			}
		}
		//if the wild card is not removed, then break since it's not a valid meld.
		if (potential_meld.size() == 3)
			return false;
		//If the two remaining cards are of the same rank, it's a valid meld.
		else if (potential_meld.at(0).get_card_face() == potential_meld.at(1).get_card_face()) {
			potential_meld.push_back(wild_Card);
			hand_container.push_back(potential_meld);
			return true;
		}
		//otherwise, return since it's not a valid meld.
		else {
			return false;
		}
	}

}

