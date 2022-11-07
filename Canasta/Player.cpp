#include "Player.h"
/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */


/* *********************************************************************
Function Name: Player
Purpose: the default constructor for the player class.
Parameters: none.
Return Value: none
Assistance Received: none
********************************************************************* */
Player::Player()
{
	score = 0;
	player_hand;
	has_decided_to_go_out = false;
}

/* *********************************************************************
Function Name: get_score
Purpose: Getter for the score data member.
Parameters: none.
Return Value: int, representing the player's score data member.
Assistance Received: none
********************************************************************* */
int Player::get_score() const
{
	return score;
}
/* *********************************************************************
Function Name: has_canasta
Purpose: Checks if the player has a canasta.
Parameters: none.
Return Value: bool, representing if the player has a canasta or not.
Assistance Received: none
********************************************************************* */
bool Player::has_canasta() const
{
	return player_hand.has_canasta();
}

/* *********************************************************************
Function Name: has_empty
Purpose: Checks if the player has an empty hand.
Parameters: none.
Return Value: bool, representing if the player has an empty hand or not.
Assistance Received: none
********************************************************************* */
bool Player::hand_empty() const
{
	return player_hand.hand_empty();
}
/* *********************************************************************
Function Name: add_to_hand
Purpose: To add a card to the hand by interfacing with the Hand function: add_to_hand 
Parameters: card_to_be_added: a Card, representing which card to add.
Return Value: none.
Assistance Received: none
********************************************************************* */
void Player::add_to_hand(Card card_to_be_added)
{
	player_hand.add_to_hand(card_to_be_added);
}

/* *********************************************************************
Function Name: add_to_hand
Purpose: To add a card to the hand by interfacing with the Hand function: add_to_hand(overloaded for a vector of Cards).
Parameters: cards_to_be_added: a vector of Cards, representing which cards to add
Return Value: none.
Assistance Received: none
********************************************************************* */
void Player::add_to_hand(std::vector<Card> cards_to_be_added)
{
	player_hand.add_to_hand(cards_to_be_added);
}
/* *********************************************************************
Function Name: create_special_meld
Purpose: To create a meld of a red three Card by interfacing with the Hand function: create_meld(overloaded to create a red three meld).
Parameters: cards_to_be_added: a Card representing a red three.
Return Value: none.
Assistance Received: none
********************************************************************* */
bool Player::create_special_meld(Card card_to_be_added)
{
	return player_hand.create_meld(card_to_be_added);
}
/* *********************************************************************
Function Name: create_meld
Purpose: To create a meld of three Cards by interfacing with the Hand function: create_meld(overloaded for a meld of three cards).
Parameters: potential_meld: a vector of Cards representing the potential meld for which to add. 
Return Value: bool, representing if the create meld operation was successful.
Assistance Received: none
********************************************************************* */
bool Player::create_meld(std::vector<Card> potential_meld)
{
	Card meld_card_1 = potential_meld.at(0);
	Card meld_card_2 = potential_meld.at(1);
	Card meld_card_3 = potential_meld.at(2);
	return player_hand.create_meld(meld_card_1, meld_card_2, meld_card_3);

}
/* *********************************************************************
Function Name: create_meld
Purpose: To create a meld of three Cards by interfacing with the Hand function: create_meld(overloaded for a meld of three cards).
Parameters: 
			 first, the first Card that is passed.
			 second, the second Card that is passed.
			 third, the third Card that is passed.
Return Value: bool, representing if the create meld operation was successful.
Assistance Received: none
********************************************************************* */
bool Player::create_meld(Card first, Card second, Card third)
{
	return player_hand.create_meld(first, second, third);
}
/* *********************************************************************
Function Name: purge_red_threes
Purpose: To make all red threes remove themselves from the hand and put them into a meld 
			using the Hand function purge_red_threes.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Player::purge_red_threes()
{
	player_hand.purge_red_threes();
}

/* *********************************************************************
Function Name: lay_off
Purpose: To add a card to a pre-existing meld using the Hand function lay_off.
Parameters: 
			 addition: a Card which is to be added to a pre-existing meld.
			 meld_number: an int representing the meld number from which to add.
Return Value: bool if the operation was successful or not.
Assistance Received: none
********************************************************************* */
bool Player::lay_off(Card addition, int meld_number)
{
	return player_hand.lay_off(addition, meld_number);
}
/* *********************************************************************
Function Name: get_player_hand
Purpose: A getter for the player's hand.
Parameters: none
Assistance Received: none
********************************************************************* */
Hand Player::get_player_hand()  const
{
	return player_hand;
}
/* *********************************************************************
Function Name: sort_hand
Purpose: To sort the player's hand from least to greatest by interfacing
			with the Hand class's function sort().
Parameters: none
Assistance Received: none
********************************************************************* */
void Player::sort_hand()
{
	player_hand.sort();
}
/* *********************************************************************
Function Name: temp_print_hand
Purpose: To print the contents of the hand and melds during a turn, hence the term
			temp, as it's not finalized until the end of the round.
Parameters: none
Assistance Received: none
********************************************************************* */
void Player::temp_print_hand()  const
{
	std::cout << std::endl;
	std::cout << "Your Hand & Melds Information: " << std::endl;
	std::cout << "Hand: "; get_player_hand().print_hand();
	std::cout << "      ";
	for (int i = 0; i < get_player_hand().get_size_of_hand(); i++) {
		std::cout << (i+1);
		if (i+1 <= 9)
			std::cout << "  ";
		else if (i+1 <=99)
			std::cout << " ";
	}
	std::cout << std::endl;
	std::cout << "Melds: ";  get_player_hand().print_melds();
	std::cout << std::endl;

}
/* *********************************************************************
Function Name: transfer_card
Purpose: To transfer wild cards between melds interfacing with the Hand class's function transfer_wild_card.
Parameters: 
			  wild_card: A Card which represents the wild card to be transferred.
			  wild_origin: an int which represents the position of the meld where the wild card originates from
			  meld_number: an int representing the position of the meld which is the wild card's transfer target.
Returns: bool, which represents if the transfer operation was successful or not.
Assistance Received: none
********************************************************************* */
bool Player::transfer_card(Card wild_card, int wild_origin, int meld_number)
{
	return player_hand.transfer_wild_card(wild_card, wild_origin, meld_number);
}

