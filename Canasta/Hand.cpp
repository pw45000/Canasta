#include "Hand.h"
Hand::Hand() {
	hand_container.reserve(15);
	meld_container.reserve(15);
}

Hand::Hand(std::vector<Card> debug_hand)
{
	hand_container = debug_hand;
}


bool Hand::transfer_wild_card(Card transfer, int wild_origin, int meld_target) {
	std::vector<Card> wild_origin_vector = meld_container.at(wild_origin);
	
	if (transfer.isWild()) {
		if (meld_container.at(wild_origin).size() == 3)
			return false;
		//checks if wild_card exists within it's designated meld.
		auto wild_itr = std::find(meld_container.at(wild_origin).begin(), meld_container.at(wild_origin).end(), transfer);
		//if the wild card is found and the meld isn't the minimum of a meld, transfer the wild card over.
		if (wild_itr != meld_container.at(wild_origin).end() && meld_container.at(meld_target).size()>=3) {
			meld_container.at(wild_origin).erase(wild_itr);
			meld_container.at(meld_target).push_back(transfer);
			
			return true;
		}
		else
			return false;

	}
	else
		return false;
	
}

bool Hand::lay_off(Card addition, int meld_number)
{
	std::vector <Card> existing_meld = meld_container.at(meld_number);
	//if the card is wild, ignore meld checking.

	if (existing_meld.at(0).isSpecial()) {
		std::cout << "Lay off error: You cannot add onto a red three's meld!" << std::endl;
		return false;
	}
	
	if (addition.isSpecial()) {
		std::cout << "Lay off error: You cannot add a special card to a meld!" << std::endl;
		return false;
	}
	
	if (addition.isWild()) {
		int wild_counter = 0;
		//count the amount of wild cards there is, since 
		//there cannot be more than 3. 
		for (int itr = 0; itr < existing_meld.size(); itr++)
			if (existing_meld.at(itr).isWild())
				wild_counter++;
		//However, do check how many wild cards there are. 
		if (wild_counter < 3) { 
			meld_container.at(meld_number).push_back(addition);
			remove_from_hand(addition);
			return true;
		}
		else {
			std::cout << "Lay off error: either the meld has too many wild cards! At most there can be 3 in a meld!" << std::endl;
			return false;
		}
	}
	//If it's not, ensure that it's going to the correct meld. 
	//This is done by checking the first element, as all wild cards will be at the end
	//of an initial meld. 
	else {
		if (addition.get_card_face() == existing_meld.at(meld_number).get_card_face()) {
			meld_container.at(meld_number).push_back(addition);
			remove_from_hand(addition);
			return true;
		}
		else {
			std::cout << "Lay off error: the card faces do not match the meld!" << std::endl;
			return false;
		}
	}

}

bool Hand::create_meld(Card first, Card second, Card third)
{
	//while it might be viewed as wasteful to make another meld, it'll come in handy
	//for searching for a wild card.
	std::vector<Card> potential_meld = { first, second, third };
	
	//to help in ensuring no duplicate melds.
	char card_rank;
	
	if (first.isSpecial() || second.isSpecial() || third.isSpecial()) {
		std::cout << "Meld error: you can't make a meld out of special cards!" << std::endl;
		return false;
	}

	
	if ((first.get_card_face() == second.get_card_face() && 
		second.get_card_face() == third.get_card_face())) {
		card_rank = first.get_card_face();

		if (is_not_duplicate_meld(card_rank)) {
			meld_container.push_back(potential_meld);
			for (int itr = 0; itr < 3; itr++) {
				remove_from_hand(potential_meld.at(itr));
			}
			return true;
		}

		else {
			std::cout << "Meld error: Meld of " << first.get_card_face() << "already exists!" << std::endl;
			return false;
		}
		

	}

	else {
		//both variables are declared outside of the loop
		//so as to show they are needed to be used elsewhere as well.
		int card_pos = 0;
		Card wild_Card;
		int wild_counter = 0;
		int wild_pos = 0;
		//search the potential meld for a wild card.
		for (card_pos = 0; card_pos < 3; card_pos++) {
			if (potential_meld.at(card_pos).isWild()) {
				wild_Card = potential_meld.at(card_pos);
				wild_pos = card_pos;
				wild_counter++;
				//rather than search through the vector again, we can just remove
				//the wild card.

			}
		}

		//need a counter to prevent vector errors.
		if (wild_counter <= 1)
			potential_meld.erase(potential_meld.begin() + wild_pos);


		//if the wild card is not removed, then break since it's not a valid meld due to lack
		//of equivalence of the faces
		if (potential_meld.size() == 3) {
			std::cout << "Meld error: one or more faces are different from another! Melds need to be of the same rank or have a wildcard!"
			<< std::endl;
			return false;
		}
		//If the two remaining cards are of the same rank, it's a valid meld.
		else if (potential_meld.at(0).get_card_face() == potential_meld.at(1).get_card_face()) {
			if (is_not_duplicate_meld(potential_meld.at(0).get_card_face())) {
				potential_meld.push_back(wild_Card);
				meld_container.push_back(potential_meld);
				for (int itr = 0; itr < 3; itr++) {
					remove_from_hand(potential_meld.at(itr));
				}


				return true;
			}

			else {
				std::cout << "Meld error: Meld of " << first.get_card_face() << "already exists!" << std::endl;
				return false;
			
			}
			
			
		}
		//otherwise, return since it's not a valid meld.
		else {
			std::cout << "Meld error: one or more faces are different from another! Melds need to be of the same rank or have a wildcard!"
			<< std::endl;
			return false;
		}
	}

}
bool Hand::create_meld(Card red_three)
{
	if (red_three.isSpecial() && (red_three.get_card_suit() == 'H' || red_three.get_card_suit() == 'D')) {
		std::vector<Card> special_meld;
		special_meld.push_back(red_three);
		meld_container.push_back(special_meld);
		remove_from_hand(red_three);
		return true;
	}
	else {
		return false;
	}

}
bool Hand::is_meldable(Card discard_head)
{
	int compatible_cards = 0;
	int wild_cards = 0;
	if (discard_head.isSpecial()) {
		if (discard_head.get_card_suit() == 'H' || discard_head.get_card_suit() == 'D')
			return true;
		else
			return false;
	}
	else if (discard_head.isWild()) {
		//O(n^2). vastly inefficient, looking into fixing this.
		for (int itr = 0; itr < hand_container.size(); itr++) {
			compatible_cards = std::count(hand_container.begin(), hand_container.end(), hand_container.at(itr));
			if (compatible_cards >= 2) {
				return true;
			}
		}
		return false;
	}
	else {
		for (int card = 0; card < hand_container.size(); card++) {
			if (hand_container.at(card).isWild())
				wild_cards = wild_cards + 1;
			if (hand_container.at(card).get_card_face() == discard_head.get_card_face())
				compatible_cards++;
		}
		
		if ((compatible_cards>=1 && wild_cards >= 1) || (compatible_cards == 2))
			return true;
		else
			return false;
	}
}
bool Hand::remove_from_hand(Card discarded_card) {
	card_itr discard_itr = std::find(hand_container.begin(), hand_container.end(), discarded_card);
	
	if (discard_itr != hand_container.end()) {
		hand_container.erase(discard_itr);
		return true;
	}
	
	else {
		return false;
	}
	
}

