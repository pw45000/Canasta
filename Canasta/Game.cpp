#include "Game.h"
/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Cansta P1*
* Class : class numberand name here*
* Date : 9/13/22*
*********************************************************** */

Game::Game()
{
	round = 0;

}

void Game::main_menu()
{
	std::string input_string;
	std::cout << "Welcome to Canasta! Please pick an option:" << std::endl;
	std::cout << "1. New Game " << std::endl;
	std::cout << "2. Load Game" << std::endl;
	std::cout << "3. Exit" << std::endl;

	
	
	do {
		std::cin >> input_string;
		if (input_string == "1") {
			std::cin.clear();
			choose_player_type();

			//scrappy way of redisplaying the prompt. 
			std::cout << "Welcome to Canasta! Please pick an option:" << std::endl;
			std::cout << "1. New Game " << std::endl;
			std::cout << "2. Load Game" << std::endl;
			std::cout << "3. Exit" << std::endl;
		}
		else if (input_string == "2")
			std::cout << "TODO: IMPLEMENT LOAD" << std::endl;
		else if (input_string == "3")
			//We'll need this, or there's some weird behavior with recursion....
			exit(0);
		else {
			std::cout << "That's not a valid option. Please pick from one of the above!" << std::endl;
		}
	}
	while (input_string != "3");

}

void Game::choose_player_type()
{
	std::string input_string;
	std::cout << "Welcome to Canasta! Please select your preferred game type: " << std::endl;
	std::cout << "1. Player vs Player (PVP) " << std::endl;
	std::cout << "2. Player vs Computer (PVE)" << std::endl;
	std::cout << "3. Exit to Main Menu" << std::endl;


	do {
		std::cin >> input_string;

		if (input_string == "1") {
			Human player1;
			Human player2;

			//I was getting an error before because I forgot to 
			//set Human as a derived class as player. 
			players.push_back(&player1);
			players.push_back(&player2); 
			return;
		}
		else if (input_string == "2")
			std::cout << "TODO: IMPLEMENT PVE" << std::endl;
		else if (input_string == "3")
			return;
		else {
			std::cout << "That's not a valid option. Please pick from one of the above!" << std::endl;
		}
	} 
	while (input_string != "3");
}
