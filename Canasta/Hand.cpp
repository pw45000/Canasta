/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */

#include "Hand.h"


/* *********************************************************************
Function Name: Hand
Purpose: The default constructor. It reserves 15 cards for the initial draw, as well as 10 for the meld container
			as that's the total amount of possible melds there are. 
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
Hand::Hand() {
	hand_container.reserve(15);
	meld_container.reserve(10);
}
/* *********************************************************************
Function Name: Hand
Purpose: A constructor made for debugging. 
Parameters: debug_hand: a vector of Cards representing what is to be assigned to the hand_container.
Return Value: none
Assistance Received: none
********************************************************************* */
Hand::Hand(std::vector<Card> debug_hand)
{
	hand_container = debug_hand;
}


/* *********************************************************************
Function Name: transfer_wild_card 
Purpose: A function made to transfer wild cards between melds. 
Parameters:
			   transfer: a Card that is the selected card to be transferred.
				wild_origin: an int representing the position of which meld to be transferred from.
				meld_target: an int representing the position of which meld to transfer to.
Algorithm: 
			1. See if the Card selected to be transferred is wild (if not, send an error message) 
				and extract the meld from which it originates, if the meld has a size greater than 3, the minimum size of a meld.
			2. Check if it has been transferred already, if so, then output an error message.
			3. Check if the meld target is -2, which is the option to transfer it to the hand. If so:
				a) Check if it could meld with the hand. If so, transfer the card from the meld and add to the hand.
				b) If it is not, display an error message.
			4. If it is not, check that the target meld has no more than 3 wild cards, and that the card is not a meld of a red three.
			5. If all the criteria are met, transfer the card over from the original meld to the target meld.
			6. Return true or false if the operation was successful. 
Local variables: 
					wild_origin_vector: a vector representing the meld from which the wild card originates.
					min_meld_size: an int representing the minimum size of a meld. 
					transfer_to_hand_option: an int representing the option to transfer a wild card to the hand.
					wild_itr: a card iterator which represents if the wild card is found in it's originating meld.
Return Value: bool, returning if the operation is successful or not.
Assistance Received: none
********************************************************************* */
bool Hand::transfer_wild_card(Card transfer, int wild_origin, int meld_target) {
	std::vector<Card> wild_origin_vector = meld_container.at(wild_origin);
	
	int min_meld_size = 3;
	int transfer_to_hand_option = -2;


	if (transfer.isWild() ) {
		if (meld_container.at(wild_origin).size() <= min_meld_size) {
			std::cout << "The selected meld to trasnfer from is too small! Please transfer with a meld with a size >3..." << std::endl;
			return false;
		}

		if (transfer.get_has_transferred() == true) {
			std::cout << "The current card has been transfered once! Please only transfer wild cards once per turn." << std::endl;
			return false;
		}


		if (meld_target == transfer_to_hand_option) {
			
			//checks if wild_card exists within it's designated meld.
			auto wild_itr = std::find(meld_container.at(wild_origin).begin(), meld_container.at(wild_origin).end(), transfer);
			//if the wild card is found and the meld isn't the minimum of a meld, transfer the wild card over.
			if (is_meldable(transfer) && wild_itr!=meld_container.at(wild_origin).end()) {
				auto wild_itr = std::find(meld_container.at(wild_origin).begin(), meld_container.at(wild_origin).end(), transfer);
				meld_container.at(wild_origin).erase(wild_itr);
				hand_container.push_back(transfer);
				return true;
			}
			else {
				std::cout << "Can't transfer wild card: you can't make any melds with the hand!" << std::endl;
				return false;
			}

		}


		//checks if wild_card exists within it's designated meld.
		auto wild_itr = std::find(meld_container.at(wild_origin).begin(), meld_container.at(wild_origin).end(), transfer);
		//if the wild card is found and the meld isn't the minimum of a meld, transfer the wild card over.
		if (wild_itr != meld_container.at(wild_origin).end() && meld_container.at(meld_target).size() >= min_meld_size) {
			meld_container.at(wild_origin).erase(wild_itr);
			transfer.set_has_transferred(true);
			meld_container.at(meld_target).push_back(transfer);

			return true;
		}
		else
			std::cout << "Transfer wild card error: cannot transfer wildcard of meld size 3 or less, or wild card not found..."
			<< std::endl;
		return false;

	}
	else {
		std::cout << "The selected card is not a wild card!" << std::endl;
		return false;
	}
}


