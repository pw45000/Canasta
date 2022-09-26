#include "Computer.h"
#include <iostream>

Computer::Computer()
{
	meld_cut_off = 5;
}

bool Computer::play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	bool immeadiate_break;


	immeadiate_break = go_out();
	if (immeadiate_break) return true;

	immeadiate_break = draw(draw_decks);
	if (immeadiate_break) return true;

	meld();
	immeadiate_break = go_out();
	if (immeadiate_break) return true;

	discard(draw_decks, enemy_melds);
	immeadiate_break = go_out();
	if (immeadiate_break) return true;

	return false;
}

void Computer::discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	//makes comparisons a lot easier.
	sort_hand();
	std::vector<Card> preference_discard; 
	std::vector<Card> no_wild_discard;
	Hand player_hand = get_player_hand();
	std::vector<Card> hand_container = player_hand.get_hand_container();
	Card preferred_card;
	int first_card_pos = 0;
	
	auto three_spades_itr = std::find(hand_container.begin(), hand_container.end(), Card("3S"));
	auto three_clubs_itr = std::find(hand_container.begin(), hand_container.end(), Card("3C"));
	
	for (int card_pos = 0; card_pos < hand_container.size(); card_pos++) {
		Card card_to_search = hand_container.at(card_pos);
		for (int meld_pos = 0; meld_pos < enemy_melds.size(); meld_pos++) {
			//checks for the first card. Due to the way I set up melding, it'll never
			//be able to have a wild card be the first card in a meld.
			if (card_to_search.get_card_face() != enemy_melds.at(meld_pos).at(0).get_card_face() && !card_to_search.isWild())
				preference_discard.push_back(card_to_search);
		}

		if (!card_to_search.isWild()) {
			no_wild_discard.push_back(card_to_search);
		}


	}

	Card top_of_discard = draw_decks.get_top_discard_pile();
	bool has_discarded_three = false;
	for (int meld_pos = 0; meld_pos < enemy_melds.size(); meld_pos++) {
		if (top_of_discard == enemy_melds.at(meld_pos).at(first_card_pos)) {
			if (three_spades_itr != hand_container.end()) {
				preferred_card = *three_spades_itr;
				draw_decks.discard_push_front(*three_spades_itr);
				remove_from_hand(*three_spades_itr);
				std::cout << "The CPU chose to get rid of three of spades since it sees the top of the discard, "
					<< top_of_discard.get_card_string() << " is in the meld: "; print_meld(meld_pos);
				std::cout << std::endl;
				has_discarded_three = true;
				break;
			}


			else if (three_clubs_itr != hand_container.end()) {
				preferred_card = *three_clubs_itr;
				draw_decks.discard_push_front(*three_clubs_itr);
				remove_from_hand(*three_clubs_itr);
				std::cout << "The CPU chose to get rid of three of clubs since it sees the top of the discard, "
					<< top_of_discard.get_card_string() << " is in the meld: "; print_meld(meld_pos);
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

void Computer::meld()
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

	//https://cplusplus.com/reference/iterator/back_inserter/
	//https://stackoverflow.com/questions/52150939/cant-dereference-value-initialized-iterator
	//first, remove the duplicate cards.

	bool has_done_action = false;

	


	std::unique_copy(hand_container.begin(), hand_container.end(), std::back_inserter(no_duplicate_cards));


	if ((has_canasta() && hand_container.size() < 6)) {
		for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
			if ((meld_container.at(meld_pos).size() < 7 && meld_container.at(meld_pos).size()>3)
				|| meld_container.at(meld_pos).size() > 7) {
				std::vector<Card> wild_transfer_meld = player_hand.get_wild_cards(meld_pos);
				for (int wild_pos = 0; wild_pos<wild_transfer_meld.size();wild_pos++) {
					if (player_hand.is_meldable(wild_transfer_meld.at(wild_pos))) {
						std::cout << "The CPU decided to transfer the wild card " <<
							wild_transfer_meld.at(wild_pos).get_card_string() << "to the hand from meld "<<wild_pos<<": ";
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
				unique_faces.push_back(hand_container.at(card_pos));
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
			bool meld_already_exists = meld_of_card_exists(natural_meld_vector.at(0));
		}

		else {
			meld_already_exists = false;
		}

		if (natural_meld_vector.size() >= 3 && !meld_already_exists) {
			Card first_card = natural_meld_vector.at(0);
			Card second_card = natural_meld_vector.at(1);
			Card third_card = natural_meld_vector.at(2);
			create_meld(first_card, second_card, third_card);
			player_hand = get_player_hand();


			for (int lay_off_pos = 3; lay_off_pos < natural_meld_vector.size(); lay_off_pos++) {
				lay_off(natural_meld_vector.at(lay_off_pos), player_hand.get_size_of_meld() - 1);
				has_done_action = true;
			}
			std::cout << "The CPU decided to meld the following cards: ";
			print_vector(natural_meld_vector);
			std::cout << " as they were an all natural meld, and getting rid of natural cards is advantageous always." << std::endl;
		}
		else if (natural_meld_vector.size() == 2 && !meld_already_exists) {
			Card first_card = natural_meld_vector.at(0);
			Card second_card = natural_meld_vector.at(1);

			can_meld_with_wild.push_back(first_card);
			can_meld_with_wild.push_back(second_card);
			
		}
		
		//if it's just one card, see if it can be laid off to a meld.
		else if (natural_meld_vector.size() == 1 && !meld_already_exists) {
			meld_container = player_hand.get_meld();
			for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
				if (natural_meld_vector.at(0) == meld_container.at(meld_pos).at(0)) {
					has_done_action = true;
					lay_off(natural_meld_vector.at(0), meld_pos);
					std::cout << "The computer decided to lay off card " << natural_meld_vector.at(0).get_card_string() << " as natural cards"
						<< "only have use in natural melds." << std::endl;
				}
			}
		}

		else if (meld_already_exists) {
			for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
				if (natural_meld_vector.at(0).get_card_face()==meld_container.at(meld_pos).at(0).get_card_face())
					for (int lay_off_pos = 0; lay_off_pos < natural_meld_vector.size(); lay_off_pos++) {
						has_done_action = true;
						lay_off(natural_meld_vector.at(lay_off_pos), meld_pos);

						std::cout << "The CPU decided to lay off the following cards: ";
						print_vector(natural_meld_vector);
						std::cout << " as they were an all natural cards, and getting rid of natural cards is always advantageous." << std::endl;
					}
			}
		}


		natural_meld_vector.clear();
	}

	std::sort(can_meld_with_wild.begin(), can_meld_with_wild.end(), 
		[](const Card& lhs, const Card& rhs) -> bool { return lhs > rhs; });

	

	while (can_meld_with_wild.size() != 0 && wild_cards_in_hand.size()!=0) {
		int card_pos = 0;
		int second_card_pos = 1;
		int wild_pos = 0; 

		Card first_nat_card = can_meld_with_wild.at(card_pos);
		Card second_nat_card = can_meld_with_wild.at(second_card_pos);
		Card third_wild_card = wild_cards_in_hand.at(wild_pos);
		std::cout << "The CPU decided to meld: ";
		print_vector(std::vector < Card >{first_nat_card, second_nat_card, third_wild_card});
		std::cout << " as the two natural cards(ordered in highest order of points) can meld with a wild card. " << std::endl;

		create_meld(first_nat_card, second_nat_card, third_wild_card);
		has_done_action = true;
		//delete the pair at the beginning of the vector
		can_meld_with_wild.erase(can_meld_with_wild.begin()+ card_pos);
		can_meld_with_wild.erase(can_meld_with_wild.begin() + card_pos);
		
		//since the cards are in pairs.
		player_hand = get_player_hand();
		wild_cards_in_hand = player_hand.get_wild_cards_from_hand();
	}

	player_hand = get_player_hand();
	wild_cards_in_hand = player_hand.get_wild_cards_from_hand();
	meld_container = player_hand.get_meld();

	sort_melds(meld_container);
	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		player_hand = get_player_hand();
		wild_cards_in_hand = player_hand.get_wild_cards_from_hand();
		meld_container = player_hand.get_meld();
		sort_melds(meld_container);
		std::vector<Card> wild_cards_from_meld = player_hand.get_wild_cards_ignore_transfer(meld_pos);
		
		if (meld_container.at(meld_pos).size() >= 3 && wild_cards_from_meld.size()<=3) {

			while (wild_cards_in_hand.size() != 0 && wild_cards_from_meld.size() < 3) {

				int absolute_meld_pos = get_absolute_pos_from_relative_meld(meld_container.at(meld_pos));
				has_done_action = true;
				lay_off(wild_cards_in_hand.at(0), absolute_meld_pos);
				std::cout << "The CPU chose to lay off the card " << wild_cards_in_hand.at(0).get_card_string() <<
					" because the meld chose, ";
				print_vector(meld_container.at(meld_pos));
				std::cout << " had the highest size and less than 3 wild cards, so it prioritized it." << std::endl;


				player_hand = get_player_hand();
				wild_cards_in_hand = player_hand.get_wild_cards_from_hand();
				wild_cards_from_meld = player_hand.get_wild_cards_ignore_transfer(meld_pos);
			}
		}
	}
	player_hand = get_player_hand();
	meld_container = player_hand.get_meld();

	for (int meld_pos = 0; meld_pos < meld_container.size(); meld_pos++) {
		std::vector<Card> meld = meld_container.at(meld_pos);
		int can_meld_to_canasta_sum = meld.size() + 3 - get_wild_cards_from_vector(meld).size();
		int min_for_canasta = 7;
		player_hand = get_player_hand();
		meld_container = player_hand.get_meld();
		if (can_meld_to_canasta_sum >= min_for_canasta && meld.size()<7 && !has_canasta()) {
			int other_melds_pos = (meld_pos == meld_container.size() - 1) ? 0 : meld_pos + 1;
			while (other_melds_pos != meld_pos) {
				
				player_hand = get_player_hand();
				meld_container = player_hand.get_meld();


				std::vector<Card> meld_to_extract_wilds = meld_container.at(other_melds_pos);
				if (meld_to_extract_wilds.size() < 3) {
					std::vector<Card> wild_to_transfer = player_hand.get_wild_cards(other_melds_pos);
					while (wild_to_transfer.size() != 0) {
						has_done_action = true;
						transfer_card(wild_to_transfer.at(0), other_melds_pos, meld_pos);
						std::cout << "CPU decided to transfer card " << wild_to_transfer.at(0).get_card_string() <<
							"from meld: ";  print_meld(other_melds_pos); std::cout << std::endl;
						std::cout << "As meld: "; print_meld(meld_pos); 
						std::cout << "can be made as a Canasta with just a few more wildcards." << std::endl;
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

	if (!has_done_action) {
		std::cout << "The CPU decided to do nothing, since it can't do any actions regarding melding." << std::endl;
	}
	





	sort_hand();



}

bool Computer::draw(Deck &draw_decks)
{
	Hand player_hand = get_player_hand();
	Card top_of_discard = draw_decks.get_top_discard_pile();
	bool can_meld = player_hand.is_meldable(top_of_discard);
	bool can_meld_with_melds = player_hand.is_meldable_with_melds(top_of_discard);

	if ((player_hand.get_size_of_hand() > 5 && (can_meld || can_meld_with_melds) && !has_canasta()) && (!draw_decks.get_discard_is_frozen())) {
		std::cout << "CPU: drawing discard pile: can meld with hand or add onto melds, hand isn't that small." << std::endl;
		std::vector<Card> picked_up_discard = draw_decks.draw_from_discard();
		add_to_hand(picked_up_discard);
		purge_red_threes();
		return false;
	}

	else if (!draw_decks.stock_is_empty()) {
		std::cout << "CPU: drawing from stock, because:";
		
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

void Computer::print_player_type()
{
	std::cout << "Computer";
}

bool Computer::choose_to_go_out()
{
	std::cout << "The computer chose to go out since it likes 100 point bonuses." << std::endl;
	return true;
}

void Computer::strategy(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	std::cout << "The computer has it's own strategy, so it doesn't need advice..." << std::endl;
}

std::string Computer::get_player_type()
{
	return "Computer";
}

