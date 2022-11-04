/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */

#include "Human.h"
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
bool Human::play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_meld)
{
	bool immeadiate_break;
	
	immeadiate_break = go_out();
	if (immeadiate_break) return true;
	
	immeadiate_break = draw(draw_decks);
	if (immeadiate_break) return true;
	
	meld(enemy_meld);
	immeadiate_break = go_out();
	if (immeadiate_break) return true;
	
	discard(draw_decks, enemy_meld);
	immeadiate_break = go_out();
	if (immeadiate_break) return true;
	
	return false;
}

/* *********************************************************************
Function Name: draw
Purpose: To simulate a draw phase for a Human, input validation included.
Parameters: 
			  draw_decks, a Deck reference representing the discard and stock pile from Round.
Algorithm:
			 1. Print out the discard and relevant Human hand information so the player can make an informed decision. 
			 2. If the stock pile is empty and the discard pile is frozen, return true.
			 3. Use a do while loop to validate input.   
			 4. If the player can draw from the stock pile and chose to do so, 
				 then keep drawing until the player draws a card that is not a red three and adds to the Hand.
				 Set has_completed_draw to true.
			 5. If the player can draw from the discard pile, then pick up the whole discard pile,
			    then pick up the discard pile and add to Hand. Set has_completed_draw to true.
			 6. If none of the criteria are met above, continue and print an error message.
			 7. If the player cannot draw from both piles, end the game. 
			 8. Continue until has_completed_draw is set to true.
			 9. If successful, it'll return false, meaning that the game shouldn't end.
Local variables:
					has_completed_draw: a bool representing if the draw phase has been completed.
					hand_for_comparisons: a Hand that is used to gather information regarding the player's hand, but not to add to. 
					draw_card: a Card that is drawn from the stock pile.
					picked_up_discard: a vector of Cards representing the entire discard pile.
					top_of_discard: a Card representing the top Card on the discard pile, to see if the discard pile is drawable.
					should_discard: a bool representing if the Human is able to pick up the discard pile.
Return Value: bool, representing if the game should end immeadiately due to an inability to draw.
Assistance Received: none
********************************************************************* */

bool Human::draw(Deck &draw_decks)
{


	bool has_completed_draw = false;
	Hand hand_for_comparisons = get_player_hand();
	Card drawn_card;


	if (draw_decks.stock_is_empty() && draw_decks.get_discard_is_frozen()) {
		std::cout << "Can't draw, the stock pile is empty and the discard pile is frozen! The round is over!" << std::endl;
		return true;
	}

	do {
		std::cout << "Discard Pile: " << std::endl;
		draw_decks.print_discard_pile();

		temp_print_hand();
		std::cout << "DRAW PHASE: Pick a Deck to draw from. " << std::endl;
		std::cout << "1. Stock" << std::endl;
		std::cout << "2. Discard " << std::endl;
		std::cout << "3. Advice" << std::endl;
		
		int choice = validate_option_based_input(1, 3);

		
		if (choice == 1) {
			if (!draw_decks.stock_is_empty()) {
				//keeps drawing a card until the card isn't a red three.
				do {
					drawn_card = draw_decks.draw_from_stock();
					add_to_hand(drawn_card);
					purge_red_threes();
				} while (drawn_card.is_red_three() && !draw_decks.stock_is_empty());
				has_completed_draw = true;
			}
			else {
				std::cout << "The stock pile is empty! Try drawing from the Discard pile." << std::endl;
			}
		}
		
		else if (choice == 3) {
			strategy_draw(draw_decks);
		}
		
		else {
			if (draw_decks.get_discard_is_frozen()) {
				std::cout << "The discard pile is frozen! Try drawing from the Stock pile." << std::endl;
			}
			else {
				Card top_of_discard = draw_decks.get_top_discard_pile();
				bool should_discard = (hand_for_comparisons.is_meldable(top_of_discard) || hand_for_comparisons.is_meldable_with_melds(top_of_discard));
				if (should_discard) {
					std::vector<Card> picked_up_discard = draw_decks.draw_from_discard();
					add_to_hand(picked_up_discard);
					purge_red_threes();
					has_completed_draw = true;
				}
				else {
					std::cout << "No cards in your hand can meld or lay off with the top of the discard pile " 
					<< top_of_discard.get_card_string() << std::endl;
				}
			}
		}
	} while (!(draw_decks.both_piles_are_empty()) && !(has_completed_draw) ||
		(!draw_decks.stock_is_empty() && !draw_decks.get_discard_is_frozen() && !(has_completed_draw))
		);

	if (has_completed_draw == true) {
		return false;
	}
	else {
		std::cout << "Either both piles are empty, or the discard is frozen and the stock pile is empty!" << std::endl;
		std::cout << "Because of this, the Round has ended!" << std::endl;
		return true;
	}

}