/* *********************************************************************
Function Name: clear_transfer_states
Purpose: To set all the Player's wild card's transfer state to false so they can be transferred the next turn.
Parameters: none
Returns: none
Assistance Received: none
********************************************************************* */
void Player::clear_transfer_states()
{
	player_hand.clear_transfer_states();
}

/* *********************************************************************
Function Name: remove_from_hand
Purpose: To remove a card from the player's hand. 
Parameters: discard_card: the Card from which to be discarded. 
Returns: bool, if the operation was successful.
Assistance Received: none
********************************************************************* */
bool Player::remove_from_hand(Card discard_card)
{
	return player_hand.remove_from_hand(discard_card);
}

/* *********************************************************************
Function Name: clear_hand
Purpose: To completely empty the hand.
Parameters: none
Returns: none
Assistance Received: none
********************************************************************* */
void Player::clear_hand()
{
	player_hand.clear_all_data();
}

/* *********************************************************************
Function Name: can_go_out
Purpose: To return if the player can go out. 
Parameters: none
Returns: bool, saying if the player can go out or not.
Assistance Received: none
********************************************************************* */
bool Player::can_go_out() const
{
	if (player_hand.hand_empty() == true && has_canasta())
		return true;
	else
		return false;
}
/* *********************************************************************
Function Name: add_to_score
Purpose: To add onto a player's score (data member).
Parameters: score_addition: an int from which to add the player's score onto.
Returns: none.
Assistance Received: none
********************************************************************* */
void Player::add_to_score(int score_addition)
{
	score += score_addition;
}
/* *********************************************************************
Function Name: add_to_score
Purpose: To setter a player's score (data member).
Parameters: score: an int from which to set the player's score.
Returns: none.
Assistance Received: none
********************************************************************* */
void Player::set_player_score(int score)
{
	this->score = score;
}
/* *********************************************************************
Function Name: set_meld
Purpose: To setter a player's melds.
Parameters: meld_container: a vector of vectors of Cards representing a player's melds to set to.  
Returns: none.
Assistance Received: none
********************************************************************* */
void Player::set_meld(std::vector<std::vector<Card>> meld_container)
{
	player_hand.set_meld(meld_container);
}
/* *********************************************************************
Function Name: set_hand
Purpose: To setter a player's hand.
Parameters: hand_container: a vector of Cards representing a player's hand to set to.
Returns: none.
Assistance Received: none
********************************************************************* */
void Player::set_hand(std::vector<Card> hand_container)
{
	player_hand.set_hand(hand_container);
}
/* *********************************************************************
Function Name: clear_hand_and_meld
Purpose: Clears both the player's hands and melds.
Parameters: none
Returns: none
Assistance Received: none
********************************************************************* */
void Player::clear_hand_and_meld()
{
	player_hand.clear_all_data();
}
/* *********************************************************************
Function Name: print_vector
Purpose: Prints an arbitrary vector, adding brackets inbetween to represent a meld.
Parameters: vector_to_print: a vector of Cards, representing a meld.
Returns: none
Assistance Received: none
********************************************************************* */
void Player::print_vector(std::vector<Card> vector_to_print)  const
{
	std::cout << "[ ";
		for (Card card : vector_to_print) {
			std::cout << card.get_card_string() << " ";
	}
	std::cout << "] " << std::endl;
}

/* *********************************************************************
Function Name: print_meld
Purpose: Prints a meld in the player's Hand's meld container.
Parameters: meld_pos: an int representing position of the meld to print out.
Returns: none
Assistance Received: none
********************************************************************* */
void Player::print_meld(int meld_pos)  const
{
	Hand player_hand = get_player_hand();
	std::vector<std::vector<Card>> meld_container = player_hand.get_meld();
	print_vector(meld_container.at(meld_pos));
}

/* *********************************************************************
Function Name: sort_melds
Purpose: Sorts a player's melds in ascending order.
Parameters: meld_pos: an int representing position of the meld to print out.
Returns: none
Assistance Received: none
********************************************************************* */
std::vector<std::vector<Card>> Player::sort_melds(std::vector<std::vector<Card>> melds_to_sort) const
{
	int first_card_pos = 0;
	std::sort(melds_to_sort.begin(), melds_to_sort.end(),
		[first_card_pos](const std::vector<Card>& lhs, const std::vector<Card>& rhs) {
			return lhs.at(first_card_pos) > rhs.at(first_card_pos);
		});
	std::sort(melds_to_sort.begin(), melds_to_sort.end(), [](const std::vector<Card>& a, 
		const std::vector<Card>& b) { return (a.size() > b.size() && a.size()<7) ; });
	return melds_to_sort;
}

