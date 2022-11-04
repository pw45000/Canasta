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
		const std::vector<Card>& b) { return a.size() > b.size(); });
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




