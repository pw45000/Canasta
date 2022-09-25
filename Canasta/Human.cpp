#include "Human.h"
#include <iostream>

bool Human::play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_meld)
{
	bool immeadiate_break;
	

	immeadiate_break = go_out();
	if (immeadiate_break) return true;
	
	immeadiate_break = draw(draw_decks);
	if (immeadiate_break) return true;
	
	meld();
	immeadiate_break = go_out();
	if (immeadiate_break) return true;
	
	discard(draw_decks, enemy_meld);
	immeadiate_break = go_out();
	if (immeadiate_break) return true;
	
	
	return false;


}

bool Human::draw(Deck &draw_decks)
{
	std::cout << "DRAW PHASE: Pick a Deck to draw from. " << std::endl;
	std::cout << "1. Stock" << std::endl;
	std::cout << "2. Discard " << std::endl;

	std::cout << "Discard Pile: " << std::endl;
	draw_decks.print_discard_pile();


	bool has_completed_draw = false;
	bool stock_is_empty;
	Hand hand_for_comparisons = get_player_hand();
	Card drawn_card;

	do {
		int choice = validate_option_based_input(1, 2);
		if (choice == 1) {
			if (!draw_decks.stock_is_empty()) {
				//keeps drawing a card until the card isn't a red three.
				do {
					drawn_card = draw_decks.draw_from_stock();
					add_to_hand(drawn_card);
					purge_red_threes();
				} while (drawn_card.is_red_three());
				has_completed_draw = true;
			}
			else {
				std::cout << "The stock pile is empty! Try drawing from the Discard pile." << std::endl;
			}
		}
		else {
			if (draw_decks.get_discard_is_frozen()) {
				std::cout << "The discard pile is frozen! Try drawing from the Stock pile." << std::endl;
			}
			else {
				Card top_of_discard = draw_decks.get_top_discard_pile();
				bool should_discard = hand_for_comparisons.is_meldable(top_of_discard);
				if (should_discard) {
					std::vector<Card> picked_up_discard = draw_decks.draw_from_discard();
					add_to_hand(picked_up_discard);
					purge_red_threes();
					has_completed_draw = true;
				}
				else {
					std::cout << "No cards in your hand can meld with the top of the discard pile " 
					<< top_of_discard.get_card_string() << std::endl;
				}
			}
		}
	} while (!(draw_decks.both_piles_are_empty()) && !(has_completed_draw) &&
		(!draw_decks.stock_is_empty() && !draw_decks.get_discard_is_frozen() && !(has_completed_draw))
		);


	if (!(draw_decks.both_piles_are_empty()) && (!draw_decks.stock_is_empty() && !draw_decks.get_discard_is_frozen())) {
		return false;
	}

	else if (draw_decks.get_discard_is_frozen() && !draw_decks.stock_is_empty()) {
		return false;
	}
	else {
		return true;
	}

}

void Human::meld()
{
	int option = 0;
	bool operation_success = false;
	bool still_melding = true;
	int choice = 0;

	do {
		std::cout << "MELD PHASE: Pick an option." << std::endl;
		std::cout << "1. Create a Meld" << std::endl;
		std::cout << "2. Add to a pre-existing Meld " << std::endl;
		std::cout << "3. Transfer wildcards from one meld to another" << std::endl;
		std::cout << "4. End Meld Phase" << std::endl;
		option = validate_option_based_input(1, 4);

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
						std::cout << "The lay off operation was unsuccessful! Please see the above output^" << std::endl;
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
		}
	} while (still_melding);


}

void Human::discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	temp_print_hand();
	print_enemy_meld(enemy_melds);
	Hand player_hand = get_player_hand();
	int size_of_hand = player_hand.get_size_of_hand();

	if (size_of_hand == 0) {
		std::cout << "You don't have anything to discard, so you skip your discard turn." << std::endl;
	}


	std::cout << "DISCARD Phase: What card would you like to discard? Select a position from 1 to " 
		<< size_of_hand << std::endl;
	int choice = validate_option_based_input(0, size_of_hand) - 1;

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

void Human::print_player_type()
{
	std::cout << "Human";
}

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

std::string Human::get_player_type()
{
	return "Human";
}

void Human::print_enemy_meld(std::vector<std::vector<Card>> enemy_meld)
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




std::vector<Card> Human::validate_comma_input()
{
	bool has_valid_input = false;
	std::string input;
	Hand player_hand = get_player_hand();
	//we need parenthesis due to order of operations.
	int card_pos_range = player_hand.get_size_of_hand();
	std::vector<Card> cards_to_meld;
	do {
		std::cout << "CREATE MELD: Please input the position of the cards you want to meld. Please put EXACTLY 3 unique positions." << std::endl;
		std::cout << "Card position starts at 1 and ends at " << card_pos_range << std::endl;
		std::cout << "That or say quit to cancel this phase." << std::endl;


		getline(std::cin, input);


		if (input == "quit" || input == "Quit" || input == "QUIT")
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

