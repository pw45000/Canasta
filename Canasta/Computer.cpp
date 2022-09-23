#include "Computer.h"
#include <iostream>

bool Computer::play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	bool immeadiate_break;


	immeadiate_break = go_out();
	if (immeadiate_break) return true;

	immeadiate_break = draw(draw_decks);
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
	
	auto three_spades_itr = std::find(hand_container.begin(), hand_container.end(), Card("3S"));
	if (three_spades_itr != hand_container.end()) {
		draw_decks.discard_push_front(*three_spades_itr);
		remove_from_hand(*three_spades_itr);
		std::cout << "The CPU chose to get rid of a three of spades since it can't make melds with it." << std::endl;
		return;
	}

	auto three_clubs_itr = std::find(hand_container.begin(), hand_container.end(), Card("3S"));
	if (three_clubs_itr != hand_container.end()) {
		draw_decks.discard_push_front(*three_clubs_itr);
		remove_from_hand(*three_clubs_itr);
		std::cout << "The CPU chose to get rid of a three of clubs since it can't make melds with it." << std::endl;
		return;
	}





	for (int card_pos = 0; card_pos < hand_container.size(); card_pos++) {
		Card card_to_search = hand_container.at(card_pos);
		for (int meld_pos = 0; meld_pos < enemy_melds.size(); meld_pos++) {
			//checks for the first card. Due to the way I set up melding, it'll never
			//be able to have a wild card be the first card in a meld.
			if (card_to_search != enemy_melds.at(meld_pos).at(0) && !card_to_search.isWild())
				preference_discard.push_back(card_to_search);
		}

		if (!card_to_search.isWild()) {
			no_wild_discard.push_back(card_to_search);
		}


	}

	if (preference_discard.size() != 0) {
		preferred_card = preference_discard.at(0);
		
		std::cout << "The CPU chose to get rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
		"In the CPU's hand, @" << preferred_card.get_point_value() << " points, and is not in any of the enemy's melds." << std::endl;
	}

	else if (no_wild_discard.size()!= 0) {
		static thread_local std::mt19937 g{ std::random_device{}() };
		static thread_local std::uniform_int_distribution<size_t> d{ 0,no_wild_discard.size() };
		preferred_card = no_wild_discard.at(d(g));

		std::cout << "The CPU chose to get rid of " << preferred_card.get_card_string() << " since it the lowest value  " <<
			"In the CPU's hand, @" << preferred_card.get_point_value() << " points, and wasn't a wild card." << std::endl;

		//https://stackoverflow.com/questions/44576857/randomly-pick-from-a-vector-in-c

	}
	else {
		static thread_local std::mt19937 g{ std::random_device{}() };
		static thread_local std::uniform_int_distribution<size_t> d{ 0,hand_container.size() };
		preferred_card = hand_container.at(d(g));
		std::cout << "The CPU had no choice, so it randomly chose a card, which ended up being: " << preferred_card.get_card_string() << std::endl;
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
	std::cout << "TODO" << std::endl;
}

bool Computer::draw(Deck &draw_decks)
{
	Hand player_hand = get_player_hand();
	Card top_of_discard = draw_decks.get_top_discard_pile();
	bool can_meld = player_hand.is_meldable(top_of_discard);

	if ((player_hand.get_size_of_hand() > 5 &&	can_meld) && (!draw_decks.get_discard_is_frozen())) {
		std::cout << "CPU: drawing discard pile: can meld with hand, hand isn't that small." << std::endl;
		std::vector<Card> picked_up_discard = draw_decks.draw_from_discard();
		add_to_hand(picked_up_discard);
		purge_red_threes();
		return false;
	}

	else if (!draw_decks.stock_is_empty()) {
		std::cout << "CPU: drawing from stock, because:";

		if (draw_decks.get_discard_is_frozen())
			std::cout << "the discard pile is frozen." << std::endl;
		else if (!can_meld)
			std::cout << "there are no cards in the CPU's hand that can meld with the card" << can_meld << std::endl;
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
	return true;
}

std::string Computer::get_player_type()
{
	return "Computer";
}

