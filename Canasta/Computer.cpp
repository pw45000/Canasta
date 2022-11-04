/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */

#include "Computer.h"
#include <iostream>

/* *********************************************************************
Function Name: play
Purpose: The main gameplay loop for each player.
Parameters:
			 draw_decks: a Deck reference which represents the discard and stock pile from the Round.
			 enemy_melds: a vector of vectors of Card which represents the enemy's melds.
Return Value: none
Assistance Received: none
********************************************************************* */
bool Computer::play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	bool immeadiate_break;


	immeadiate_break = go_out();
	if (immeadiate_break) return true;

	immeadiate_break = draw(draw_decks);
	if (immeadiate_break) return true;

	meld(enemy_melds);
	immeadiate_break = go_out();
	if (immeadiate_break) return true;

	discard(draw_decks, enemy_melds);
	immeadiate_break = go_out();
	if (immeadiate_break) return true;

	return false;
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
void Computer::discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
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
			if(!card_to_search.isWild() && !card_to_search.isSpecial())
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
				std::cout << "The CPU chose to get rid of 3S since it sees the top of the discard, "
					<< top_of_discard.get_card_string() << " is in the enemy meld: "; print_meld(meld_pos);
				std::cout << std::endl;
				has_discarded_three = true;
				break;
			}


			else if (three_clubs_itr != hand_container.end()) {
				preferred_card = *three_clubs_itr;
				draw_decks.discard_push_front(*three_clubs_itr);
				remove_from_hand(*three_clubs_itr);
				std::cout << "The CPU chose to get rid of 3C since it sees the top of the discard, "
					<< top_of_discard.get_card_string() << " is in the enemy meld: "; print_meld(meld_pos);
					std::cout<< std::endl;
					has_discarded_three = true;
				break;
			}
		}
	}



	if (preference_discard.size() != 0 && !has_discarded_three) {
		preferred_card = preference_discard.at(0);
		
		std::cout << "The CPU chose to get rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
		"In the CPU's hand, @" << preferred_card.get_point_value() << " points, and is not in any of the enemy's melds." << std::endl;
	}

	else if (not_in_melds_but_wilds.size() != 0 && !has_discarded_three) {
		preferred_card = not_in_melds_but_wilds.at(0);
		std::cout << "The CPU chose to get rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
			"In the CPU's hand, @" << preferred_card.get_point_value() << " points, and wasn't in an enemy meld." << std::endl;
	}

	else if (no_wild_discard.size()!= 0 && !has_discarded_three) {
		preferred_card = no_wild_discard.at(0);

		std::cout << "The CPU chose to get rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
			"In the CPU's hand, @" << preferred_card.get_point_value() << " points, and wasn't a wild card." << std::endl;

		//https://stackoverflow.com/questions/44576857/randomly-pick-from-a-vector-in-c

	}
	else if (hand_container.size()!=0 && !has_discarded_three) {
		preferred_card = hand_container.at(0);
		std::cout << "The CPU had no choice, so it got rid of it's lowest value card, which ended up being: " << preferred_card.get_card_string() << std::endl;
	}
	else if (!has_discarded_three) {
		std::cout << "The CPU has nothing to discard, so it didn't." << std::endl;
		return;
	}
	
	if (preferred_card.isWild() || preferred_card.isSpecial()) {
		draw_decks.set_discard_freeze(true);
	}

	else {
		draw_decks.set_discard_freeze(false);
	}

	draw_decks.discard_push_front(preferred_card);
	remove_from_hand(preferred_card);




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