/* *********************************************************************
Function Name: get_wild_cards_from_vector
Purpose: Get all wild cards from an arbitrary vector of Cards.
Parameters: arbitary_card_vector: an arbitrary vector from which wild cards are to be extracted from.
Returns: a vector of Cards, representing all the wild cards in a vector.
Assistance Received: none
********************************************************************* */
std::vector<Card> Player::get_wild_cards_from_vector(std::vector<Card> arbitrary_card_vect)  const
{
	std::vector<Card> vector_of_wild_cards; 
	for (int card_pos = 0; card_pos < arbitrary_card_vect.size(); card_pos++) {
		if (arbitrary_card_vect.at(card_pos).isWild() && arbitrary_card_vect.at(card_pos).get_has_transferred() == false) {
			vector_of_wild_cards.push_back(arbitrary_card_vect.at(card_pos));
		}
	}
	return vector_of_wild_cards;
}
/* *********************************************************************
Function Name: meld_of_card_exists
Purpose: Check if there's a meld of the card passed that matches the face of said card.
Parameters: card_to_search, a Card to compare against all the player's melds.
Returns: a bool, representing if a meld of the card searched already exists.
Assistance Received: none
********************************************************************* */
bool Player::meld_of_card_exists(Card card_to_search)  const
{
	return player_hand.meld_exits_already(card_to_search);
}
/* *********************************************************************
Function Name: meld_of_card_exists
Purpose: Get an absolute position in the unsorted vector of melds given a vector that has been found.
Parameters: arbitrary_meld_vect, a vector of Cards representing the meld to search.
Returns: a int, representing the absolute position of the passed vector in the current melds.
Assistance Received: none
********************************************************************* */
int Player::get_absolute_pos_from_relative_meld(std::vector<Card> arbitrary_meld_vect)  const
{
	int first_element = 0; 
	int error_pos = -999;
	Hand player_hand = get_player_hand();
	std::vector<std::vector<Card>> meld_container = player_hand.get_meld();
	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		if (arbitrary_meld_vect.at(first_element) == meld_container.at(meld_pos).at(first_element))
			return meld_pos;
	}
	return -error_pos;

}



/* *********************************************************************
Function Name: get_go_out_decision
Purpose: Retrieve the has_decided_to_go_out data member.
Parameters: none
Returns: a bool representing the data member has_decided_to_go_out.
Assistance Received: none
********************************************************************* */
bool Player::get_go_out_decision() const
{
	return has_decided_to_go_out;
}

/* *********************************************************************
Function Name: set_go_out_decision
Purpose: A setter for has_decided_to_go_out data member.
Parameters: go_out_decision: a bool representing what to set the data member
				has_decided_to_go_out as.
Returns: none
Assistance Received: none
********************************************************************* */
void Player::set_go_out_decision(bool go_out_decision)
{
	has_decided_to_go_out = go_out_decision;
}
/* *********************************************************************
Function Name: go_out
Purpose: To return if the player has decided to go out.
Parameters: none
Returns: bool, representing if the player has decided to go out
Assistance Received: none
********************************************************************* */
bool Player::go_out()
{
	bool able_to_go_out = can_go_out();
	bool did_chose_to_go_out = false;
	if (able_to_go_out) {
		did_chose_to_go_out = choose_to_go_out();

		if (did_chose_to_go_out) {
			set_go_out_decision(true);
		}
	}
	return did_chose_to_go_out;
}

/* *********************************************************************
Function Name: get_dangerous_amount_of_cards
Purpose: To gather the amount of how many cards, if discarded, will give the enemy a canasta.
Parameters: enemy_melds, a vector of vectors of Cards representing the enemy's melds. 
Returns: int, representing how many cards, if discarded, will give the enemy a canasta.
Assistance Received: none
********************************************************************* */
int Player::get_dangerous_amount_of_cards(std::vector<std::vector<Card>> enemy_melds) const
{
	int first_position = 0;
	Hand player_hand = get_player_hand();
	int amount_of_dangerous_cards = 0;
	std::vector<Card> hand_container = player_hand.get_hand_container();
	for (int card_pos = 0; card_pos < hand_container.size(); card_pos++) {
		for (int meld_pos = 0; meld_pos < enemy_melds.size(); meld_pos++) {
			if (hand_container.at(card_pos).get_card_face() == 
			enemy_melds.at(meld_pos).at(first_position).get_card_face()
			&&enemy_melds.at(meld_pos).size()==6) {
				amount_of_dangerous_cards++;
			}
		}
	}
	return amount_of_dangerous_cards;
}

