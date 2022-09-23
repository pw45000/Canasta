#include "Player.h"
/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Cansta P1*
* Class : class numberand name here*
* Date : 9/13/22*
*********************************************************** */

Player::Player()
{
	score = 0;
	player_hand;
}

int Player::get_score()
{
	return score;
}

bool Player::has_canasta()
{
	return player_hand.has_canasta();
}

bool Player::hand_empty()
{
	return player_hand.hand_empty();
}

void Player::add_to_hand(Card card_to_be_added)
{
	player_hand.add_to_hand(card_to_be_added);
}

void Player::add_to_hand(std::vector<Card> cards_to_be_added)
{
	player_hand.add_to_hand(cards_to_be_added);
}

void Player::create_special_meld(Card card_to_be_added)
{
	player_hand.create_meld(card_to_be_added);
}

bool Player::create_meld(std::vector<Card> potential_meld)
{
	Card meld_card_1 = potential_meld.at(0);
	Card meld_card_2 = potential_meld.at(1);
	Card meld_card_3 = potential_meld.at(2);
	return player_hand.create_meld(meld_card_1, meld_card_2, meld_card_3);

}

void Player::purge_red_threes()
{
	player_hand.purge_red_threes();
}

bool Player::lay_off(Card addition, int meld_number)
{
	return player_hand.lay_off(addition, meld_number);
}

Hand Player::get_player_hand()
{
	return player_hand;
}

void Player::sort_hand()
{
	player_hand.sort();
}

void Player::temp_print_hand()
{
	std::cout << std::endl;
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

bool Player::transfer_card(Card wild_card, int wild_origin, int meld_number)
{
	return player_hand.transfer_wild_card(wild_card, wild_origin, meld_number);
}

void Player::clear_transfer_states()
{
	player_hand.clear_transfer_states();
}

bool Player::remove_from_hand(Card discard_card)
{
	return player_hand.remove_from_hand(discard_card);
}

void Player::clear_hand()
{
	player_hand.clear_all_data();
}

bool Player::can_go_out()
{
	if (player_hand.hand_empty() == true && has_canasta())
		return true;
	else
		return false;
}

void Player::add_to_score(int score_addition)
{
	score += score_addition;
}

void Player::set_player_score(int score)
{
	this->score = score;
}

void Player::set_meld(std::vector<std::vector<Card>> meld_container)
{
	player_hand.set_meld(meld_container);
}

void Player::set_hand(std::vector<Card> hand_container)
{
	player_hand.set_hand(hand_container);
}

void Player::clear_hand_and_meld()
{
	player_hand.clear_all_data();
}

void Player::meld() {
	return;
}


bool Player::go_out()
{
	bool able_to_go_out = can_go_out();
	bool did_chose_to_go_out = false;
	if (able_to_go_out) {
		did_chose_to_go_out = choose_to_go_out();

		if (did_chose_to_go_out) {
			add_to_score(100);
		}
	}
	return did_chose_to_go_out;
}


