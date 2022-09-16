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

void Player::purge_red_threes()
{
	player_hand.purge_red_threes();
}

Hand Player::get_player_hand()
{
	return player_hand;
}

void Player::play(Deck& draw_decks)
{
	std::cout << "TODO" << std::endl;
}

bool Player::draw(Deck &draw_decks)
{
	return false;
}

void Player::meld()
{
	std::cout << "TODO" << std::endl;
}

void Player::discard()
{
	std::cout << "TODO" << std::endl;
}