/* *********************************************************************
Function Name: is_dangerous_card
Purpose: To gather the amount of how many cards, if discarded, will give the enemy a canasta.
Parameters: 
			  potential_danger_card, a Card which is to be checked if it is "dangerous", see above.
			  enemy_melds, a vector of vectors of Cards representing the enemy's melds. 
Returns: bool, representing if the Card passed if discarded, will give the enemy a canasta.
Assistance Received: none
********************************************************************* */
bool Player::is_dangerous_card(Card potential_danger_card, std::vector<std::vector<Card>> enemy_melds) const
{
	int first_pos = 0;
	for (int meld_pos = 0; meld_pos < enemy_melds.size(); meld_pos++) {
		if (potential_danger_card.get_card_face() == enemy_melds.at(meld_pos).at(first_pos).get_card_face())
			return true;
	}
	return false;
}
/* *********************************************************************
Function Name: meld
Purpose: The Computer's strategy regarding the meld phase.
Parameters:
			 draw_decks: a Deck reference which represents the discard and stock pile from the Round.
			 enemy_melds: a vector of vectors of Card which represents the enemy's melds.
Algorithm:
			1. The computer will consider first if any of the cards in its hand can be made as a
				canasta when discarded to the enemy (i.e. enemy has 6 4s then it’ll hold onto a 4).
				If it sees this, it’ll play more conservatively, holding onto cards in its hand
				by restricting the total number of cards laid off per meld by the size of dangerous cards.
				So if the CPU has a hand of 5, it’ll always keep 2 cards, except for natural melds.
			2. The computer will first make a copy of unique faces in the hand.
				Then, it’ll see how many cards are there that make up that unique face(if they are natural).
				If the face is already in a pre-existing meld, it’ll search and find the meld, and add onto it.
				If not, if the cards found are greater than 3, it’ll create a meld. If there’s two natural cards, save for later,
				as they can be potentially melded with a wild card. If there’s just one, see if it can be laid off
				(this might be removed for redundancy purposes).
			3. Then, the cards that have a potential to be melded with wild cards are sorted in ascending order.
				Each pair is melded with a vector of wild cards, while both aren’t empty. When choosing to meld with wild cards,
				it’ll choose the meld with the highest score.
			4. Afterward, the CPU will sort a temporary vector of vectors of the meld container by size,
				and decide by the order of size which melds are best to lay off wild cards.
			5. Afterward, if the CPU sees that a meld can be made as a canasta through transferring wildcards,
				it’ll do so from extracting wild cards from other melds greater than the size of 3, but less than a size of 7.
			6. If the CPU did none of the aforementioned strategies above,
				it’ll say it did nothing, also stating if this decision was due to seeing a
				dangerous card(a card that if discarded will give the enemy a canasta) in it’s hand.


Local variables:
			player_hand: a Hand representing the player's hand and melds.
			hand_container: a vector of Cards representing the player's hand.
			meld_container: a vector of Cards representing the player's melds.
			no_duplicate_card: a vector of Cards representing all unique cards in the player's hand.
			unique_faces: a vector of Cards representing all unique faces derived from no_duplicate_card.
			natural_meld_vector: a vector of Cards which represents all natural cards in the Hand.
			can_meld_with_wild: a vector of Cards which represents a pair of two Cards with the same face.
			wild_cards_in_hand: a vector of Cards which represents all the wild cards in a player's hand.
			transfer_to_hand: an int representing the option to transfer a card to a player's hand.
			amount_of_dangerous_cards: an int representing how many cards there are in the Computer's hand, if discarded,
			will give the enemy a free canasta.
			has_done_action: a bool representing if the Computer has melded, added to a meld, or transferred wild cards.
			first_card, second_card, third_card: Cards representing the 1st, 2nd, and 3rd card in a meld.
			first_nat_card... third_nat_card: Cards representing the 1st, 2nd, and 3rd natural cards in a meld.
			can_meld_to_canasta_sum: the sum needed to get a canasta, gained by gathering the size of the meld plus 3 minus the wild cards
				in the meld, so to see if it can be transferred.
			min_for_canasta: an int representing the minimum size a meld has to be to be a canasta (7).
			meld_already_exists: a bool representing if a meld of a particular Card's face already exists.
			meld_to_extract_wilds: a vector of Cards representing the meld in particular, to extract wild cards from to transfer cards to another meld.
			absolute_meld_pos: the absolute value of the position of a particular meld with respect to the unsorted meld container in the Player's Hand.
			wild_to_transfer: The meld at which the wild cards should be transferred from.
			meld: a vector of Cards representing a single meld within an iteration over the meld_container.
			extracted_face: the face extracted from a Card to see if there is a meld that already exists in meld_container.
			card_pos: an int which represents the position of a first Card in a potential meld.
			second_card_pos: an int which represents the position of a second Card in a potential meld.
			wild_pos: an int which represents the position of a wild card in a given meld or hand.

Return Value: none.
Assistance Received: Particulary in regards to unique and adding in an inaxproimate amount of cards, I used the following:
	//https://cplusplus.com/reference/iterator/back_inserter/
	//https://stackoverflow.com/questions/52150939/cant-dereference-value-initialized-iterator
********************************************************************* */
void Player::strategy_meld(std::vector<std::vector<Card>> enemy_melds, std::string plr_type)
{
	Hand player_hand = get_player_hand();
	std::vector<Card> hand_container = player_hand.get_hand_container();
	std::vector<std::vector<Card>> meld_container = player_hand.get_meld();
	std::vector<Card> no_duplicate_cards;
	std::vector<Card> unique_faces;
	std::vector<Card> natural_meld_vector;
	std::vector<Card> can_meld_with_wild;
	std::vector<Card> wild_cards_in_hand = player_hand.get_wild_cards_from_hand();
	//because of user input, the option to transfer to the hand is -2. 
	int transfer_to_hand = -2;
	int amount_of_dangerous_cards = get_dangerous_amount_of_cards(enemy_melds);

	if (amount_of_dangerous_cards > 0) {
		if (plr_type == "Computer") {
			std::cout << "The CPU sees that one of its cards if discarded will give the enemy make a canasta, so it's playing more conservatively..."
				<< std::endl;
		}
		else if (plr_type == "Human") {
			std::cout << "You ought to play more conservatively, as if you discard a certain card, you'll give your opponent a canasta. " << std::endl;
		}
	}


	bool has_done_action = false;



	//first, remove the duplicate cards.

	std::unique_copy(hand_container.begin(), hand_container.end(), std::back_inserter(no_duplicate_cards));


	if ((has_canasta() && hand_container.size() < 6)) {
		for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
			if ((meld_container.at(meld_pos).size() < 7 && meld_container.at(meld_pos).size() > 3)
				|| meld_container.at(meld_pos).size() > 7) {
				std::vector<Card> wild_transfer_meld = player_hand.get_wild_cards(meld_pos);
				for (int wild_pos = 0; wild_pos < wild_transfer_meld.size(); wild_pos++) {
					if (player_hand.is_meldable(wild_transfer_meld.at(wild_pos))) {
						if (plr_type == "Computer") {
							std::cout << "The CPU decided to transfer the wild card " <<
								wild_transfer_meld.at(wild_pos).get_card_string() << " to the hand from meld " << wild_pos << ": ";
							print_meld(wild_pos);
							std::cout << "since it is quite eager to get rid of the cards out of it's hand to go out." << std::endl;
						}
						else if (plr_type == "Human") {
							std::cout << "Transfer the wild card " <<
								wild_transfer_meld.at(wild_pos).get_card_string() << " to the hand from meld " << wild_pos << ": ";
							print_meld(wild_pos);
							std::cout << "since you can use this strategy to get rid of cards out of your hand to go out." << std::endl;
						}
						transfer_card(wild_transfer_meld.at(wild_pos), meld_pos, -2);
						has_done_action = true;
					}
				}
			}
		}
	}
	player_hand = get_player_hand();
	wild_cards_in_hand = player_hand.get_wild_cards_from_hand();





	//then, make sure we only represent each card of one face, no wild cards or special cards.
	for (int card_pos = 0; card_pos < no_duplicate_cards.size(); card_pos++) {
		Card extracted_card = no_duplicate_cards.at(card_pos);
		if ((!extracted_card.isWild() && !extracted_card.isSpecial())) {
			bool is_unique = true;
			for (int unique_card_pos = 0; unique_card_pos < unique_faces.size(); unique_card_pos++) {
				if (extracted_card.get_card_face() == unique_faces.at(unique_card_pos).get_card_face())
					is_unique = false;
			}
			if (is_unique)
				unique_faces.push_back(no_duplicate_cards.at(card_pos));
		}
	}

	//check the hand for each of these unique faces. Tally up the total of natural cards
	//with the same rank. If 3 or higher, it'll meld. If more than 4, it'll lay off the rest.
	for (int card_pos = 0; card_pos < unique_faces.size(); card_pos++) {
		char face_to_search_for = unique_faces.at(card_pos).get_card_face();
		player_hand = get_player_hand();
		hand_container = player_hand.get_hand_container();
		meld_container = player_hand.get_meld();
		for (int hand_c_pos = 0; hand_c_pos < hand_container.size(); hand_c_pos++) {

			Card card_from_hand = hand_container.at(hand_c_pos);
			char extracted_face = card_from_hand.get_card_face();
			if (extracted_face == face_to_search_for && (!card_from_hand.isWild() && !card_from_hand.isSpecial())) {
				natural_meld_vector.push_back(card_from_hand);
			}
		}

		bool meld_already_exists = false;

		//if the natural meld vector is greater than 0.
		if (natural_meld_vector.size() > 0) {
			meld_already_exists = meld_of_card_exists(natural_meld_vector.at(0));
		}

		else {
			meld_already_exists = false;
		}
		//prevent an underflow, also 3 is the min needed for a canasta.
		if (natural_meld_vector.size() >= 3 && !meld_already_exists &&
			((int)hand_container.size() - amount_of_dangerous_cards > 0) &&
			!is_dangerous_card(natural_meld_vector.at(0), enemy_melds)) {
			Card first_card = natural_meld_vector.at(0);
			Card second_card = natural_meld_vector.at(1);
			Card third_card = natural_meld_vector.at(2);
			create_meld(first_card, second_card, third_card);
			player_hand = get_player_hand();

			//to prevent an underflow.
			for (int lay_off_pos = 3; lay_off_pos < (int)natural_meld_vector.size() - amount_of_dangerous_cards; lay_off_pos++) {
				lay_off(natural_meld_vector.at(lay_off_pos), player_hand.get_size_of_meld() - 1);
				has_done_action = true;
			}
			if (plr_type == "Computer") {
				std::cout << "The CPU decided to meld the following cards: ";
				print_vector(natural_meld_vector);
				std::cout << " as they were an all natural meld, and getting rid of natural cards is generally advantageous." << std::endl;
			}
			else if (plr_type == "Human") {
				std::cout << "Meld the following cards: ";
				print_vector(natural_meld_vector);
				std::cout << " as this is an all natural meld, and getting rid of natural cards is generally advantageous." << std::endl;
			}
		}
		else if (natural_meld_vector.size() == 2 && !meld_already_exists) {
			Card first_card = natural_meld_vector.at(0);
			Card second_card = natural_meld_vector.at(1);

			can_meld_with_wild.push_back(first_card);
			can_meld_with_wild.push_back(second_card);

		}

		else if (meld_already_exists) {
			for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
				if (natural_meld_vector.at(0).get_card_face() == meld_container.at(meld_pos).at(0).get_card_face()) {

					int loop_size = natural_meld_vector.size();

					for (int lay_off_pos = 0; lay_off_pos < loop_size; lay_off_pos++) {
						has_done_action = true;
						lay_off(natural_meld_vector.at(lay_off_pos), meld_pos);

						if (plr_type == "Computer") {
							std::cout << "The CPU decided to add to a pre-existing meld using the following card(s): ";
							print_vector(natural_meld_vector);
							std::cout << " as they were all natural card(s), and getting rid of natural card(s) is always advantageous." << std::endl;
						}

						else if (plr_type == "Human") {
							std::cout << "Add to a pre-existing meld using the following card(s): ";
							print_vector(natural_meld_vector);
							std::cout << " as they were all natural cards(s) , and getting rid of natural card(s) is always advantageous." << std::endl;
						}
					}
				}
			}
		}


		natural_meld_vector.clear();
	}

	std::sort(can_meld_with_wild.begin(), can_meld_with_wild.end(),
		[](const Card& lhs, const Card& rhs) -> bool { return lhs > rhs; });


	//to prevent an underflow.
	while (can_meld_with_wild.size() != 0 && (int)wild_cards_in_hand.size() - amount_of_dangerous_cards > 0) {
		int card_pos = 0;
		int second_card_pos = 1;
		int wild_pos = 0;

		Card first_nat_card = can_meld_with_wild.at(card_pos);
		Card second_nat_card = can_meld_with_wild.at(second_card_pos);
		Card third_wild_card = wild_cards_in_hand.at(wild_pos);

		bool meld_already_exists = false;

		//it is inevitable duplicates from the natural meld vector will exist. Therefore, we need to 
		//ensure they are not melded.
		if (can_meld_with_wild.size() > 0) {
			meld_already_exists = meld_of_card_exists(can_meld_with_wild.at(0));
		}

		else {
			meld_already_exists = false;
		}


		if (!meld_already_exists) {
			if (plr_type == "Computer") {
				std::cout << "The CPU decided to meld: ";
				print_vector(std::vector < Card >{first_nat_card, second_nat_card, third_wild_card});
				std::cout << " as the two natural cards(ordered in highest order of points) can meld with a wild card. " << std::endl;
			}
			else if (plr_type == "Human") {
				std::cout << "Meld the following: ";
				print_vector(std::vector < Card >{first_nat_card, second_nat_card, third_wild_card});
				std::cout << " as the two natural cards(ordered in highest order of points) can meld with a wild card. " << std::endl;
			}
			create_meld(first_nat_card, second_nat_card, third_wild_card);
			has_done_action = true;
		}
		//delete the pair at the beginning of the vector
		can_meld_with_wild.erase(can_meld_with_wild.begin() + card_pos);
		can_meld_with_wild.erase(can_meld_with_wild.begin() + card_pos);

		//since the cards are in pairs.
		player_hand = get_player_hand();
		wild_cards_in_hand = player_hand.get_wild_cards_from_hand();
	}

	player_hand = get_player_hand();
	wild_cards_in_hand = player_hand.get_wild_cards_from_hand();
	meld_container = player_hand.get_meld();

	meld_container = sort_melds(meld_container);
	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		player_hand = get_player_hand();
		wild_cards_in_hand = player_hand.get_wild_cards_from_hand();
		meld_container = player_hand.get_meld();
		meld_container = sort_melds(meld_container);
		int absolute_meld_pos = get_absolute_pos_from_relative_meld(meld_container.at(meld_pos));
		std::vector<Card> wild_cards_from_meld = player_hand.get_wild_cards_ignore_transfer(absolute_meld_pos);

		if (meld_container.at(meld_pos).size() >= 3 && wild_cards_from_meld.size() <= 3) {

			//prevent an underflow error.
			while ((((int)wild_cards_in_hand.size() - amount_of_dangerous_cards) > 0) && wild_cards_from_meld.size() < 3) {

				absolute_meld_pos = get_absolute_pos_from_relative_meld(meld_container.at(meld_pos));
				has_done_action = true;

				if (plr_type == "Computer") {
					std::cout << "The CPU chose to lay off the card " << wild_cards_in_hand.at(0).get_card_string() <<
						" because the meld chose, ";
					print_vector(meld_container.at(meld_pos));
					std::cout << " had the highest size(<7) and less than 3 wild cards, so it prioritized it." << std::endl;
				}

				else if (plr_type == "Human") {
					std::cout << "Add this card to a pre-existing meld " << wild_cards_in_hand.at(0).get_card_string() <<
						" because the meld shown, ";
					print_vector(meld_container.at(meld_pos));
					std::cout << " had the highest size(<7) and less than 3 wild cards, so you ought to prioritize it." << std::endl;
				}

				lay_off(wild_cards_in_hand.at(0), absolute_meld_pos);



				player_hand = get_player_hand();
				wild_cards_in_hand = player_hand.get_wild_cards_from_hand();
				wild_cards_from_meld = player_hand.get_wild_cards_ignore_transfer(absolute_meld_pos);
			}
		}
	}
	player_hand = get_player_hand();
	meld_container = player_hand.get_meld();

	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		std::vector<Card> meld = meld_container.at(meld_pos);
		int can_meld_to_canasta_sum = meld.size() + 3 - get_wild_cards_from_vector(meld).size();
		int min_for_canasta = 7;
		bool has_transferred = false;
		player_hand = get_player_hand();
		meld_container = player_hand.get_meld();
		if (can_meld_to_canasta_sum >= min_for_canasta && (meld.size() < 6 && meld.size() > 3) && !has_canasta()) {
			int other_melds_pos = (meld_pos == meld_container.size() - 1) ? 0 : meld_pos + 1;
			while (other_melds_pos != meld_pos) {

				player_hand = get_player_hand();
				meld_container = player_hand.get_meld();


				std::vector<Card> meld_to_extract_wilds = meld_container.at(other_melds_pos);
				if (meld_to_extract_wilds.size() > 3) {
					std::vector<Card> wild_to_transfer = player_hand.get_wild_cards(other_melds_pos);
					while (wild_to_transfer.size() != 0 && meld_to_extract_wilds.size() > 3) {
						has_done_action = true;
						if (plr_type == "Computer") {
							std::cout << "CPU decided to transfer card " << wild_to_transfer.at(0).get_card_string() <<
								" from meld: ";  print_meld(other_melds_pos);
							std::cout << "As meld: "; print_meld(meld_pos);
							std::cout << " can be made as a Canasta with just a few more wildcards." << std::endl;
						}

						else if (plr_type == "Human ") {
							std::cout << "Transfer card " << wild_to_transfer.at(0).get_card_string() <<
								" from meld: ";  print_meld(other_melds_pos);
							std::cout << "As meld: "; print_meld(meld_pos);
							std::cout << " can be made as a Canasta with just a few more wildcards." << std::endl;
						}

						transfer_card(wild_to_transfer.at(0), other_melds_pos, meld_pos);
						player_hand = get_player_hand();
						meld_container = player_hand.get_meld();
						meld_to_extract_wilds = meld_container.at(other_melds_pos);
						wild_to_transfer.erase(wild_to_transfer.begin());
					}
				}

				player_hand = get_player_hand();
				meld_container = player_hand.get_meld();

				if (other_melds_pos == meld_container.size() - 1)
					other_melds_pos = 0;
				else
					other_melds_pos++;
			}
		}
	}



	if (!has_done_action && amount_of_dangerous_cards == 0) {
		if (plr_type=="Computer")
			std::cout << "The CPU decided to do nothing, since it can't do any actions regarding melding." << std::endl;
		else if (plr_type=="Human") 
			std::cout << "End your meld phase. You can't meld anything." << std::endl;
	}

	else if (amount_of_dangerous_cards > 0 && !has_done_action) {
		if (plr_type == "Computer")
			std::cout << "The CPU decided to do nothing, since it would rather do nothing than give a free canasta to the enemy." << std::endl;
		else if (plr_type == "Human")
			std::cout << "End your meld phase, otherwise you'd risk giving a free canasta to the enemy." << std::endl;

	}






	sort_hand();



}


