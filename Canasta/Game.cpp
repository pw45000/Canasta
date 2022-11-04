/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */
#include "Game.h"


/* *********************************************************************
Function Name: Game
Purpose: The default Game constructor. 
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
Game::Game()
{
	round = 0;
	players.reserve(2);

}
/* *********************************************************************
Function Name: Game
Purpose: The Game destructor. Deletes any new players allocated on the heap.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
Game::~Game() {
	if (players.size() > 0) {
		delete players.at(0);
		delete players.at(1);
	}
}

/* *********************************************************************
Function Name: Game
Purpose: The Game copy constructor. Made to satisfy the rule of 3.
Parameters: other_game: a const reference to another Game Class from which to be copied.
Return Value: none
Assistance Received: none
********************************************************************* */
Game::Game(const Game& other_game)
{
	players = other_game.players;
	round = other_game.round;
}


/* *********************************************************************
Function Name: main_menu
Purpose: The function which represents the main menu of the game.
Parameters: none
Algorithm: 
			1. Creates a do-while loop to simulate a menu playing until a player quits. 
				In this case, the case to break this loop will be 3. 
			2. For each iteration of this do while loop, display a prompt with 3 options: 
				New Game, Load Game, Exit, and validate a range based input. 
			3. Depending on each choice, either:
				a) make a new game by choose_player_type
				b) Attempt to load a round, and if successful, proceed to the loaded round.
				c) Exit the game.
Local variables: 
					 choice, an int which represents the input of the user.
					 loading_Round, a Round class which represents a new round from which will be loaded into.
					 load_success, a bool which represents if the new round is successfully loaded.
Return Value: none
Assistance Received: none
********************************************************************* */
void Game::main_menu()
{
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
				std::cout << "Failed to load file or the user inputted 0 to quit!" << std::endl;
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

/* *********************************************************************
Function Name: choose_player_type
Purpose: The function which represents choosing the player type after selecting new game.
Parameters: none
Algorithm:
			1. Creates a do-while loop to simulate a menu playing until a player quits.
				In this case, the case to break this loop will be 3.
			2. For each iteration of this do while loop, display a prompt with 3 options:
				Player vs Player, Player vs Computer, Exit to Main Menu, and validate a range based input.
			3. Depending on each choice, either:
				a) Make a new game by pushing two new Humans to players and then call main_game to play the game.
				b) Make a new game by pushing one Human and one Computer(AI) to players and then call main_game to play the game.
				c) Exit to main menu.
Local variables: 
					 choice: an integer which represents the chosen input.
Return Value: none
Assistance Received: none
********************************************************************* */
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


/* *********************************************************************
Function Name: main_game
Purpose: The function which acts the main game loop, including taking care of score, players, Rounds, etc...
Parameters: none
Algorithm:
			1. Create a do-while loop to enclose input regarding whether to play another round or not.
				this loop will break if the player has quit or the player chose not to player another around.
			2. Create a new Round object, constructing with the Game's players and tracked round number.
			3. Call the round object with false, since a round hasn't been loaded. The round will return if the player has quit.
			4. If the player hasn't quit and the round is over, ask if they want to play another round, and validate the prompted
				inputed choice. Each time, each player's hand is cleared.
			5. Once the player decides to end the round or the round ends, see if they quit. If not, display who won.
			6. Clear the players and delete the memory allocated on the heap representing the players.
Local variables:
					 choice: an integer which represents the chosen input in the input loop.
					 round_number: an integer representing the current round number.
					 player_1: a Player* representing the first player.
					 player_2: a Player* representing the second player.
					 has_quit: a bool representing if the player quit or not.

Return Value: none
Assistance Received: none
********************************************************************* */
void Game::main_game()
{
	int choice = 0;
	int round_number = 0;
	Player* player_1 = players.at(0);
	Player* player_2 = players.at(1);
	bool has_quit = false;

	do {
		round_number++;
		Round game_round(players, round_number);
		has_quit = game_round.main_round(false);
		if (!has_quit) {
			std::cout << "Would you like to another round?" << std::endl;
			std::cout << "1. Yes" << std::endl;
			std::cout << "2. No" << std::endl;
			choice = validate_option_based_input(1, 2);
		}
		player_1->clear_hand_and_meld();
		player_2->clear_hand_and_meld();
	} while (choice != 2 && has_quit == false);
	
	if(!has_quit)
		decide_winner();

	delete players.at(0);
	delete players.at(1);
	players.clear();

}


/* *********************************************************************
Function Name: main_game
Purpose: The function which acts the main game loop, including taking care of score, players, Rounds, etc...
Parameters: loaded_round, a Round reference to the round currently loaded in the main menu of Game.
Algorithm:
			1. Create a do-while loop to enclose input regarding whether to play another round or not.
				this loop will break if the player has quit or the player chose not to player another around.
			2. Create a new Round object, constructing with the Game's players and tracked round number.
			3. Either the following will happen based on the loop_count being 0(loaded) or >0 (past loaded round): 
					a) Call the round object with false, since a round hasn't been loaded. The round will return if the player has quit.
					b) Call the round object with true, since a round has been loaded. The round will return if a player has quit.
			4. If the player hasn't quit and the round is over, ask if they want to play another round, and validate the prompted
				inputed choice. Each time, each player's hand is cleared.
			5. Once the player decides to end the round or the round ends, see if they quit. If not, display who won.
			6. Clear the players and delete the memory allocated on the heap representing the players.
Local variables:
					 choice: an integer which represents the chosen input in the input loop.
					 round_number: an integer representing the current round number.
					 loop_count: an integer representing how many times a round has been played since being loaded.
					 player_1: a Player* representing the first player.
					 player_2: a Player* representing the second player.
					 has_quit: a bool representing if the player quit or not.

Return Value: none
Assistance Received: none
********************************************************************* */
void Game::main_game(Round &loaded_round)
{
	int choice = 0;
	int round_number = 0;
	int loop_count = 0;
	
	Player* player_1 = players.at(0);
	Player* player_2 = players.at(1);
	bool has_quit = false;

	do {
		if (loop_count == 0)
			has_quit = loaded_round.main_round(true);
		else {
			Round game_round(players, round_number);
			has_quit = game_round.main_round(false);
		}
		
		if (!has_quit) {
			std::cout << "Would you like to another round?" << std::endl;
			std::cout << "1. Yes" << std::endl;
			std::cout << "2. No" << std::endl;
			choice = validate_option_based_input(1, 2);
			round_number++;
			loop_count++;
		}
		player_1->clear_hand_and_meld();
		player_2->clear_hand_and_meld();
		
	} while (choice != 2 && has_quit == false);

	if (!has_quit)
		decide_winner();

	delete players.at(0);
	delete players.at(1);
	players.clear();
}



/* *********************************************************************
Function Name: decide_winner
Purpose: Gets the total score for each player and then annouces the winner.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */

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



/* *********************************************************************
Function Name: validate_option_based_input
Purpose: Validating option based input in a lower and upper bound.
Parameters: 
			  lower_bound, an int that represents the lower bound of acceptable input.
			  upper_bound, an int that represents the upper bound of acceptable input.
Algorithm:
			 1). Use a do-while loop to simulate continous input which will break when input is valid. 
			     Within this input, prior to input,
				  the cin buffer is cleared and all prior input(including newlines) is ignored. 
			 2). There are cases in which the input will always be false: 
						a) The input is not within upper or lower bounds.
						b) The input is not numeric.
			 3). If the input is none of these cases, then convert the string into an integer and store it, and set the input to be valid.
			 4). Return the valid inputted choice. 

			
Local variables:


Return Value: none
Assistance Received: none
********************************************************************* */

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


/* *********************************************************************
Function Name: validate_option_based_input
Purpose: Validating option based input in a lower and upper bound.
Parameters:
			  lower_bound, an int that represents the lower bound of acceptable input.
			  upper_bound, an int that represents the upper bound of acceptable input.
			  special_option, a bool that tells if the function should accept -1 as an acceptable input.
Algorithm:
			 1). Use a do-while loop to simulate continous input which will break when input is valid.
				  Within this input, prior to input,
				  the cin buffer is cleared and all prior input(including newlines) is ignored.
			 2). There are cases in which the input will always be false:
						a) The input is not within upper or lower bounds.
						b) The input is not numeric.
			 3). If the input is none of these cases or is -1, 
			 then convert the string into an integer and store it, and set the input to be valid.
			 4). Return the valid inputted choice.


Local variables:


Return Value: none
Assistance Received: Some parts of the input validation came from past projects of mine, 
such as the VC8000 computer, https://github.com/pw45000/VC-8000.
********************************************************************* */

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