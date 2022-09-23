#pragma once
class Player;
#include "Player.h"

class Computer : public Player {
public: 
	bool play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) override;
	void discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds) override;
	void meld();
	bool draw(Deck &draw_decks) override ;
	void print_player_type() override;
	bool choose_to_go_out() override;

	virtual std::string get_player_type() override;

private:
};