/* *********************************************************************
Function Name: draw
Purpose: The Computer's strategy regarding the draw phase.
Parameters:
			 draw_decks: a Deck reference which represents the discard and stock pile from the Round.
			 enemy_melds: a vector of vectors of Card which represents the enemy's melds.
Algorithm:
			1. If the CPU sees that the first card of the discard pile is meldable,
			as well as the discard pile isn’t frozen, and that the CPU has a hand size greater than 5, it’ll draw from the discard pile.
			2. If none of the above are true and the stock pile is empty, it’ll draw from the stock pile.
			3. Otherwise, it’ll concede, saying it can’t draw from either piles, hence the game is over.
Local variables:
			player_hand: a Hand representing the player's hand for comparisons.
			top_of_discard: A Card representing the top of the discard pile for which the Computer to see if it can draw from there.
			can_meld: a bool which represents if the top of the discard pile is meldable with the hand.
			can_meld_with_melds: a bool which represents if the top of the discard pile is meldable with the Computer's melds.
			hand_is_not_small: a bool which represents if the hand is greater than 5 or not.
			picked_up_discard: a vector of Cards which represents the discard pile being picked up after being drawn.
Return Value: bool, representing if the game should end immeadiately if the Computer cannot draw.
Assistance Received: none
********************************************************************* */
bool Player::strategy_draw(Deck& draw_decks, std::string plr_type)
{
	Hand player_hand = get_player_hand();
	Card top_of_discard = draw_decks.get_top_discard_pile();
	bool can_meld = player_hand.is_meldable(top_of_discard);
	bool can_meld_with_melds = player_hand.is_meldable_with_melds(top_of_discard);
	bool hand_is_not_small = (((int)player_hand.get_size_of_hand() > 5));

	if (((can_meld || can_meld_with_melds) && ((!has_canasta() || ((has_canasta()) && (hand_is_not_small))))
		&& (!draw_decks.get_discard_is_frozen()))) {
		if (plr_type == "Computer") {
			std::cout << "CPU: drawing discard pile: can meld with hand or add onto melds, hand isn't that small." << std::endl;
			std::vector<Card> picked_up_discard = draw_decks.draw_from_discard();
			add_to_hand(picked_up_discard);
			purge_red_threes();
		}
		else if (plr_type == "Human")
			std::cout << "I'd suggest drawing from the discard pile: you can meld with hand or add onto melds, and your hand isn't that small." << std::endl;
		return false;
	}

	else if (!draw_decks.stock_is_empty()) {
		if (plr_type == "Computer")
			std::cout << "CPU: drawing from stock, because: ";
		else if (plr_type == "Human")
			std::cout << "I'd suggest you draw from stock, because: ";

		if (draw_decks.get_discard_is_frozen())
			std::cout << "the discard pile is frozen." << std::endl;
		else if (!can_meld) {
			if (plr_type == "Computer")
				std::cout << "there are no cards in the CPU's hand that can meld with the card " << top_of_discard.get_card_string() << std::endl;
			else if (plr_type == "Human")
				std::cout << "there are no cards in the your hand that can meld with the card " << top_of_discard.get_card_string() << std::endl;

		}
		else {
			if (plr_type == "Computer")
				std::cout << "The bot wants to keep a small hand, so it can go out soon." << std::endl;
			else if (plr_type == "Human")
				std::cout << "You should keep a small hand, so that you can go out soon." << std::endl;

		}


		if (plr_type == "Computer") {
			Card drawn_card;
			do {
				drawn_card = draw_decks.draw_from_stock();
				add_to_hand(drawn_card);
				purge_red_threes();
			} while (drawn_card.is_red_three() && !draw_decks.stock_is_empty());
		}


		return false;
	}

	else {
		if (plr_type == "Computer")
			std::cout << "The stock pile is empty and the CPU can't draw from the discard pile. It concedes!" << std::endl;
		else if (plr_type == "Human")
			std::cout << "You can't do much but wait and let the game end since the stock pile is empty and the discard pile is empty..." << std::endl;
		return true;
	}


}

