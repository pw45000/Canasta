#include "Human.h"

void Human::play()
{
	return;
}

bool Human::draw(Deck draw_decks)
{
	std::cout << "DRAW PHASE: Pick a Deck to draw from. " << std::endl;
	std::cout << "1. Stock" << std::endl;
	std::cout << "2. Discard " << std::endl;
	int choice = validate_option_based_input(1, 2);
	bool can_draw_from_both = true;
	Hand hand_for_comparisons = get_player_hand();

	if (choice == 1) {
		if (!draw_decks.stock_is_empty()) {
			draw_decks.draw_from_stock();
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
				draw_decks.draw_from_discard();
			}
		}
	}

	return true;

}

void Human::meld()
{
	return;
}

void Human::discard()
{
	return;
}
