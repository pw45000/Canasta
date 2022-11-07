/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */

#include "Computer.h"
#include <iostream>

/* *********************************************************************
Function Name: play
Purpose: The main gameplay loop for each player.
Parameters:
			 draw_decks: a Deck reference which represents the discard and stock pile from the Round.
			 enemy_melds: a vector of vectors of Card which represents the enemy's melds.
Return Value: none
Assistance Received: none
********************************************************************* */
bool Computer::play(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	bool immeadiate_break;


	immeadiate_break = go_out();
	if (immeadiate_break) return true;

	immeadiate_break = draw(draw_decks);
	if (immeadiate_break) return true;

	meld(enemy_melds);
	immeadiate_break = go_out();
	if (immeadiate_break) return true;

	discard(draw_decks, enemy_melds);
	immeadiate_break = go_out();
	if (immeadiate_break) return true;

	return false;
}


void Computer::discard(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	strategy_discard(draw_decks, enemy_melds, get_player_type());

}



void Computer:: meld(std::vector<std::vector<Card>> enemy_melds)
{
	strategy_meld(enemy_melds, get_player_type());
}

bool Computer::draw(Deck &draw_decks)
{
	return strategy_draw(draw_decks, get_player_type());

}
/* *********************************************************************
Function Name: print_player_type
Purpose: Prints the Computer's player type.
Parameters: none.
Return Value: none
Assistance Received: none
********************************************************************* */
void Computer::print_player_type()
{
	std::cout << "Computer";
}
/* *********************************************************************
Function Name: choose_to_go_out
Purpose: Give a decision as to if the Computer wants to go out.
Parameters: none.
Return Value: bool representing if the Computer chose to go out.
Assistance Received: none
********************************************************************* */
bool Computer::choose_to_go_out()
{
	std::cout << "The computer chose to go out since it likes 100 point bonuses." << std::endl;
	return true;
}

/* *********************************************************************
Function Name: strategy
Purpose: Overrides strategy for the Computer, and prints out a message stating it doesn't need it's own strategy.
Parameters: 
			 draw_decks: a Deck reference representing the discard and stock pile from Round.
			 enemy_melds: a vector of vectors of Cards representing the enemy's melds.
Return Value: none.
Assistance Received: none
********************************************************************* */
void Computer::strategy(Deck& draw_decks, std::vector<std::vector<Card>> enemy_melds)
{
	std::cout << "The computer has it's own strategy, so it doesn't need advice..." << std::endl;
}

/* *********************************************************************
Function Name: get_player_type
Purpose: returns the Computer's player type.
Parameters: none.
Return Value: string representing the Computer's player type.
Assistance Received: none
********************************************************************* */
std::string Computer::get_player_type() const
{
	return "Computer";
}