/* *********************************************************************
Function Name: meld
Purpose: To simulate the meld phase for the Human player, input validation included.
Parameters:
			 draw_decks: a Deck reference representing the discard and stock pile from Round.
			 enemy_melds: a vector of vectors of Cards representing the enemy's melds.
Algorithm:
			1. Print out relevant information, such as the hand, and the enemy's melds, to ensure the player can make an informed decision.
			2. Use a do while loop to validate player input. Additionally, there is a do while loop in each subphase to 
			   ensure the user doesn't get locked out of a phase just because they made a mistake. 
			3. Based on the options chosen, do: 
				a) Create a meld by getting 3 comma seperated positions(input validated) and call the create_meld function using player_hand.
				b) To add onto a pre-existing meld, validate an option first by getting the size of the hand, and providing options bounded
					by the size of the hand, as well as providing 0 to quit. Then, do a similar process for melds, then, if all is well, 
					call lay_off using player_hand.
				c) To transfer cards, choose a meld bounded by a process similar to the above but by bounding the input by first with the size
					of the meld container, ensuring the meld chosen isn't too small (size<=3). 
					Then, gather a list of all transferable wild cards. If there are none, redo the loop. Then, get the user 
					to input another meld, the other to transfer to and ensure there are no more than 3 wild cards.
				d) Exit the menu, ending the meld phase by setting still_melding to false.
Local variables:
			option: an int representing what the player chose in the menu.
			operation_success: a bool which represents if a subphase was run successfully (i.e. creating a meld).
			still_melding: a bool which represents if the meld phase is still 
			card_pos: an int representing the position of a chosen card in the hand.
			wild_pos: an int representing the position of a chosen wild card in a meld or hand.
			meld_pos: an int representing the meld to transfer to when transferring a wild card.
			card_to_lay_off: a Card representing which card is to be added to another meld.
			card_to_transfer: a Card representing which card is to be transferred from one meld to another.
Return Value: none
Assistance Received: none
********************************************************************* */
void Human::meld(std::vector<std::vector<Card>> enemy_melds)
{
	int option = 0;
	bool operation_success = false;
	bool still_melding = true;
	do {
		print_enemy_meld(enemy_melds);
		temp_print_hand();
		std::cout << "MELD PHASE: Pick an option." << std::endl;
		std::cout << "1. Create a Meld" << std::endl;
		std::cout << "2. Add to a pre-existing Meld " << std::endl;
		std::cout << "3. Transfer wildcards from one meld to another" << std::endl;
		std::cout << "4. End Meld Phase" << std::endl;
		std::cout << "5. Advise" << std::endl;
		option = validate_option_based_input(1, 5);

		switch (option) {
		case 1: {
			temp_print_hand();
			operation_success = false;
			std::vector<Card> potentenial_meld = validate_comma_input();
			if (potentenial_meld.size() == 0)
				break;
			else {
				operation_success = create_meld(potentenial_meld);
				temp_print_hand();
			}
			if (!operation_success)
				std::cout << "The meld operation was unsuccessful! Please see the above output^" << std::endl;
			break;
		}
		case 2: {
			do {
				temp_print_hand();
				operation_success = false;
				int card_pos = 0;
				int meld_pos = 0;
				Card card_to_lay_off;
				Hand player_hand = get_player_hand();

				if (player_hand.get_size_of_meld() != 0) {

					std::cout << "ADD TO EXISTING MELD: Pick a card position from 1 to " << player_hand.get_size_of_hand()
						<< " to add to a pre-existing meld. Say 0 to cancel the operation" << std::endl;
					card_pos = validate_option_based_input(0, player_hand.get_size_of_hand()) - 1;

					//this is if the user enters 0.
					if (card_pos == -1) break;

					card_to_lay_off = player_hand.get_card_from_hand(card_pos);

					std::cout << "Great, now pick a meld position from 1 to " << player_hand.get_size_of_meld()
						<< " to add onto. Enter 0 cancel the operation." << std::endl;
					meld_pos = validate_option_based_input(0, player_hand.get_size_of_meld()) - 1;

					//this is if the user enters 0.
					if (meld_pos == -1) break;

					operation_success = lay_off(card_to_lay_off, meld_pos);
					if (!operation_success) {
						std::cout << "The add onto operation was unsuccessful! Please see the above output^" << std::endl;
					}
				}
				else {
					std::cout << "Meld Error: you have no melds to add onto!" << std::endl;
					break;
				}
			} while (operation_success != true);
			temp_print_hand();
			break;
		}
		case 3:
		{
			temp_print_hand();
			operation_success = false;
			int wild_pos = 0;
			int wild_card_pos;
			int meld_pos = 0;
			Card card_to_transfer;
			Hand player_hand = get_player_hand();
			do {
				if (player_hand.get_size_of_meld() != 0) {

					std::cout << "TRANSFER WILD CARDS: Pick a meld from 1 to " << player_hand.get_size_of_meld()
						<< " to extract the wild card's position. Say 0 to cancel the operation" << std::endl;
					wild_pos = validate_option_based_input(0, player_hand.get_size_of_meld()) - 1;

					//this is if the user enters 0.
					if (wild_pos == -1) break;


					std::vector<Card> wild_meld = player_hand.get_wild_cards(wild_pos);

					if (wild_meld.size() == 0) {
						std::cout << "The meld you chose has no wild cards that can be transfered!" << std::endl;
						break;
					}

					else {
						std::cout << "Great, now pick a card from the following list to transfer Say 0 to cancel" << std::endl;
						//card_to_transfer = player_hand.get_card_from_hand(meld_pos);
						player_hand.print_all_wilds_of_meld(wild_pos);
						wild_card_pos = validate_option_based_input(0, wild_meld.size())-1;
						if (wild_card_pos == -1)
							break;
						//extracts the specific card we want from the list of wildcards.
						card_to_transfer = wild_meld.at(wild_card_pos);
					}

					std::cout << "Great, now pick a meld position from 1 to " << player_hand.get_size_of_meld()
						<< " to add onto. Enter 0 cancel the operation." << std::endl;
					std::cout << "Also, input -1";
					std::cout<<" if you want to transfer the wild card back to the hand. You can only do this " <<
						"if you can create a meld with the cards in the hand." << std::endl;
					meld_pos = validate_option_based_input(-1, player_hand.get_size_of_meld(), true)-1;




					//this is if the user enters 0.
					if (meld_pos == -1) break;
					if (meld_pos == wild_pos) {
						std::cout << "You don't need to transfer a wild card to the same meld..." << std::endl;
						break;
					}


					operation_success = transfer_card(card_to_transfer, wild_pos, meld_pos);
					if (!operation_success) {
						std::cout << "The  was unsuccessful! Please see the above output^" << std::endl;
					}
				}
				else {
					std::cout << "Meld Error: you have no melds to add onto!" << std::endl;
					break;
				}
			} while (operation_success != true);

			break;
		}
		case 4:
			still_melding = false;
			break;
		case 5:
			strategy_meld(enemy_melds);
		}
		
	} while (still_melding);


}
/* *********************************************************************
Function Name: discard
Purpose: To simulate the discard phase for the Human player, input validation included. 
Parameters: 
			draw_decks: a Deck reference representing the discard and stock pile from Round.
			enemy_melds: a vector of vectors of Cards representing the enemy's melds.
Algorithm: 
			1. Print out relevant information, such as the hand, and the enemy's melds, to ensure the player can make an informed decision.
			2. If the player hand is empty, then skip the discard phase.
			3. Prompt the user to enter a position of a Card they'd like to discard and validate it. 
			4. If the user discards a wild card or a card of 3, then freeze the discard pile. 
			5. If the user discards a natural card, unfreeze the discard pile.
Local variables: 
			player_hand: a Hand that represent's the current Human's hand, but only a copy.
			size_of_hand: an int that represents the size of the Human's hand.
			choice: an int which represents the player's choice from validated output, so in this case,
					  the position of the card to discard.
			card_to_discard: the Card which the player chose to discard, to be stored to see if it is wild or natural.
Return Value: none
Assistance Received: none
********************************************************************* */
void Human::discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	temp_print_hand();
	print_enemy_meld(enemy_melds);
	Hand player_hand = get_player_hand();
	int size_of_hand = player_hand.get_size_of_hand();

	if (hand_empty()) {
		std::cout << "You don't have anything to discard, so you skip your discard turn." << std::endl;
		return;
	}


	std::cout << "DISCARD Phase: What card would you like to discard? Select a position from 1 to " 
		<< size_of_hand << std::endl;
	std::cout << "OR input 0 to get advise." << std::endl;
	
	int choice = 0;
	choice = validate_option_based_input(0, size_of_hand) - 1;
	while (choice == -1) {
		strategy_draw(draw_decks);
		std::cout << "DISCARD Phase: What card would you like to discard? Select a position from 1 to "
			<< size_of_hand << std::endl;
		std::cout << "OR input 0 to get advise." << std::endl;
		choice = validate_option_based_input(0, size_of_hand) - 1;
	}


	Card card_to_discard = player_hand.get_card_from_hand(choice);
	if (card_to_discard.isWild() || card_to_discard.isSpecial()) {
		draw_decks.discard_push_front(card_to_discard);
		remove_from_hand(card_to_discard);
		draw_decks.set_discard_freeze(true);
	}
	else {
		draw_decks.discard_push_front(card_to_discard);
		remove_from_hand(card_to_discard);
		draw_decks.set_discard_freeze(false);
	}

	
}
/* *********************************************************************
Function Name: print_player_type
Purpose: To print out the player's type.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Human::print_player_type()
{
	std::cout << "Human";
}
/* *********************************************************************
Function Name: choose_to_go_out
Purpose: To prompt the user if they want to go out or not.
Parameters: none
Return Value: bool, representing if the user chose to go out.
Assistance Received: none
********************************************************************* */
bool Human::choose_to_go_out()
{
	std::cout << "You can go out, you have a Canasta and have melded all other cards. Do you want to go out?" << std::endl;
	std::cout << "This action will end the round, and you'll get a bonus 100 points for ending it. " << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;

	int choice = validate_option_based_input(1, 2);
	if (choice == 1) return true;
	else return false;
}
/* *********************************************************************
Function Name: get_player_type
Purpose: To output a Human's player type.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
std::string Human::get_player_type()
{
	return "Human";
}
/* *********************************************************************
Function Name: print_enemy_melds
Purpose: To output the opponent's melds.
Parameters: enemy_meld, a vector of vectors of Cards that represents the enemy's melds.
Return Value: none
Assistance Received: none
********************************************************************* */
void Human::print_enemy_meld(std::vector<std::vector<Card>> enemy_meld) const
{
	std::cout << "Opponent's melds: " << std::endl;
	for (int meld_pos = 0; meld_pos < enemy_meld.size(); meld_pos++) {
		std::cout << "[ ";
		for (int card_pos = 0; card_pos < enemy_meld.at(meld_pos).size(); card_pos++)
			std::cout << enemy_meld.at(meld_pos).at(card_pos).get_card_string()<<" ";
		std::cout << "] ";
	}
	std::cout << std::endl;
}
/* *********************************************************************
Function Name: strategy
Purpose: To give an advice menu to the Human and as well as give advice.
Parameters: 
			  draw_decks: a Deck reference representing the Round's stock and discard pile.
			  enemy_meld: a vector of vectors of Cards that represents the enemy's melds.
Algorithm: 
			1. Use a do while loop to continually give and validate input, within this do while loop, also, 
				print all relevant player's hand information, as well as the enemy's melds.
			2. Depending on which option the player picks: 
				a) Give advice regarding drawing.
				b) Give advice regarding melding.
				c) Give advice regarding discarding.
				d) exit the menu, and return from the function.
Local variables: 
					choice, an int which represents the player's inputted option.
Return Value: none
Assistance Received: none
********************************************************************* */
void Human::strategy(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	int choice = 0;


	do {
		temp_print_hand();
		print_enemy_meld(enemy_melds);
		std::cout << "Discard pile: " << std::endl;
		draw_decks.print_discard_pile();
		std::cout << "What would you like advice regarding?" << std::endl;
		std::cout << "1. Drawing" << std::endl;
		std::cout << "2. Meld" << std::endl;
		std::cout << "3. Discard" << std::endl;
		std::cout << "4. Go out of menu" << std::endl;
		choice = validate_option_based_input(1, 4);
		switch (choice) {
		case 1:
			strategy_draw(draw_decks);
			break;
		case 2:
			strategy_meld(enemy_melds);
			break;
		case 3:
			strategy_discard(draw_decks, enemy_melds);
			break;
		case 4:
			return;
		}
	} while (choice != 4);

	
	return;
	
}
/* *********************************************************************
Function Name: strategy_draw
Purpose: The Computer's strategy regarding the draw phase reapplied to give advise to the Human, and is nondestructive.
			Note: while it says CPU, this is only regarding recommendations, the CPU doesn't play for the player.
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
Return Value: none.
Assistance Received: none
********************************************************************* */
void Human::strategy_draw(Deck& draw_decks) const
{
	Hand player_hand = get_player_hand();
	Card top_of_discard = draw_decks.get_top_discard_pile();
	bool can_meld = player_hand.is_meldable(top_of_discard);
	bool can_meld_with_melds = player_hand.is_meldable_with_melds(top_of_discard);
	bool hand_is_not_small = (((int)player_hand.get_size_of_hand() > 5));

	if (((can_meld || can_meld_with_melds) && ((!has_canasta() || ((has_canasta()) && (hand_is_not_small))))
		&& (!draw_decks.get_discard_is_frozen()))) {
		std::cout << "You should draw from the discard pile: can meld with hand or add onto melds" 
			<<" and you don't have a canasta, or do you have a canasta but need to purge your hand more." << std::endl;
		return;
	}

	else if (!draw_decks.stock_is_empty()) {
		std::cout << "You should draw from stock, because: ";
		if (draw_decks.get_discard_is_frozen())
			std::cout << "the discard pile is frozen." << std::endl;
		else if (!can_meld)
			std::cout << "there are no cards in the your hand that can meld with the card " << top_of_discard.get_card_string() << std::endl;
		else {
			std::cout << "You should keep a small hand, especially for attempting to go out." << std::endl;
		}
		return ;
	}

	else {
		std::cout << "The stock pile is empty and you can't draw from the discard pile, so you can't do much but let the round end..." << std::endl;
		return ;
	}
}
/* *********************************************************************
Function Name: strategy_meld
Purpose: The Computer's strategy repurposed to be able to give advice to the Human player and is non destructive.
			Additionally, due to this nature, it will instead run on emulated sizes of container for loops dependent on that matter.
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
			emulated_size: an int which represents the emulated size of a particular container.

Return Value: none.
Assistance Received: Particulary in regards to unique and adding in an inaxproimate amount of cards, I used the following:
	//https://cplusplus.com/reference/iterator/back_inserter/
	//https://stackoverflow.com/questions/52150939/cant-dereference-value-initialized-iterator
********************************************************************* */
void Human::strategy_meld(std::vector<std::vector<Card>> enemy_melds) const
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
		std::cout << "One of your cards if discarded will give the enemy make a canasta, so the following advice will be more cautious..."
			<< std::endl;
	}

	//https://cplusplus.com/reference/iterator/back_inserter/
	//https://stackoverflow.com/questions/52150939/cant-dereference-value-initialized-iterator
	//first, remove the duplicate cards.

	bool has_done_action = false;




	std::unique_copy(hand_container.begin(), hand_container.end(), std::back_inserter(no_duplicate_cards));


	if ((has_canasta() && hand_container.size() < 6)) {
		for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
			if ((meld_container.at(meld_pos).size() < 7 && meld_container.at(meld_pos).size() > 3)
				|| meld_container.at(meld_pos).size() > 7) {
				std::vector<Card> wild_transfer_meld = player_hand.get_wild_cards(meld_pos);
				for (int wild_pos = 0; wild_pos < wild_transfer_meld.size(); wild_pos++) {
					if (player_hand.is_meldable(wild_transfer_meld.at(wild_pos))) {
						std::cout << "You should transfer the wild card " <<
							wild_transfer_meld.at(wild_pos).get_card_string() << " to the hand from meld " << wild_pos << ": ";
						print_meld(wild_pos);
						std::cout << "since you should be hasty as to remove all the cards in your hand." << std::endl;
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

		if (natural_meld_vector.size() > 0) {
			meld_already_exists = meld_of_card_exists(natural_meld_vector.at(0));
		}

		else {
			meld_already_exists = false;
		}
		//prevent an underflow.
		if (natural_meld_vector.size() >= 3 && !meld_already_exists &&
			((int)hand_container.size() - amount_of_dangerous_cards > 0) &&
			!is_dangerous_card(natural_meld_vector.at(0), enemy_melds)) {
			Card first_card = natural_meld_vector.at(0);
			Card second_card = natural_meld_vector.at(1);
			Card third_card = natural_meld_vector.at(2);
			player_hand = get_player_hand();

			//to prevent an underflow.
			for (int lay_off_pos = 3; lay_off_pos < (int)natural_meld_vector.size() - amount_of_dangerous_cards; lay_off_pos++) {
				has_done_action = true;
			}
			std::cout << "Meld the following cards: ";
			print_vector(natural_meld_vector);
			std::cout << " since it is an natural meld, getting rid of natural cards is generally advantageous." << std::endl;
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

					int loop_size;
					if (is_dangerous_card(natural_meld_vector.at(0), enemy_melds))
						loop_size = (int)natural_meld_vector.size();
					else
						loop_size = (int)natural_meld_vector.size() - amount_of_dangerous_cards;

					for (int lay_off_pos = 0; lay_off_pos < loop_size; lay_off_pos++) {
						has_done_action = true;

						std::cout << "Lay off the following card(s): ";
						print_vector(natural_meld_vector);
						std::cout << "They are all natural cards, and getting rid of natural cards is generally advantageous." << std::endl;
					}
				}
			}
		}


		natural_meld_vector.clear();
	}

	std::sort(can_meld_with_wild.begin(), can_meld_with_wild.end(),
		[](const Card& lhs, const Card& rhs) -> bool { return lhs > rhs; });


	//to prevent an underflow.
	int emulated_size = (int)wild_cards_in_hand.size();
	while (can_meld_with_wild.size() != 0 && emulated_size - amount_of_dangerous_cards > 0) {
		int card_pos = 0;
		int second_card_pos = 1;
		int wild_pos = 0;

		bool meld_already_exists = false;
		//it's inevitable by the way natural meld aka the vector we're searching from that there will be
		//duplicates. Hence, we can go against this and make sure there are none.
		if (can_meld_with_wild.size() > 0) {
			meld_already_exists = meld_of_card_exists(can_meld_with_wild.at(0));
		}

		else {
			meld_already_exists = false;
		}

		if (!meld_already_exists) {
			Card first_nat_card = can_meld_with_wild.at(card_pos);
			Card second_nat_card = can_meld_with_wild.at(second_card_pos);
			Card third_wild_card = wild_cards_in_hand.at(wild_pos);
			std::cout << "Meld the following: ";
			print_vector(std::vector < Card >{first_nat_card, second_nat_card, third_wild_card});
			std::cout << " as the two natural cards(ordered in highest order of points) can meld with a wild card. " << std::endl;
		}
		//create_meld(first_nat_card, second_nat_card, third_wild_card);
		emulated_size--;
		has_done_action = true;
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
	

	player_hand = get_player_hand();
	wild_cards_in_hand = player_hand.get_wild_cards_from_hand();
	meld_container = player_hand.get_meld();
	meld_container = sort_melds(meld_container);
	int emulatd_wild_card_in_hand = (int)wild_cards_in_hand.size();

	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		int absolute_meld_pos = get_absolute_pos_from_relative_meld(meld_container.at(meld_pos));
		std::vector<Card> wild_cards_from_meld = player_hand.get_wild_cards_ignore_transfer(absolute_meld_pos);
		int emulated_wild_card_size = (int)wild_cards_from_meld.size();
		if (meld_container.at(meld_pos).size() >= 3 && emulated_wild_card_size <= 3) {

			//prevent an underflow error.
			while ((emulatd_wild_card_in_hand - amount_of_dangerous_cards > 0) && (emulated_wild_card_size < 3)) {

				int absolute_meld_pos = get_absolute_pos_from_relative_meld(meld_container.at(meld_pos));
				has_done_action = true;
				//lay_off(wild_cards_in_hand.at(0), absolute_meld_pos);

				std::cout << "Lay off the card " << wild_cards_in_hand.at(0).get_card_string() <<
					" because the meld chosen: ";
				print_vector(meld_container.at(absolute_meld_pos));
				std::cout << " has the highest size and less than 3 wild cards, so you ought to prioritize it." << std::endl;
				wild_cards_in_hand.erase(wild_cards_in_hand.begin());
				emulatd_wild_card_in_hand--;
				emulated_wild_card_size++;

				wild_cards_from_meld = player_hand.get_wild_cards_ignore_transfer(absolute_meld_pos);
			}
		}
	}
	player_hand = get_player_hand();
	meld_container = player_hand.get_meld();

	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		std::vector<Card> meld = meld_container.at(meld_pos);
		int can_meld_to_canasta_sum = meld.size() + 3 - (int)get_wild_cards_from_vector(meld).size();
		int min_for_canasta = 7;
		int emulated_meld_size = meld.size();
		player_hand = get_player_hand();
		meld_container = player_hand.get_meld();
		if (can_meld_to_canasta_sum >= min_for_canasta && meld.size() < 7 && !has_canasta()) {
			int other_melds_pos = (meld_pos == meld_container.size() - 1) ? 0 : meld_pos + 1;
			while (other_melds_pos != meld_pos) {

				player_hand = get_player_hand();
				meld_container = player_hand.get_meld();


				std::vector<Card> meld_to_extract_wilds = meld_container.at(other_melds_pos);
				if (meld_to_extract_wilds.size() > 3) {
					std::vector<Card> wild_to_transfer = player_hand.get_wild_cards(other_melds_pos);
					while (wild_to_transfer.size() != 0 && emulated_meld_size>3) {
						has_done_action = true;
						//transfer_card(wild_to_transfer.at(0), other_melds_pos, meld_pos);
						std::cout << "Transfer the card " << wild_to_transfer.at(0).get_card_string() <<
							" from meld: ";  print_meld(other_melds_pos); std::cout << std::endl;
						std::cout << "As meld: "; print_meld(meld_pos);
						std::cout << "can be made as a Canasta with just a few more wildcards." << std::endl;
						wild_to_transfer.erase(wild_to_transfer.begin());
						emulated_meld_size--;
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
		std::cout << "There's nothing to meld, lay off, or transfer this phase. Do nothing." << std::endl;
	}

	else if (amount_of_dangerous_cards > 0 && !has_done_action) {
		std::cout << "Do nothing, as otherwise you're giving the enemy a free canasta!" << std::endl;
	}
}
/* *********************************************************************
Function Name: strategy_discard
Purpose: The Computer's strategy regarding the discard phase repurposed to give advise to the Human player.
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
void Human::strategy_discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) const
{
	//makes comparisons a lot easier.
	std::vector<Card> preference_discard;
	std::vector<Card> not_in_melds_but_wilds;
	std::vector<Card> no_wild_discard;
	Hand player_hand = get_player_hand();
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
				std::cout << "You should choose to get rid of 3S since the top of the discard, "
					<< top_of_discard.get_card_string() << " is in the enemy meld: "; print_meld(meld_pos);
				std::cout << std::endl;
				has_discarded_three = true;
				break;
			}


			else if (three_clubs_itr != hand_container.end()) {
				preferred_card = *three_clubs_itr;
				std::cout << "You should choose to get rid of 3C since the top of the discard, "
					<< top_of_discard.get_card_string() << " is in the enemy meld: "; print_meld(meld_pos);
				std::cout << std::endl;
				has_discarded_three = true;
				break;
			}
		}
	}



	if (preference_discard.size() != 0 && !has_discarded_three) {
		preferred_card = preference_discard.at(0);

		std::cout << "I suggest to get rid of: " << preferred_card.get_card_string() << " since it the lowest value  " <<
			"In your hand, @" << preferred_card.get_point_value() << " points, and is not in any of the enemy's melds." << std::endl;
	}

	else if (not_in_melds_but_wilds.size() != 0 && !has_discarded_three) {
		preferred_card = not_in_melds_but_wilds.at(0);
		std::cout << "I suggest to get rid of: " << preferred_card.get_card_string() << " since it the lowest value  " <<
			"In your hand, @" << preferred_card.get_point_value() << " points, and wasn't in an enemy meld." << std::endl;
	}

	else if (no_wild_discard.size() != 0 && !has_discarded_three) {
		preferred_card = no_wild_discard.at(0);

		std::cout << "I suggest to get rid of: " << preferred_card.get_card_string() << " since it the lowest value  " <<
			"your hand, @" << preferred_card.get_point_value() << " points, and wasn't a wild card." << std::endl;

		//https://stackoverflow.com/questions/44576857/randomly-pick-from-a-vector-in-c

	}
	else if (hand_container.size() != 0 && !has_discarded_three) {
		preferred_card = hand_container.at(0);
		std::cout << "You don't really have a no choice, so it get rid of your lowest value card, which is " << preferred_card.get_card_string() << std::endl;
	}
	else if (!has_discarded_three) {
		std::cout << "You can't discard anything, I can't really recommend what to discard. " << std::endl;
		return;
	}

	if (preferred_card.isWild() || preferred_card.isSpecial()) {
		draw_decks.set_discard_freeze(true);
	}

	else {
		draw_decks.set_discard_freeze(false);
	}


}

/* *********************************************************************
Function Name: validate_comma_input
Purpose: To extract and validate 3 comma seperated inputs in order to create a potential meld..
Parameters: none
Algorithm:
			 1. Use a do while loop to extract and validate comma seperated input based on card positions, and add to a vector.
			 2. Remove any extra spaces within this input. If the player inputs 0, then break immeadiately. 
			 3. Check if the vector is of size 3, if not, then are too many or too little positions. Repeat the input loop. 
			 4. Get only unique positions in the comma based input. If the size isn't 3, then there are duplicates. Repeat the input loop.
			 5. Check that all inputs are numeric and within the bounds of the hand. If not, repeat the loop. 
			 6. If the cards pass all the critera, return the vector of Cards. 
			 7. Note that all positions are index 1 rather than 0, so some addition/subtraction is involved.
Local variables:
					has_valid_input: a bool, which represents if an input is valid.
					input: a string which represents the Human's input. 
					player_hand: a Hand representing the Human's hand. 
					card_pos_range: an int representing the maximum size of that can be inputted.
					potential_card_pos: a string representing all the possible positions that the user has inputted.
					pos_to_compare: an int representing all the positions from which to compare to ensure there are no duplicates.
Return Value: none
Assistance Received: none
********************************************************************* */
std::vector<Card> Human::validate_comma_input()
{
	bool has_valid_input = false;
	std::string input;
	Hand player_hand = get_player_hand();
	//we need parenthesis due to order of operations.
	int card_pos_range = player_hand.get_size_of_hand();
	std::vector<Card> cards_to_meld;
	do {
		std::cout << "CREATE MELD: Please input the position of the cards you want to meld. Please put EXACTLY 3 comma seperated unique positions." << std::endl;
		std::cout << "Card position starts at 1 and ends at " << card_pos_range << std::endl;
		std::cout << "That or say 0 to cancel this phase." << std::endl;


		getline(std::cin, input);


		if (input == "0")
			break;

		std::vector<std::string> results;

		//strips the string of all whitespace.
		input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
		std::stringstream  ss(input);
		std::string str;


		while (getline(ss, str, ',')) {
			results.push_back(str);	
		}
		if (results.size() != 3) {
			std::cout << "You either too many or too little positions. Please put only 3 positions" << std::endl;
		}

		results.erase(std::unique(results.begin(), results.end()),results.end());

		if (results.size() != 3) {
			std::cout << "No duplicates can exist! Please enter unique positions." << std::endl;
		}

		for (int input_pos = 0; input_pos < results.size(); input_pos++) {
			std::string potential_card_pos = results.at(input_pos);
			//checks if all the positions are alphanumeric.
			if (!(std::all_of(potential_card_pos.begin(), potential_card_pos.end(), ::isdigit))) {
				std::cout<<"Position is not numeric. Please input a numeric position!"<<std::endl;
			}


			else {
				//converts from string to int and then ensures it's within the card range.
				//note that it's not at index 0, since we don't know if the user is technically apt.
				int pos_to_compare = stoi(potential_card_pos);
				if (pos_to_compare >= 1 && pos_to_compare <= card_pos_range) {
					cards_to_meld.push_back(player_hand.get_card_from_hand(pos_to_compare-1));
				}
				else {
					std::cout << "Position is not within range 1 to " << card_pos_range << "!" << std::endl;
					break;
				}
			}
			ss.str("");
		}

		if (cards_to_meld.size() == 3)
			has_valid_input = true;
		else
			cards_to_meld.clear();


	} while (has_valid_input == false);
	return cards_to_meld;
}

