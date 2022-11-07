/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */
#pragma once
class Player;
#include "Player.h"

class Computer : public Player {
public: 
	bool play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) override;
	void discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) override;
	void meld(std::vector<std::vector<Card>> enemy_melds) override;
	bool draw(Deck &draw_decks) override ;
	void strategy(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) override;

	
	void print_player_type() override;
	bool choose_to_go_out() override;
	virtual std::string get_player_type() const override;

};