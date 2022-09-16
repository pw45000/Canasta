#include "Human.h"

void Human::play(Deck& draw_decks)
{
	draw(draw_decks);
}

bool Human::draw(Deck &draw_decks)
{
	std::cout << "DRAW PHASE: Pick a Deck to draw from. " << std::endl;
	std::cout << "1. Stock" << std::endl;
	std::cout << "2. Discard " << std::endl;

	bool has_completed_draw = false;
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
					//std::vector<Card> picked_up_discard = draw_decks.draw_from_discard();
					//add_to_hand(picked_up_discard);
					purge_red_threes();
					has_completed_draw = true;
					//picked_up_discard.clear();
					draw_decks.clear_discard();
				}
				else {
					std::cout << "No cards in your hand can meld with the top of the discard pile " 
					<< top_of_discard.get_card_string() << std::endl;
				}
			}
		}
	} while (!(draw_decks.both_piles_are_empty()) && !(has_completed_draw));


	if (!(draw_decks.both_piles_are_empty())) {
		return true;
	}
	else {
		return false;
	}

}

void Human::meld()
{
	return;
}

void Human::discard()
{
	return;
}

void Human::print_player_type()
{
	std::cout << "Human:" << std::endl;
}