void Computer:: meld(std::vector<std::vector<Card>> enemy_melds)
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
		std::cout << "The CPU sees that one of its cards if discarded will give the enemy make a canasta, so it's playing more conservatively..."
			<< std::endl;
	}


	bool has_done_action = false;

	

	//first, remove the duplicate cards.

	std::unique_copy(hand_container.begin(), hand_container.end(), std::back_inserter(no_duplicate_cards));


	if ((has_canasta() && hand_container.size() < 6)) {
		for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
			if ((meld_container.at(meld_pos).size() < 7 && meld_container.at(meld_pos).size()>3)
				|| meld_container.at(meld_pos).size() > 7) {
				std::vector<Card> wild_transfer_meld = player_hand.get_wild_cards(meld_pos);
				for (int wild_pos = 0; wild_pos<wild_transfer_meld.size();wild_pos++) {
					if (player_hand.is_meldable(wild_transfer_meld.at(wild_pos))) {
						std::cout << "The CPU decided to transfer the wild card " <<
							wild_transfer_meld.at(wild_pos).get_card_string() << " to the hand from meld "<<wild_pos<<": ";
						print_meld(wild_pos);
						std::cout << "since it is quite eager to get rid of the cards out of it's hand to go out." << std::endl;
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
			((int)hand_container.size()-amount_of_dangerous_cards>0) && 
			!is_dangerous_card(natural_meld_vector.at(0),enemy_melds)) {
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
			std::cout << "The CPU decided to meld the following cards: ";
			print_vector(natural_meld_vector);
			std::cout << " as they were an all natural meld, and getting rid of natural cards is generally advantageous." << std::endl;
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

					int loop_size= natural_meld_vector.size();

					for (int lay_off_pos = 0; lay_off_pos < loop_size; lay_off_pos++) {
						has_done_action = true;
						lay_off(natural_meld_vector.at(lay_off_pos), meld_pos);

						std::cout << "The CPU decided to lay off the following card(s): ";
						print_vector(natural_meld_vector);
						std::cout << " as they were an all natural cards, and getting rid of natural cards is always advantageous." << std::endl;
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
			std::cout << "The CPU decided to meld: ";
			print_vector(std::vector < Card >{first_nat_card, second_nat_card, third_wild_card});
			std::cout << " as the two natural cards(ordered in highest order of points) can meld with a wild card. " << std::endl;

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
		
		if (meld_container.at(meld_pos).size() >= 3 && wild_cards_from_meld.size()<=3) {

			//prevent an underflow error.
			while ((((int)wild_cards_in_hand.size() - amount_of_dangerous_cards) > 0) && wild_cards_from_meld.size() < 3) {

				absolute_meld_pos = get_absolute_pos_from_relative_meld(meld_container.at(meld_pos));
				has_done_action = true;

				std::cout << "The CPU chose to lay off the card " << wild_cards_in_hand.at(0).get_card_string() <<
					" because the meld chose, ";
				print_vector(meld_container.at(meld_pos));
				std::cout << " had the highest size and less than 3 wild cards, so it prioritized it." << std::endl;
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
		if (can_meld_to_canasta_sum >= min_for_canasta && (meld.size()<6 && meld.size()>3) && !has_canasta()) {
			int other_melds_pos = (meld_pos == meld_container.size() - 1) ? 0 : meld_pos + 1;
			while (other_melds_pos != meld_pos) {
				
				player_hand = get_player_hand();
				meld_container = player_hand.get_meld();


				std::vector<Card> meld_to_extract_wilds = meld_container.at(other_melds_pos);
				if (meld_to_extract_wilds.size() > 3) {
					std::vector<Card> wild_to_transfer = player_hand.get_wild_cards(other_melds_pos);
					while (wild_to_transfer.size() != 0 && meld_to_extract_wilds.size() > 3) {
						has_done_action = true;
						std::cout << "CPU decided to transfer card " << wild_to_transfer.at(0).get_card_string() <<
							" from meld: ";  print_meld(other_melds_pos);
						std::cout << "As meld: "; print_meld(meld_pos);
						std::cout << " can be made as a Canasta with just a few more wildcards." << std::endl;
						transfer_card(wild_to_transfer.at(0), other_melds_pos, meld_pos);
						player_hand = get_player_hand();
						meld_container = player_hand.get_meld();
						meld_to_extract_wilds = meld_container.at(other_melds_pos);
						wild_to_transfer.erase(wild_to_transfer.begin());
					}
				}
				
				player_hand = get_player_hand();
				meld_container = player_hand.get_meld();

				if (other_melds_pos == meld_container.size()-1)
					other_melds_pos = 0;
				else
					other_melds_pos++;
			}
		}
	}



	if (!has_done_action && amount_of_dangerous_cards==0) {
		std::cout << "The CPU decided to do nothing, since it can't do any actions regarding melding." << std::endl;
	}

	else if (amount_of_dangerous_cards > 0 && !has_done_action) {
		std::cout << "The CPU decided to do nothing, since it would rather do nothing than give a free canasta to the enemy." << std::endl;
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
bool Computer::draw(Deck &draw_decks)
{
	Hand player_hand = get_player_hand();
	Card top_of_discard = draw_decks.get_top_discard_pile();
	bool can_meld = player_hand.is_meldable(top_of_discard);
	bool can_meld_with_melds = player_hand.is_meldable_with_melds(top_of_discard);
	bool hand_is_not_small = (((int)player_hand.get_size_of_hand() > 5));

	if (((can_meld || can_meld_with_melds) && ((!has_canasta() || ((has_canasta())  && (hand_is_not_small))))
		&& (!draw_decks.get_discard_is_frozen()))) {
		std::cout << "CPU: drawing discard pile: can meld with hand or add onto melds, hand isn't that small." << std::endl;
		std::vector<Card> picked_up_discard = draw_decks.draw_from_discard();
		add_to_hand(picked_up_discard);
		purge_red_threes();
		return false;
	}

	else if (!draw_decks.stock_is_empty()) {
		std::cout << "CPU: drawing from stock, because: ";
		
		Card drawn_card;
		do {
			drawn_card = draw_decks.draw_from_stock();
			add_to_hand(drawn_card);
			purge_red_threes();
		} while (drawn_card.is_red_three() && !draw_decks.stock_is_empty());
		

		if (draw_decks.get_discard_is_frozen())
			std::cout << "the discard pile is frozen." << std::endl;
		else if (!can_meld)
			std::cout << "there are no cards in the CPU's hand that can meld with the card " << top_of_discard.get_card_string() << std::endl;
		else {
			std::cout << "The bot wants to keep a small hand." << std::endl;
		}
		return false;
	}

	else {
		std::cout << "The stock pile is empty and the CPU can't draw from the discard pile. It concedes!" << std::endl;
		return true;
	}


}
/* *********************************************************************
Function Name: print_player_type
Purpose: Prints the Computer's player type.
Parameters: none.
Return Value: none
Assistance Received: none
********************************************************************* */
void Computer::print_player_type()
{
	std::cout << "Computer";
}
/* *********************************************************************
Function Name: choose_to_go_out
Purpose: Give a decision as to if the Computer wants to go out.
Parameters: none.
Return Value: bool representing if the Computer chose to go out.
Assistance Received: none
********************************************************************* */
bool Computer::choose_to_go_out()
{
	std::cout << "The computer chose to go out since it likes 100 point bonuses." << std::endl;
	return true;
}

/* *********************************************************************
Function Name: strategy
Purpose: Overrides strategy for the Computer, and prints out a message stating it doesn't need it's own strategy.
Parameters: 
			 draw_decks: a Deck reference representing the discard and stock pile from Round.
			 enemy_melds: a vector of vectors of Cards representing the enemy's melds.
Return Value: none.
Assistance Received: none
********************************************************************* */
void Computer::strategy(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	std::cout << "The computer has it's own strategy, so it doesn't need advice..." << std::endl;
}

/* *********************************************************************
Function Name: get_player_type
Purpose: returns the Computer's player type.
Parameters: none.
Return Value: string representing the Computer's player type.
Assistance Received: none
********************************************************************* */
std::string Computer::get_player_type()
{
	return "Computer";
}

