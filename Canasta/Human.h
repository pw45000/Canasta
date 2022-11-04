/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */
#pragma once
class Human;
class Player;
#include "Player.h"



class Human : public Player {
public: 
	bool play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) override ;
	bool draw(Deck &draw_decks) override;
	void meld(std::vector<std::vector<Card>> enemy_melds) override;
	void discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) override;
	void print_player_type() override;
	bool choose_to_go_out() override;
	virtual std::string get_player_type() override;
	void print_enemy_meld(std::vector<std::vector<Card>> enemy_meld) const;
	void strategy(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) override;
	void strategy_draw(Deck& draw_decks) const;
	void strategy_meld(std::vector<std::vector<Card>> enemy_melds) const; 
	void strategy_discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) const;

	std::vector<Card> validate_comma_input();
};