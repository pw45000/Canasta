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

Game::~Game() {
	if (players.size() > 0) {
		delete players.at(0);
		delete players.at(1);
	}
}



void Game::main_menu()
{
	std::string input_string;


	int choice = 0;
	
	//to avoid stopping after the first return to main menu.
	do {
		std::cout << "Welcome to Canasta! Please pick an option:" << std::endl;
		std::cout << "1. New Game " << std::endl;
		std::cout << "2. Load Game" << std::endl;
		std::cout << "3. Exit" << std::endl;
		choice = validate_option_based_input(1, 3);
		switch (choice) {
		case 1:
			choose_player_type();			
			break;
		case 2: {
			Round loading_round;
			bool load_success = loading_round.load_game();
			if (load_success) {
				players = loading_round.get_players();
				main_game(loading_round);
			}
			else
				std::cout << "Failed to load file!" << std::endl;
			break;
		}
		case 3: {
			return;
		}
		default:
			std::cout << "Unknown behavior: unknown option." << std::endl;
		}
	} while (choice != 3);

}

void Game::choose_player_type()
{
	std::string input_string;


	
	int choice;
	//to avoid stopping after the first return to main menu.
	do {
		//because we have 3 options.
		std::cout << "Welcome to Canasta! Please select your preferred game type: " << std::endl;
		std::cout << "1. Player vs Player (PVP) " << std::endl;
		std::cout << "2. Player vs Computer (PVE)" << std::endl;
		std::cout << "3. Exit to Main Menu" << std::endl;
		choice = validate_option_based_input(1, 3);
		switch (choice) {
		case 1:
			//bypass the error of case transfer skipping initialization
		{

			players.push_back(new Human);
			players.push_back(new Human);

			main_game();


			return;
			break;
		}
		case 2:
			players.push_back(new Computer);
			players.push_back(new Human);

			main_game();
			return;
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
	auto player_1 = players.at(0);
	auto player_2 = players.at(1);
	bool has_quit = false;

	do {
		round_number++;
		Round game_round(players, round_number);
		has_quit = game_round.main_round(false);
		if (has_quit) break;
		std::cout << "Would you like to another round?" << std::endl;
		std::cout << "1. Yes" << std::endl;
		std::cout << "2. No" << std::endl;
		choice = validate_option_based_input(1, 2);
		player_1->clear_hand_and_meld();
		player_2->clear_hand_and_meld();
	} while (choice != 2 && has_quit == false);
	
	if(!has_quit)
		decide_winner();

	delete players.at(0);
	delete players.at(1);
	players.clear();

}



void Game::main_game(Round &loaded_round)
{
	int choice = 0;
	int round_number = 0;
	int loop_count = 0;
	
	auto player_1 = players.at(0);
	auto player_2 = players.at(1);
	bool has_quit = false;

	do {
		if (loop_count == 0)
			has_quit = loaded_round.main_round(true);
		else {
			Round game_round(players, round_number);
			has_quit = game_round.main_round(false);
		}
		if (has_quit) break;
		
		std::cout << "Would you like to another round?" << std::endl;
		std::cout << "1. Yes" << std::endl;
		std::cout << "2. No" << std::endl;
		choice = validate_option_based_input(1, 2);
		round_number++;
		loop_count++;
		player_1->clear_hand_and_meld();
		player_2->clear_hand_and_meld();
		
	} while (choice != 2 && has_quit == false);

	if (!has_quit)
		decide_winner();

	delete players.at(0);
	delete players.at(1);
	players.clear();

}

//https://stackoverflow.com/questions/20814703/should-i-delete-static-object-in-c
//empty for now due to this.

Game::Game(const Game& other_game)
{
	players = other_game.players;
	round = other_game.round;
}

void Game::decide_winner()
{
	auto player_1 = players.at(0);
	auto player_2 = players.at(1);


	int player_1_score = player_1->get_score();
	int player_2_score = player_2->get_score();

	if (player_1_score > player_2_score) {
		std::cout << "Victory for life: Player 1 (" << player_1->get_player_type() << ") with a score of " << player_1_score << std::endl;
		std::cout << "Dejected Loser: Player 2 (" << player_2->get_player_type() << ") with a score of " << player_2_score << std::endl;
	}

	else {
		std::cout << "Victory for life: Player 2 (" << player_2->get_player_type() << ") with a score of " << player_2_score << std::endl;
		std::cout << "Dejected Loser: Player 1 (" << player_1->get_player_type() << ") with a score of " << player_1_score << std::endl;
	}

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
int validate_option_based_input(int lower_bound, int upper_bound, bool special_option)
{
	std::string input;
	bool is_valid = false;
	int converted_option = 0;
	do {

		std::cin >> input;
		std::cin.clear();
		std::cin.ignore(10000000, '\n');

		if (input == "-1")
			return -1;


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

	} while (is_valid != true);

	return converted_option;
}
//parts taken from past project VC8000, plug github link