/* *********************************************************************
Function Name: lay_off
Purpose: To add a card to a pre-existing meld.
Parameters:
				addition: a Card that is the selected card to be added to a meld.
				meld_number: an int which represents the position of which meld to add onto.
Algorithm:
			1. Check if the existing meld is special, i.e. a meld of a red three. Also, check if the addition is a red three.
			2. If the card to be added is wild, check that the amount of wild cards, making sure that there are no more than three.
				If there are no more than three, transfer the wild card from the hand to the meld. 
			3. If the card to be added is not wild, check that the card to added face matches the meld's face. 
			4. Return true if the operation was successful, false if the criteria above isn't met. 
Local variables:
					first_pos: an integer which represents the first position in a vector.
					min_meld_pos: the minimum size for a vector.
Return Value: bool, returning if the operation is successful or not.
Assistance Received: none
********************************************************************* */
bool Hand::lay_off(Card addition, int meld_number)
{
	std::vector <Card> existing_meld = meld_container.at(meld_number);
	//if the card is wild, ignore meld checking.

	int first_pos = 0;
	int min_meld_pos = 3;
	
	if (existing_meld.at(first_pos).isSpecial()) {
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
		for (int card_pos = 0; card_pos < existing_meld.size(); card_pos++)
			if (existing_meld.at(card_pos).isWild())
				wild_counter++;
		//However, do check how many wild cards there are. 
		if (wild_counter < min_meld_pos) {
			addition.set_has_transferred(true);
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
		if (addition.get_card_face() == existing_meld.at(first_pos).get_card_face()) {
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

/* *********************************************************************
Function Name: create_meld
Purpose: To move cards from the hand to create a new meld. 
Parameters:
				first: a Card which is the first card passed. 
				second: a Card which is the second card passed. 
				third: a Card which is the third Card passed. 
Algorithm:
			1. Create a vector of the potential melded cards from the parameters described above. 
			2. Check if any one of them are special, return false if so. 
			3. Check if any of the cards are wild. 
			4. If not, check that that they all have the same face, if so:
				a) check if the meld is a duplicate meld. If so, return false.
				b) If it is not a duplicate meld, remove the cards from the hand and 
					push the potential meld into the meld container. 
			5. If there is a wild card: 
				a) Tally the amount of wild cards in the potential meld. If there's more than one, 
					return false. 
				b) If that is not the case, store the wild cards position and remove it. 
				c) Check if the two cards have the same face. 
				d) If so, add the wild card back into the potential meld, remove the hands from the hand, 
					and add back to the meld container.
			6. Return if the operation was successful. 
Local variables:
					potential_meld: a vector of Cards which is used to be pushed to the meld and for all comparisons.
					card_rank: a char that is used to compare against other melds to ensure no duplicates.
Return Value: bool, returning if the operation is successful or not.
Assistance Received: none
********************************************************************* */
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

	bool has_wilds = (first.isWild() || second.isWild() || third.isWild());

	
	if ((first.get_card_face() == second.get_card_face() && 
		second.get_card_face() == third.get_card_face()) &&!has_wilds) {
		card_rank = first.get_card_face();

		if (is_not_duplicate_meld(card_rank)) {
			meld_container.push_back(potential_meld);
			for (int card_pos = 0; card_pos < 3; card_pos++) {
				remove_from_hand(potential_meld.at(card_pos));
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
		//of equivalent faces
		if (potential_meld.size() == 3) {
			std::cout << "Meld error: one or more faces are different from another! Melds need to be of the same rank or have a wildcard!"
			<< std::endl;
			return false;
		}
		//If the two remaining cards are of the same rank, it's a valid meld.
		else if (potential_meld.at(0).get_card_face() == potential_meld.at(1).get_card_face()) {
			if (is_not_duplicate_meld(potential_meld.at(0).get_card_face())) {
				wild_Card.set_has_transferred(true);
				potential_meld.push_back(wild_Card);
				meld_container.push_back(potential_meld);
				for (int card_pos = 0; card_pos < 3; card_pos++) {
					remove_from_hand(potential_meld.at(card_pos));
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
/* *********************************************************************
Function Name: create_meld
Purpose: Creates a meld of a red three. Verifies the card passed is a red three.
Parameters: red_three: a Card that represents a red three.
Return Value: bool that represents if the operation was successful or not.
Assistance Received: none
********************************************************************* */

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

/* *********************************************************************
Function Name: is_meldable_with_melds
Purpose: Checks if the top of the discard is meldable with the current Player's melds.
Parameters: discard_head: a Card that represents the top of the discard.
Return Value: bool that represents if the top of the discard is meldable with other melds.
Algorithm: 
			 1. If the passed card is a special, check if it's a red three. If so, return true, otherwise, return false.
			 2. If the passed card is wild, check if there's a meld with less than three wild cards.
			 3. If the passed card is natural, check that there is a meld that exists which first Card's face matches it's face.
			 4. Depending on if the criteria are met above, return true or false.
Local variables: 
				    can_meld: a bool that represents if the card can meld. 
					 first_pos: represents the first position in a vector.
Assistance Received: none
********************************************************************* */
bool Hand::is_meldable_with_melds(Card passed_card)  const {
	bool can_meld = false;
	int first_pos = 0;

	if (passed_card.isSpecial()) {
		if (passed_card.get_card_suit() == 'H' || passed_card.get_card_suit() == 'D')
			return true;
		else
			return false;
	}
	
	else if (passed_card.isWild()) {
		for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
			if (!meld_container.at(meld_pos).at(first_pos).isSpecial() && get_wild_cards(meld_pos).size() < 3)
				return true;
		}
	}
	
	else if (passed_card.isNatural()) {
		for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++)
			if (passed_card.get_card_face() == meld_container.at(meld_pos).at(first_pos).get_card_face())
				return true;
	}
	return false;
}





/* *********************************************************************
Function Name: is_meldable
Purpose: Checks if the top of the discard is meldable with the player's hand.
Parameters: passed_card: a Card that is to be checked if it can be melded.
Return Value: bool that represents if the top of the discard can be melded with the hand.
Algorithm: 
			1. check if the passed card has transferred. If so, then it cannot be melded.
			2. If the passed card is special and is a red three, return true. Else, return false. 
			3. If the passed card is wild, and there are two natural cards which have the same face, return true. Otherwise, return false.
			4. Otherwise, since the passed card is natural, check if there's two other cards with the same face in the hand,
				or if there's a wild card in the hand and another card with the same face in the hand. 
				Return true or false based on the criteria above.
Assistance Received: none
********************************************************************* */
bool Hand::is_meldable(Card passed_card) const
{
	int compatible_cards = 0;
	int wild_cards = 0;

	if (passed_card.get_has_transferred())
		return false;

	if (passed_card.isSpecial()) {
		if (passed_card.get_card_suit() == 'H' || passed_card.get_card_suit() == 'D')
			return true;
		else
			return false;
	}

	else if (passed_card.isWild()) {
		for (int card_pos = 0; card_pos < hand_container.size(); card_pos++) {
			for (int smlr_card_pos = 0; smlr_card_pos < hand_container.size(); smlr_card_pos++) {
				if (hand_container.at(smlr_card_pos).get_card_face() == hand_container.at(card_pos).get_card_face())
					compatible_cards++;
				if (compatible_cards >= 2) {
					return true;
				}
			}
		}
		return false;
	}
	else {
		for (int card = 0; card < hand_container.size(); card++) {
			if (hand_container.at(card).isWild())
				wild_cards = wild_cards + 1;
			if (hand_container.at(card).get_card_face() == passed_card.get_card_face())
				compatible_cards++;
		}
		//the first case sees if we can make a meld with 2 naturals and 1 wild, 
		//the second sees if we can make a meld with all natural cards.
		if ((compatible_cards>=1 && wild_cards >= 1) || (compatible_cards >= 2))
			return true;
		else
			return false;
	}
}

/* *********************************************************************
Function Name: remove_from_hand
Purpose: Removes a card from the hand.
Parameters: discarded_card: a Card that represents the card to be discarded
Return Value: bool that represents if the card was found in the hand and erased or not.
Assistance Received: none
********************************************************************* */
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
/* *********************************************************************
Function Name: is_canasta
Purpose: Checks if a meld is a canasta.
Parameters: meld_number: an int representing the position of a meld.
Return Value: bool that represents if the meld at position meld_number is a canasta.
Assistance Received: none
********************************************************************* */
bool Hand::is_canasta(int meld_number) const
{
	if (meld_container.size() < meld_number)
		return false;

	if (meld_container.at(meld_number).size() >= 7)
		return true;
	else
		return false;
}
/* *********************************************************************
Function Name: is_not_duplicate_meld
Purpose: Checks if there already is a meld of a rank/face.
Parameters: rank: a character representing the face of a card to be checked.
Return Value: bool that represents if the rank is a duplicate meld or not.
Assistance Received: none
********************************************************************* */
bool Hand::is_not_duplicate_meld(char rank) const
{
	int first_pos = 0;
	for (std::vector<Card> meld : meld_container) {
		Card first_element = meld.at(first_pos);
		char first_element_rank = first_element.get_card_face();
		if (rank == first_element_rank) {
			return false;
		}
	}
	return true;
}
/* *********************************************************************
Function Name: hand_empty
Purpose: Checks if the hand is empty.
Parameters: none
Return Value: bool that represents if hand is empty or not.
Assistance Received: none
********************************************************************* */
bool Hand::hand_empty() const
{
	bool hand_is_empty = (hand_container.size() == 0) ? true : false;
	return hand_is_empty;
}

/* *********************************************************************
Function Name: has_canasta
Purpose: Checks if in the hand, there is a canasta.
Parameters: none
Return Value: bool that represents if hand has a canasta or not.
Assistance Received: none
********************************************************************* */
bool Hand::has_canasta() const
{
	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		if (is_canasta(meld_pos))
			return true;
	}
	return false;
}
/* *********************************************************************
Function Name: calculate_meld_points
Purpose: Calculates the total points in each meld.
Parameters: meld_number: an int which represents the position of the meld to calculate points from.
Return Value: int that represents the total score in the given meld..
Assistance Received: none
********************************************************************* */
int Hand::calculate_meld_points(int meld_number)
{
	int meld_points = 0;
	std::vector<Card> meld_target = meld_container.at(meld_number);

	for (card_itr card = meld_target.begin(); card != meld_target.end(); card++) {
		meld_points += card->get_point_value();
	}
	return meld_points;
}
/* *********************************************************************
Function Name: print_hand
Purpose: Prints the contents of the hand.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::print_hand() const
{
	for (Card hand_card : hand_container) {
		std::cout << hand_card.get_card_string() << " ";
	}
	std::cout << std::endl;
}

/* *********************************************************************
Function Name: print_melds
Purpose: Prints the contents of the meld container.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::print_melds() const
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
/* *********************************************************************
Function Name: add_hand
Purpose: Adds a card to the hand.
Parameters: card_to_add: A card which will be added to hand.
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::add_to_hand(Card card_to_add)
{
	hand_container.push_back(card_to_add);
}
/* *********************************************************************
Function Name: add_hand
Purpose: Adds an overloaded version of a function which adds several cards to the hand.
Parameters: cards_to_add: a vector of Cards to be added to the hand.
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::add_to_hand(std::vector<Card> cards_to_add)
{
	for (int card_pos = 0; card_pos < cards_to_add.size();card_pos++ ) {
		hand_container.push_back(cards_to_add.at(card_pos));
	}
}

/* *********************************************************************
Function Name: purge_red_threes
Purpose: Removes all red threes from the hand and melds them.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::purge_red_threes()
{
	for (int card_pos = 0; card_pos < hand_container.size(); card_pos++) {
		std::string card_string = hand_container.at(card_pos).get_card_string();
		if (card_string == "3H" || card_string == "3D") {
			Card red_three = hand_container.at(card_pos);
			create_meld(red_three);
		}
	}
}

/* *********************************************************************
Function Name: get_size_of_hand
Purpose: Retrieves the size of the hand container.
Parameters: none
Return Value: int representing the size of the hand container.
Assistance Received: none
********************************************************************* */
int Hand::get_size_of_hand() const
{
	return hand_container.size();
}

/* *********************************************************************
Function Name: get_size_of_meld
Purpose: Retrieves the size of the meld container.
Parameters: none
Return Value: int representing the size of the meld container.
Assistance Received: none
********************************************************************* */
int Hand::get_size_of_meld() const
{
	return meld_container.size();
}

/* *********************************************************************
Function Name: get_card_from_hand
Purpose: Retrieves a card from the hand.
Parameters: pos: an integer representing the position of the card from which to be extracted.
Return Value: int representing the size of the meld container.
Assistance Received: none
********************************************************************* */
Card Hand::get_card_from_hand(int pos) const
{
	return hand_container.at(pos);
}

/* *********************************************************************
Function Name: print_all_wilds_of_meld
Purpose: Retrieves a card from the hand.
Parameters: meld_pos: an integer representing the position of the meld from which to be extracted.
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::print_all_wilds_of_meld(int meld_pos) const
{
	std::vector<Card> wild_meld = meld_container.at(meld_pos);

	int wild_counter = 0;

	for (int meld_pos = 0; meld_pos < wild_meld.size(); meld_pos++)
		if (wild_meld.at(meld_pos).isWild() && wild_meld.at(meld_pos).get_has_transferred()==false) {
			wild_counter++;
			std::cout << wild_counter << ". " << wild_meld.at(meld_pos).get_card_string() << std::endl;
		}
}

/* *********************************************************************
Function Name: get_wilds_cards
Purpose: Retrieves all wild cards from a meld.
Parameters: meld_pos: an integer representing the position of the meld from which to be extracted.
Return Value: vector of Cards representing all the wild cards in a given meld.
Assistance Received: none
********************************************************************* */
std::vector<Card> Hand::get_wild_cards(int meld_pos) const
{
	std::vector<Card> extraction_meld = meld_container.at(meld_pos);
	std::vector<Card> wild_meld;
	for (int meld_pos = 0; meld_pos < extraction_meld.size(); meld_pos++)
		if (extraction_meld.at(meld_pos).isWild() && !(extraction_meld.at(meld_pos).get_has_transferred()))
			wild_meld.push_back(extraction_meld.at(meld_pos));
	return wild_meld;
}

/* *********************************************************************
Function Name: get_wilds_cards
Purpose: Retrieves all wild cards from a meld, except it ignores if the wild cards have been transferred.
Parameters: meld_pos: an integer representing the position of the meld from which to be extracted.
Return Value: vector of Cards representing all the wild cards in a given meld.
Assistance Received: none
********************************************************************* */
std::vector<Card> Hand::get_wild_cards_ignore_transfer(int meld_pos) const
{
	std::vector<Card> extraction_meld = meld_container.at(meld_pos);
	std::vector<Card> wild_meld;
	for (int meld_pos = 0; meld_pos < extraction_meld.size(); meld_pos++)
		if (extraction_meld.at(meld_pos).isWild())
			wild_meld.push_back(extraction_meld.at(meld_pos));
	return wild_meld;
}

/* *********************************************************************
Function Name: get_wild_cards_from_hand
Purpose: Retrieves all wild cards from a the hand.
Parameters: none 
Return Value: vector of Cards representing all the wild cards in the hand container.
Assistance Received: none
********************************************************************* */
std::vector<Card> Hand::get_wild_cards_from_hand() const
{
	std::vector<Card> wild_vector; 

	for (int card_pos = 0; card_pos < hand_container.size(); card_pos++) {
		if (hand_container.at(card_pos).isWild() && hand_container.at(card_pos).get_has_transferred() == false)
			wild_vector.push_back(hand_container.at(card_pos));
	}
	return wild_vector;

}

/* *********************************************************************
Function Name: get_meld
Purpose: Retrieves the meld container.
Parameters: none
Return Value: vector of vectors of cards, representing the meld container.
Assistance Received: none
********************************************************************* */
std::vector<std::vector<Card>> Hand::get_meld() const
{
	return meld_container;
}
/* *********************************************************************
Function Name: get_card_from_meld
Purpose: A card from a meld given a position.
Parameters: 
			  meld_pos, an int representing the meld from which to extract.
			  card_pos, an int representing the position of the card in the meld.
Return Value: A Card representing the card in the meld.
Assistance Received: none
********************************************************************* */
Card Hand::get_card_from_meld(int meld_pos, int card_pos) const
{
	return meld_container.at(meld_pos).at(card_pos);
}

/* *********************************************************************
Function Name: clear_transfer_states
Purpose: Sets the transferred state to false for all cards in a meld.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::clear_transfer_states()
{
	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		std::vector<Card> meld_to_change = meld_container.at(meld_pos);
		for (int card = 0; card < meld_to_change.size(); card++)
			meld_container.at(meld_pos).at(card).set_has_transferred(false);
	}
}
/* *********************************************************************
Function Name: clear_all_data
Purpose: Clears both the hand and meld container.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::clear_all_data()
{
	hand_container.clear();
	meld_container.clear();
}
/* *********************************************************************
Function Name: get_total_score
Purpose: Retrieves the total score for hands and melds. 
Parameters: has_gone_out, a bool representing if the current player has gone out. 
Return Value: an int representing the total score.
Algorithm: 
			1. For each card in the hand, sum up all of its point values. 
			2. For each card in each meld, sum up all of it's point values. 
				If the meld is greater than 7, add a bonus of 500 or 300 depending on if it's an
				all natural meld or a mixed meld (i.e. naturals and wilds). 
			3. Return the difference of the sum of the melds and sum of the hands. 
Local variables: 
					 hand_score_subtraction, an int representing the summation of all of the point value scores in the hand.
					 meld_score_addition, an int representing the summation of all of the point value scores in the meld container.
					 is_natural_meld, a bool representing if a meld is full of all natural cards or not. 
Assistance Received: none
********************************************************************* */
int Hand::get_total_score(bool has_gone_out) const
{
	int hand_score_subtraction = 0;
	int meld_score_addition = 0;
	bool is_natural_meld = true;

	for (int card_pos = 0; card_pos < hand_container.size(); card_pos++)
		hand_score_subtraction += hand_container.at(card_pos).get_point_value();

	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		for (int meld_card_pos = 0; meld_card_pos < meld_container.at(meld_pos).size(); meld_card_pos++) {
			if (meld_container.at(meld_pos).at(meld_card_pos).isWild())
				is_natural_meld = false;
			meld_score_addition += meld_container.at(meld_pos).at(meld_card_pos).get_point_value();
		}
		if (is_natural_meld == true && meld_container.at(meld_pos).size() >= 7)
			meld_score_addition += 500;
		else if (is_natural_meld == false && meld_container.at(meld_pos).size() >= 7)
			meld_score_addition += 300;
	}

	int total_score = meld_score_addition - hand_score_subtraction;

	return (total_score);
}

/* *********************************************************************
Function Name: get_hand_container
Purpose: Retrieves the hand container.
Parameters: none
Return Value: a vector of Cards representing the hand container.
Assistance Received: none
********************************************************************* */
std::vector<Card> Hand::get_hand_container() const
{
	return hand_container;
}

/* *********************************************************************
Function Name: size_of_non_spec_melds
Purpose: Retrieves the size of the non special melds in the meld container.
Parameters: none
Return Value: int representing the size of the non special melds in the meld container.
Assistance Received: none
********************************************************************* */
int Hand::size_of_non_spec_melds() const
{
	int non_spec_meld_counter = 0;
	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		
		if (!meld_container.at(meld_pos).at(0).isSpecial())
		non_spec_meld_counter++;
	}
	return non_spec_meld_counter;
}

/* *********************************************************************
Function Name: set_meld
Purpose: Sets the meld container to another vector of vectors of Cards representing the meld container.
Parameters: meld_container, a vector of vectors of cards representing a meld container.
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::set_meld(std::vector<std::vector<Card>> &meld_container)
{
	this-> meld_container = meld_container;
}

/* *********************************************************************
Function Name: set_hand
Purpose: Sets the meld container to another vector of vectors of Cards representing the meld container.
Parameters: hand_container, a vector of cards representing a hand container.
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::set_hand(std::vector<Card> &hand_container)
{
	this->hand_container = hand_container;
}

/* *********************************************************************
Function Name: meld_exists_already
Purpose: Check if a meld of the given card's face exists already.
Parameters: card_to_search, a Card from which face will be compared against all other melds to see
				if there are duplicates.
Return Value: bool saying that a meld exists already or doesn't.
Assistance Received: none
********************************************************************* */
bool Hand::meld_exits_already(Card card_to_search) const
{
	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		for (int card_pos = 0; card_pos < meld_container.at(meld_pos).size(); card_pos++) {
			if (card_to_search.get_card_face() == meld_container.at(meld_pos).at(card_pos).get_card_face())
				return true;
		}
	}
	return false;
}
/* *********************************************************************
Function Name: get_score_from_meld
Purpose: Get the score from a single meld.
Parameters: meld_pos, representing the meld at which position to total the score.
Return Value: int representing the total score of a meld.
Assistance Received: none
********************************************************************* */
int Hand::get_score_from_meld(int meld_pos) const
{
	int score = 0;
	for (int card_pos = 0; card_pos < meld_container.at(meld_pos).size(); card_pos++) {
		score += meld_container.at(meld_pos).at(card_pos).get_point_value();
	}
	return score;
}
/* *********************************************************************
Function Name: sort
Purpose: sorts the hand container.
Parameters: none.
Return Value: none
Assistance Received: none
********************************************************************* */
void Hand::sort()
{
	std::sort(hand_container.begin(), hand_container.end());
}