/* *********************************************************************
Function Name: discard
Purpose: The Computer's strategy regarding the discard phase.
Parameters:
			 draw_decks: a Deck reference which represents the discard and stock pile from the Round.
			 enemy_melds: a vector of vectors of Card which represents the enemy's melds.
Algorithm:
			1. First, the CPU will create a vector of all cards that aren’t in the enemy’s melds,
				as well as a list of all cards that aren’t wild cards, based on a sorted hand from least to greatest points.
			2. Then, it’ll see if the top of the discard is in the enemy’s melds.
				If so, it’ll check if it has a 3 of spades or clubs, and discard that.
			3. Otherwise, it’ll attempt to discard from the vector of all cards that aren’t in enemy’s melds.
			4. Otherwise, it’ll attempt to discard cards that aren’t wild cards.
			5. Otherwise, it’ll attempt to discard a card at the lowest point value in the hand.
			6. Finally, if there’s nothing to discard, it’ll skip the discard turn.

Local variables:
			preference_discard: a vector of Cards representing what the Computer has the top preference to discard,
			i.e. the cards that are not in the enemy's melds.
			not_in_melds_but_wilds: a vector of Cards representing what the Computer has in terms of wild cards.
			no_wild_discard; a vector of Cards that is all natural cards, regardless of if they're in the enemy's melds.
			player_hand: a Hand representing the player's hand for comparisons.
			hand_container: a vector of Cards' representing the Computer's hand.
			card_to_search: the Card to be searched for if it's in the enemy's melds.
			preferred_card: the Card that is the most preferred to be discarded.
			first_card_pos: the first position in all vectors, particularly ones containing cards.
			has_discarded_three: a bool representing if the Computer already chose to discard a three.
			three_spades_itr: an iterator representing if the Computer found a three of spades in it's hand.
			three_clubs_itr: an iterator representing if the Computer found a three of clubs in it's hand.

Return Value: none.
Assistance Received: none
********************************************************************* */
void Player::strategy_discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds, std::string plr_type)
{
	std::vector<Card> preference_discard;
	std::vector<Card> not_in_melds_but_wilds;
	std::vector<Card> no_wild_discard;
	Hand player_hand = get_player_hand();
	//makes comparisons a lot easier.
	player_hand.sort();
	std::vector<Card> hand_container = player_hand.get_hand_container();
	Card preferred_card;
	int first_card_pos = 0;

	auto three_spades_itr = std::find(hand_container.begin(), hand_container.end(), Card("3S"));
	auto three_clubs_itr = std::find(hand_container.begin(), hand_container.end(), Card("3C"));

	for (int card_pos = 0; card_pos < hand_container.size(); card_pos++) {
		Card card_to_search = hand_container.at(card_pos);
		bool should_add = true;
		for (int meld_pos = 0; meld_pos < enemy_melds.size(); meld_pos++) {
			//checks for the first card. Due to the way I set up melding, it'll never
			//be able to have a wild card be the first card in a meld.
			if (card_to_search.get_card_face() == enemy_melds.at(meld_pos).at(0).get_card_face()) {
				should_add = false;
			}
		}

		if (should_add == true) {
			if (!card_to_search.isWild() && !card_to_search.isSpecial())
				preference_discard.push_back(card_to_search);
			else {
				not_in_melds_but_wilds.push_back(card_to_search);
			}
		}



		if (!card_to_search.isWild()) {
			no_wild_discard.push_back(card_to_search);
		}


	}

	Card top_of_discard = draw_decks.get_top_discard_pile();
	bool has_discarded_three = false;
	for (int meld_pos = 0; meld_pos < enemy_melds.size(); meld_pos++) {
		if (top_of_discard.get_card_face() == enemy_melds.at(meld_pos).at(first_card_pos).get_card_face()) {
			if (three_spades_itr != hand_container.end()) {
				preferred_card = *three_spades_itr;
				draw_decks.discard_push_front(*three_spades_itr);
				remove_from_hand(*three_spades_itr);
				if (plr_type == "Computer") {
					std::cout << "The CPU chose to get rid of 3S since it sees the top of the discard, "
						<< top_of_discard.get_card_string() << " is in the enemy meld: "; print_meld(meld_pos);
					std::cout << std::endl;
				}

				else if (plr_type == "Human") {
					std::cout << "You should get rid of 3S since the top of the discard, "
						<< top_of_discard.get_card_string() << " is in the enemy meld: "; print_meld(meld_pos);
					std::cout << std::endl;
				}
				has_discarded_three = true;
				break;
			}


			else if (three_clubs_itr != hand_container.end()) {
				preferred_card = *three_clubs_itr;
				draw_decks.discard_push_front(*three_clubs_itr);
				remove_from_hand(*three_clubs_itr);
				
				if (plr_type == "Computer") {
					std::cout << "The CPU chose to get rid of 3C since it sees the top of the discard, "
						<< top_of_discard.get_card_string() << " is in the enemy meld: "; print_meld(meld_pos);
					std::cout << std::endl;
				}

				else if (plr_type == "Human") {
					std::cout << "You should get rid of 3C since the top of the discard, "
						<< top_of_discard.get_card_string() << " is in the enemy meld: "; print_meld(meld_pos);
					std::cout << std::endl;
				}

				has_discarded_three = true;
				break;
			}
		}
	}



	if (preference_discard.size() != 0 && !has_discarded_three) {
		preferred_card = preference_discard.at(0);

		if (plr_type == "Computer") {
			std::cout << "The CPU chose to get rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
				"In the CPU's hand, @" << preferred_card.get_point_value() << " points, and is not in any of the enemy's melds, and wasn't a wild card." << std::endl;
		}
		else if (plr_type == "Human") {
			std::cout << "You should get rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
				"In the your hand hand, @" << preferred_card.get_point_value() << " points, and is not in any of the enemy's melds, and wasn't a wild card." << std::endl;
		}
	}

	else if (not_in_melds_but_wilds.size() != 0 && !has_discarded_three) {
		preferred_card = not_in_melds_but_wilds.at(0);
		if (plr_type == "Computer") {
			std::cout << "The CPU chose to get rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
				"In the CPU's hand, @" << preferred_card.get_point_value() << " points, and wasn't in an enemy meld." << std::endl;
		}
		else if (plr_type == "Human") {
			std::cout << "You should get rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
				"In the your hand, @" << preferred_card.get_point_value() << " points, and wasn't in an enemy meld." << std::endl;
		}
	}

	else if (no_wild_discard.size() != 0 && !has_discarded_three) {
		preferred_card = no_wild_discard.at(0);

		if (plr_type == "Computer") {
			std::cout << "The CPU chose to get rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
				"In the CPU's hand, @" << preferred_card.get_point_value() << " points, and wasn't a wild card." << std::endl;
		}

		else if (plr_type == "Human") {
			std::cout << "You should  rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
				"In the your hand, @" << preferred_card.get_point_value() << " points, and wasn't a wild card." << std::endl;
		}

		//https://stackoverflow.com/questions/44576857/randomly-pick-from-a-vector-in-c

	}
	else if (hand_container.size() != 0 && !has_discarded_three) {
		preferred_card = hand_container.at(0);
		if (plr_type == "Computer")
			std::cout << "The CPU had no choice, so it got rid of it's lowest value card, which ended up being: " << preferred_card.get_card_string() << std::endl;
		else if (plr_type == "Human")
			std::cout << "You don't have much of a chose, so get rid of the lowest value card, which ended up being: " << preferred_card.get_card_string() << std::endl;
	}
	else if (!has_discarded_three) {
		if (plr_type == "Computer")
			std::cout << "The CPU has nothing to discard, so it didn't." << std::endl;
		else if (plr_type == "Human")
			std::cout << "You have nothing to discard, so you'll skip your turn." << std::endl;
		return;
	}

	if (plr_type == "Computer") {
		if (preferred_card.isWild() || preferred_card.isSpecial()) {
			draw_decks.set_discard_freeze(true);
		}

		else {
			draw_decks.set_discard_freeze(false);
		}

	
		draw_decks.discard_push_front(preferred_card);
		remove_from_hand(preferred_card);
	}

}
