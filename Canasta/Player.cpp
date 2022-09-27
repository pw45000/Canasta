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
	has_decided_to_go_out = false;
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

bool Player::create_meld(Card first, Card second, Card third)
{
	return player_hand.create_meld(first, second, third);
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

void Player::print_vector(std::vector<Card> vector_to_print)
{
	std::cout << "[ ";
		for (Card card : vector_to_print) {
			std::cout << card.get_card_string() << " ";
	}
	std::cout << "] " << std::endl;
}

void Player::print_meld(int meld_pos)
{
	Hand player_hand = get_player_hand();
	std::vector<std::vector<Card>> meld_container = player_hand.get_meld();
	print_vector(meld_container.at(meld_pos));
}

int Player::get_score_from_meld(int meld_pos)
{
	return 0;
}

void Player::sort_melds(std::vector<std::vector<Card>> &melds_to_sort)
{
	int first_card_pos = 0;
	std::sort(melds_to_sort.begin(), melds_to_sort.end(),
		[first_card_pos](const std::vector<Card>& lhs, const std::vector<Card>& rhs) {
			return lhs.size() > rhs.size();
		});
}

std::vector<Card> Player::get_wild_cards_from_vector(std::vector<Card> arbitrary_card_vect)
{
	std::vector<Card> vector_of_wild_cards; 
	for (int card_pos = 0; card_pos < arbitrary_card_vect.size(); card_pos++) {
		if (arbitrary_card_vect.at(card_pos).isWild() && arbitrary_card_vect.at(card_pos).get_has_transferred() == false) {
			vector_of_wild_cards.push_back(arbitrary_card_vect.at(card_pos));
		}
	}
	return vector_of_wild_cards;
}

bool Player::meld_of_card_exists(Card card_to_search)
{
	return player_hand.meld_exits_already(card_to_search);
}

int Player::get_absolute_pos_from_relative_meld(std::vector<Card> arbitrary_meld_vect)
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




bool Player::get_go_out_decision() const
{
	return has_decided_to_go_out;
}

void Player::set_go_out_decision(bool go_out_decision)
{
	has_decided_to_go_out = go_out_decision;
}

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

int Player::get_dangerous_amount_of_cards(std::vector<std::vector<Card>> enemy_melds)
{
	Hand player_hand = get_player_hand();
	int amount_of_dangerous_cards = 0;
	std::vector<Card> hand_container = player_hand.get_hand_container();
	for (int card_pos = 0; card_pos < hand_container.size(); card_pos++) {
		for (int meld_pos = 0; meld_pos < enemy_melds.size(); meld_pos++) {
			if (hand_container.at(card_pos).get_card_face() == 
			enemy_melds.at(meld_pos).at(0).get_card_face()
			&&enemy_melds.at(meld_pos).size()==6) {
				amount_of_dangerous_cards++;
			}
		}
	}
	return amount_of_dangerous_cards;
}

bool Player::is_dangerous_card(Card potential_danger_card, std::vector<std::vector<Card>> enemy_melds)
{
	for (int meld_pos = 0; meld_pos < enemy_melds.size(); meld_pos++) {
		if (potential_danger_card.get_card_face() == enemy_melds.at(meld_pos).at(0).get_card_face())
			return true;
	}
	return false;
}