bool Hand::is_canasta(int meld_number)
{
	if (meld_container.at(meld_number).size() >= 7)
		return true;
	else
		return false;
}

bool Hand::is_not_duplicate_meld(char rank)
{
	for (std::vector<Card> meld : meld_container) {
		Card first_element = meld.at(0);
		char first_element_rank = first_element.get_card_face();
		if (rank == first_element_rank) {
			return false;
		}
	}
	return true;
}

bool Hand::hand_empty()
{
	bool hand_is_empty = (meld_container.size() == 0) ? true : false;
	return hand_is_empty;
}

bool Hand::has_canasta()
{
	for (int itr = 0; itr < meld_container.size(); itr++) {
		if (is_canasta(itr))
			return true;
	}
	return false;
}

int Hand::calculate_meld_points(int meld_number)
{
	int meld_points = 0;
	std::vector<Card> meld_target = meld_container.at(meld_number);

	for (card_itr card = meld_target.begin(); card != meld_target.end(); card++) {
		meld_points += card->get_point_value();
	}
	return meld_points;
}

void Hand::print_hand()
{
	for (Card hand_card : hand_container) {
		std::cout << hand_card.get_card_string() << " ";
	}
	std::cout << std::endl;
}

void Hand::print_melds()
{
	for (int meld = 0; meld < meld_container.size(); meld++) {
		std::cout << "[ ";
		for (int card = 0; card < meld_container.at(meld).size(); card++) {
			Card card_to_print = meld_container.at(meld).at(card);
			std::cout << card_to_print.get_card_string() << " ";
		}
		std::cout << "] ";
	}
	std::cout << std::endl;

}

void Hand::add_to_hand(Card card_to_add)
{
	hand_container.push_back(card_to_add);
}

void Hand::add_to_hand(std::vector<Card> card_to_add)
{
	for (card_itr card = card_to_add.begin(); card != card_to_add.end(); card++) {
		hand_container.push_back(*card);
	}
}

void Hand::purge_red_threes()
{
	for (int itr = 0; itr < hand_container.size(); itr++) {
		std::string card_string = hand_container.at(itr).get_card_string();
		if (card_string == "3H" || card_string == "3D") {
			Card red_three = hand_container.at(itr);
			create_meld(red_three);
		}
	}
}

int Hand::get_size_of_hand()
{
	return hand_container.size();
}

int Hand::get_size_of_meld()
{
	return meld_container.size();
}

Card Hand::get_card_from_hand(int pos)
{
	return hand_container.at(pos);
}

void Hand::print_all_wilds_of_meld(int meld_pos)
{
	std::vector<Card> wild_meld = meld_container.at(meld_pos);

	int wild_counter = 0;

	for (int itr = 0; itr < wild_meld.size(); itr++)
		if (wild_meld.at(itr).isWild()) {
			wild_counter++;
			std::cout << wild_counter << ". " << wild_meld.at(itr).get_card_string() << std::endl;
		}
}

int Hand::count_all_wilds_of_meld(int meld_pos)
{
	std::vector<Card> wild_meld = meld_container.at(meld_pos);
	int amount_of_wild_cards = 0;
	for (int itr = 0; itr < wild_meld.size(); itr++)
		if (wild_meld.at(itr).isWild())
			amount_of_wild_cards++;
	return amount_of_wild_cards;
}

Card Hand::get_card_from_meld(int meld_pos, int card_pos)
{
	return meld_container.at(meld_pos).at(card_pos);
}



