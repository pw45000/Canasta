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

	int choice = validate_option_based_input(1, 3);
	
	//to avoid stopping after the first return to main menu.
	do {
		switch (choice) {
		case 1:
			choose_player_type();

			//scrappy way of redisplaying the prompt. 
			std::cout << "Welcome to Canasta! Please pick an option:" << std::endl;
			std::cout << "1. New Game " << std::endl;
			std::cout << "2. Load Game" << std::endl;
			std::cout << "3. Exit" << std::endl;
			choice = validate_option_based_input(1, 3);
			break;
		case 2:
			std::cout << "TODO: IMPLEMENT LOAD" << std::endl;
			return;
			break;
		case 3:
			//We'll need this, or there's some weird behavior with recursion....
			return;
		default:
			std::cout << "Unknown behavior: unknown option." << std::endl;
		}
	} while (choice != 3);

}

void Game::choose_player_type()
{
	std::string input_string;
	std::cout << "Welcome to Canasta! Please select your preferred game type: " << std::endl;
	std::cout << "1. Player vs Player (PVP) " << std::endl;
	std::cout << "2. Player vs Computer (PVE)" << std::endl;
	std::cout << "3. Exit to Main Menu" << std::endl;

	
	int choice;
	//to avoid stopping after the first return to main menu.
	do {
		//because we have 3 options.
		choice = validate_option_based_input(1, 3);
		switch (choice) {
		case 1:
			//bypass the error of case transfer skipping initialization
		{
			Human player1;
			Human player2;
			players.push_back(&player1);
			players.push_back(&player2);

			main_game();


			return;
			break;
		}
		case 2:
			std::cout << "TODO: IMPLEMENT PVE" << std::endl;
			break;
		case 3:
			return;
			break;
		default:
			std::cout << "Unknown behavior: unknown option." << std::endl;
			break;
		}
	} while (choice != 3);
}

void Game::main_game()
{
	int choice = 0;
	int round_number = 0;

	do {
		round_number++;
		Round game_round(players, round_number);
		game_round.main_round();
		std::cout << "Would you like to play again?" << std::endl;
		std::cout << "1. Yes" << std::endl;
		std::cout << "2. No" << std::endl;
		choice = validate_option_based_input(1, 2);
	} while (choice != 2);
	players.clear();
}

//https://stackoverflow.com/questions/20814703/should-i-delete-static-object-in-c
//empty for now due to this.
Game::~Game()
{
}

Game::Game(const Game& other_game)
{
	players = other_game.players;
	round = other_game.round;
}

int validate_option_based_input(int lower_bound, int upper_bound)
{
	std::string input;
	bool is_valid = false;
	int converted_option = 0;
	do {
		
		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(10000000, '\n');
		
		if (std::all_of(input.begin(), input.end(), ::isdigit)) {
			converted_option = std::stoi(input);

			if (converted_option >= lower_bound && converted_option <= upper_bound) {
				is_valid = true;
			}
			else {
				std::cout << "Input Error: selected number is not an option." << std::endl;
			}
		}
		else {
			std::cout << "Input Error: inputted string is not numeric." << std::endl;
		}

	} 
	while (is_valid != true); 
	
	return converted_option;
}
//parts taken from past project VC8000, plug github link