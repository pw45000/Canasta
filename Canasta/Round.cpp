/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Canasta C++ Project 1*
* Class : CMPS-366-01*
* Date : 9/28/22*
*********************************************************** */

#include "Round.h"

/* *********************************************************************
Function Name: Round
Purpose: The default constructor for the Round class.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
Round::Round()
{

	next_player = 0;
	round_number = 0;
}

/* *********************************************************************
Function Name: Round
Purpose: The non default constructor for the class, including a player list and round number from Game.
Parameters: 
			  players: a vector of Player pointers representing the players in the Game. 
			  round_number: an int representing the number of the round.
Return Value: none.
Assistance Received: none
********************************************************************* */
Round::Round(std::vector<Player*> players, int round_number)
{
	this->players = players;
	this->round_number = round_number;
	next_player = 0;
}


/* *********************************************************************
Function Name: Round
Purpose: The copy constructor for the Round class.
Parameters: 
			  other_round, a const reference to a Round class from which to copy from.
Return Value: none
Assistance Received: none
********************************************************************* */
Round::Round(const Round& other_round)
{
	this->next_player = other_round.next_player;
	this->stock_and_discard = other_round.stock_and_discard;
	this->players = other_round.players;

}
/* *********************************************************************
Function Name: Round
Purpose: The destructor for the Round class.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
Round::~Round()
{
	stock_and_discard.clear_discard();
}







/* *********************************************************************
Function Name: coin_toss
Purpose: Does a coin toss and asks the second player heads or tails, will decide who will go first depending on the coin_toss.
Parameters: none
Algorithm: 
			 1. Create a seed and uniform distribution based on the device between 1 and 2, representing heads and tails.
			 2. Ask the player for a validated input of 1 or 2 representing heads or tails. 
			 3. Depending on the answer, either player 2 will go first if they guessed correctly or
				 Player 1 if they guessed incorrectly.
Local variables: 
		1. seed1, a chrono based variable that represents a seed based on the system.
		2. dev, a std::random device which decides the device to use.
		3. flipped_coin: a value between 1 or 2 represented by heads or tails. 
		4. choice, an int representing if the player chose heads or tails.
Return Value: int, representing the next player, decided by the coin toss.
Assistance Received: I read up on random numbers at the following article: 
							https://stackoverflow.com/questions/59644856/measuring-time-to-generate-better-random-numbers-in-c
********************************************************************* */
int Round::coin_toss()
{
	auto seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::random_device dev;
	std::uniform_int_distribution<std::mt19937::result_type> coin(1, 2);

	auto flipped_coin = coin(dev);
	std::cout << "Player 2! Heads or Tails?" << std::endl;
	std::cout << "1. Heads" << std::endl;
	std::cout << "2. Tails" << std::endl;
	int choice = validate_option_based_input(1, 2);

	if (choice == flipped_coin) {
		std::cout << "Player 1 goes first! They guessed correctly, the value is " << ((flipped_coin==1) ? "Heads" : "Tails") << std::endl;
		return 2;
	}

	else {
		std::cout << "Player 2 goes first! Player 1 guessed incorrectly the value is "<< ((flipped_coin == 1) ? "Heads" : "Tails") << std::endl;
		return 1; 
	}
	

}

/* *********************************************************************
Function Name: main_round
Purpose: To act as the main round gameplay loop.
Parameters: has_loaded_file, a boolean representing if a file has been loaded to start the round.
Algorithm:
			 1. See if a file has been loaded or not. If so, start the main gameplay do while loop.
			 2. If not, see if the scores are the same. If they are, do a coin toss. 
				 If not, whichever player with a higher score goes first.
			 3. The do while loop will continue until the round is over or the player quits. 
			 4. In the do while loop, there is are 4 options a player can take:
				 (this in of itself is a do while loop which is broken on save or the option to continue.
				a) Save (which has the two options to save and continue or to save and quit)
				b) Take the turn (which simply continues onward)
				c) Quit the game, which breaks the loop and returns to main_game.
				d) Ask for advice, which starts another do while loop, where the player can ask for help regarding the following:
					i). Drawing
					ii. Melding
					iii.Discarding
					iv.Exit
				5. If the player continues onward, the round will decide who goes depending on the next player.
				6. In a player's turn, they are called with their play function which passes the enemy melds.
					Each turn, a player's transfer states are cleared, so the player can transfer wild cards once per turn.
				7. This goes on until a player quits, at which point the scores are output and tallied.
				8. At almost each of these steps, information regarding the round is output.
Local variables:
	1. player1, a Player* that represents player 1. 
	2. player2, a Player* that represents player 2.
	3. menu_choice, an int that represents the choice a player gives in a input based menu.
Return Value: bool that returns if a player quit or not.
Assistance Received: none
********************************************************************* */
bool Round::main_round(bool has_loaded_file)
{
	auto player1 = players.at(0);
	auto player2 = players.at(1);
	int menu_choice = 0;
	bool round_is_over = false;

	if (has_loaded_file == false) {
		if (player1->get_score() == player2->get_score()) {
			//the coin toss decides which player is going next.
			//so, we'll need to set the result for it's return.
			set_next_player(coin_toss());
		}

		else {
			if (player1->get_score() > player2->get_score())
				next_player = 1;
			else
				next_player = 2;
		}


		initial_draw();
		sort_players_hands();
	}
	output_round_info();
	
	do {
		do {
			menu_choice = pre_turn_menu();

			switch (menu_choice) {
			case 1: {
				std::cout << "How would you like to save?" << std::endl;
				std::cout << "1. save and continue" << std::endl;
				std::cout << "2. save and quit" << std::endl;
				int save_choice = validate_option_based_input(1, 2);
				sort_players_hands();
				save_round();
				if (save_choice == 2)
					return true;
				break;
			}
			case 2:
				continue;
				break;
			case 3:
				return true;
				break;
			case 4: {
				auto player_to_give_advice_pos = get_next_player() - 1;
				auto player_to_give_advice = players.at(player_to_give_advice_pos);
				auto enemy_player = (player_to_give_advice == 0) ? players.at(1) : players.at(0);
				Hand enemy_hand = enemy_player->get_player_hand();
				std::vector<std::vector<Card>> enemy_meld = enemy_hand.get_meld();
				
				player_to_give_advice->strategy(stock_and_discard, enemy_meld);

				break;
			}
			}
			//break if the option is to quit the game or to take the turn.
		} while (menu_choice != 3 && menu_choice != 2);
		output_round_info();

		if (round_is_over == true) break;
		
		
		if (next_player == 1) {
			output_round_info();

			Hand enemy_hand = player2->get_player_hand();
			std::vector<std::vector<Card>> enemy_meld = enemy_hand.get_meld();
			round_is_over = player1->play(stock_and_discard, enemy_meld);
			player1->clear_transfer_states();
			//we'll need to increment next player to pass the turn.
			next_player++;
		}


		else {
			Hand enemy_hand = player1->get_player_hand();
			std::vector<std::vector<Card>> enemy_meld = enemy_hand.get_meld();
			round_is_over = player2->play(stock_and_discard, enemy_meld);
			player2->clear_transfer_states();
			//since 2 is bigger than 1, we'll need to decrement 
			//to get the next player to be 1.
			next_player--;
		}
		output_round_info();
	} while (round_is_over == false && menu_choice != 4);



	tally_score();
	output_round_info();
	
	return false;

}

/* *********************************************************************
Function Name: initial_draw
Purpose: Drawing the initial amount of cards. 
Parameters: none
Algorithm: 
			1. Draw 15 cards for each player. If the player drew a red three, draw again. 
Local variables:
	1. initial_draw_count: an int for storing how many cards are drawn in the initial draw of a card.
	2. drawn_card: a Card representing the Card drawn from the stock pile.
	3. drawn_string: the string that represents drawn_card in string form.
Return Value: none.
Assistance Received: none
********************************************************************* */
void Round::initial_draw()
{
	//for each player, draw 15 cards from the stockpile.
	int initial_draw_count = 15;
	for (int card_count = 0; card_count < players.size(); card_count++) {
		for (int card = 0; card < initial_draw_count; card++) {
			Card drawn_card = stock_and_discard.draw_from_stock();
			std::string drawn_string = drawn_card.get_card_string();

			if (drawn_string == "3H" || drawn_string == "3D") {
				std::cout << "Lucky you! Player " << card_count + 1 << ", you got a red three on the initial draw!" << std::endl;
				players.at(card_count)->create_special_meld(drawn_card);
				card--;
			}
			else {
				players.at(card_count)->add_to_hand(drawn_card);
			}
		}
	}
}
/* *********************************************************************
Function Name: get_next_player
Purpose: Drawing the initial amount of cards.
Parameters: none
Return Value: an int which returns the next player in the Round.
Assistance Received: none
********************************************************************* */
int Round::get_next_player() const
{
	return next_player;
}

/* *********************************************************************
Function Name: set_next_player
Purpose: Drawing the initial amount of cards.
Parameters: next_player: an int which represents the next player
Return Value: an int which returns the next player in the Round.
Assistance Received: none
********************************************************************* */
void Round::set_next_player(int next_player)
{
	if (next_player==1 || next_player ==2)
		this->next_player = next_player;
}

/* *********************************************************************
Function Name: output_round_info
Purpose: Outputting all the round's info, including the round, score, player hand/melds, etc..
Parameters: none
Return Value: an int which returns the next player in the Round.
Algorithm: 
			1. Store variable to players, and gets the player hand from said variable. 
			2. Prints the Round number, Player 1 type with all player information, 
			3. Prints Player 2's information.
			4. Prints the stock pile and discard pile. 
			5. Prints the next player.
Assistance Received: none
********************************************************************* */
void Round::output_round_info() const
{
	auto player_1 = players.at(0);
	auto player_1_hand = player_1->get_player_hand();
	auto player_2 = players.at(1);
	auto player_2_hand = player_2->get_player_hand();

	std::cout << "Round: " << round_number << "\n" << std::endl;


	player_1->print_player_type();
	std::cout <<":"<< std::endl;
	std::cout << "   Score: " << player_1->get_score() << std::endl;

	std::cout << "   Hand: ";
	player_1_hand.print_hand();
	std::cout << "   Melds: ";
	player_1_hand.print_melds();
	std::cout << "\n" << std::endl;


	player_2->print_player_type();
	std::cout << ":" << std::endl;
	std::cout << "   Score: " << player_2->get_score() << std::endl;

	std::cout << "   Hand: ";
	player_2_hand.print_hand();
	std::cout << "   Melds: ";
	player_2_hand.print_melds();
	std::cout << "\n" << std::endl;

	std::cout << "Stock: ";
	stock_and_discard.print_stock_pile();
	std::cout << "Discard Pile: ";
	stock_and_discard.print_discard_pile();

	std::cout<<std::endl;
	std::cout << "Next Player: ";
	(next_player == 1) ? player_1->print_player_type() : player_2->print_player_type();
	std::cout << std::endl;

	std::cout << std::endl;
}

/* *********************************************************************
Function Name: sort_player_hands
Purpose: Drawing the initial amount of cards.
Parameters: next_player: an int which represents the next player
Return Value: an int which returns the next player in the Round.
Assistance Received: none
********************************************************************* */
void Round::sort_players_hands()
{
	for (int plr_pos = 0; plr_pos < players.size(); plr_pos++)
		players.at(plr_pos)->sort_hand();
}

/* *********************************************************************
Function Name: pre_turn_menu
Purpose: Displays the pre turn menu.
Parameters: next_player: an int which represents the next player
Return Value: an int which returns the next player in the Round.
Algorithm: 
			 1. Receive the type of the next player. 
			 2. Depending on if the next player is human, a computer, or something else:
				a) If it's human, display a menu with 4 options (advice included) and validate input.
				b) If it's a computer, display a menu with 3 options (advice excluded) and validate input.
				c) If it's neither, return a number representing an error.
Local variables: 
					next_player: an int representing the numeric value of the next player.
					next_player_type: a string representing the next player's type, i.e. "Human" or "Computer", typically.
					error_number: an int representing an error code, -999 in this case.
Assistance Received: none
********************************************************************* */
int Round::pre_turn_menu()
{
	int next_player = get_next_player()-1;
	std::string next_player_type = players.at(next_player)->get_player_type();
	int error_number = -999;
	if (next_player_type == "Human") {

		std::cout << "1. Save the game" << std::endl;
		std::cout << "2. Take the turn" << std::endl;
		std::cout << "3. Quit the game" << std::endl;
		std::cout << "4. Advice (ask for help)" << std::endl;
		return validate_option_based_input(1, 4);
	}

	else if (next_player_type == "Computer") {
		std::cout << "1. Save the game" << std::endl;
		std::cout << "2. Take the turn" << std::endl;
		std::cout << "3. Quit the game" << std::endl;
		return validate_option_based_input(1, 4);
	}
	else {
		std::cout << "Unknown Player type! Can't display pre turn menu!" << std::endl;
		return error_number;
	}
	
}

/* *********************************************************************
Function Name: tally_score
Purpose: Tallies the score for both players in the round and prints it out.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */
void Round::tally_score()
{	
	int player_1_pos = 0;
	int player_2_pos = 1;
	bool player_1_gone_out = players.at(player_1_pos)->get_go_out_decision();
	bool player_2_gone_out = players.at(player_2_pos)->get_go_out_decision();
	int player_1_score = players.at(player_1_pos)->get_player_hand().get_total_score(player_1_gone_out);
	int player_2_score = players.at(player_2_pos)->get_player_hand().get_total_score(player_2_gone_out);

	if (player_1_gone_out) {
		player_1_score += 100;
	}
	else if (player_2_gone_out) {
		player_2_score += 100;
	}
	
	std::cout << "Player 1 (" << players.at(player_1_pos)->get_player_type()<<") "<< " round score: " << player_1_score << std::endl;
	std::cout << "Player 2 (" << players.at(player_2_pos)->get_player_type() << ") " << " round score: " << player_2_score << std::endl;

	players.at(player_1_pos)->add_to_score(player_1_score);
	players.at(player_2_pos)->add_to_score(player_2_score);
}

/* *********************************************************************
Function Name: set_round_number
Purpose: Sets the round number.
Parameters: round_number: an int representing what the next round number will be.
Return Value: none
Assistance Received: none
********************************************************************* */
void Round::set_round_number(int round_number)
{
	if (round_number>0)
		this->round_number = round_number;
}
/* *********************************************************************
Function Name: get_players
Purpose: To retrieve the players in a round.
Parameters: none
Return Value: a vector of player pointers representing each player, particularly a pointer to avoid object slicing.
Assistance Received: none
********************************************************************* */
std::vector<Player*> Round::get_players()
{
	return players;
}

/* *********************************************************************
Function Name: load_game
Purpose: To load a serialized file into a Round.
Parameters: none
Return Value: bool, representing if the file that has been loaded has been loaded successfully or not.
Algorithm: 
			1. Prompt for a file name input and then use a getline for a file name. 
				If the user inputs 0, automatically cancel the action and return false, as no file was loaded.
				The same will happen if the program cannot find the file, except for an extra error message. 
			2. Using filestreams, extract each line of the file into a vector of strings, and ignore empty lines in the file.
				In each line, using a lambda, the function will remove both extra white spaces on the interior of each
				string, as well as any extra white space on the left of the string. Right strings do not need to be of concern, 
				as it'll simply not parse the statement further.
			3. Check if the file has exactly 12 lines, the exact amount needed to further parse the strings.
			4. Using a switch statement, call each function by the position of the line. For instance, if the line is position 1(0),
				load the round number. 
			5. Close the file, outputting the round information of the file just loaded. Then, return true or false if all the loadings
				were successful.
Local variables:
					 input_file_name: A string representing what the user has inputted the file name as. 
					 file_to_load: an ifstream which assists in parsing each line of the serialized file. 
					 extracted_string: a string extracted from a line loaded by file_to_load.
					 load_success: a bool representing if the loading process has been completed successfully.
					 lines_to_parse: a vector of strings representing all the extracted strings from the file.
Assistance Received: none
********************************************************************* */
bool Round::load_game()
{
	std::cout << "Please enter the file you wish to load. Say 0 to quit." << std::endl;
	std::string input_file_name;
	getline(std::cin, input_file_name);

	if (input_file_name == "0") {
		return false;
	}

	std::ifstream file_to_load(input_file_name);
	std::string extracted_string;
	std::vector<std::string> lines_to_parse;
	bool load_success = true;

	if (std::filesystem::exists(input_file_name)) {
		while (getline(file_to_load, extracted_string)) {
			std::istringstream ss(extracted_string);

			if (extracted_string.find(':') != std::string::npos) {
				
				//removes extra spaces inside the string.
				//https://stackoverflow.com/questions/35301432/remove-extra-white-spaces-in-c
				//https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
				extracted_string.erase(std::unique(extracted_string.begin(), extracted_string.end(),
					[](char a, char b) { return isspace(a) && isspace(b); }),extracted_string.end());

				//https://stackoverflow.com/questions/216823/how-to-trim-an-stdstring
				extracted_string.erase(extracted_string.begin(), std::find_if(extracted_string.begin(), extracted_string.end(), [](unsigned char ch) {
					return !std::isspace(ch);
					}));
				lines_to_parse.push_back(extracted_string);
			}
		}
	}
	else {
		std::cout << "File specified does not exists!" << std::endl;
		return false;
	}

	if (lines_to_parse.size()!=12) {
		std::cout << "The load file has either too little or too much information!" << std::endl;
		return false;
	}

	else {
		for (int line_pos = 0; line_pos < lines_to_parse.size(); line_pos++) {
			std::string line_to_parse = lines_to_parse.at(line_pos);
			switch (line_pos) {
			case 0: 
				load_success = load_round_number(line_to_parse);
				break;
			case 1: 
				load_success = load_player(line_to_parse);
				break;
			case 2:
				load_success = load_player_score(0, line_to_parse);
				break;
			case 3: 
				load_success = load_hand(0,line_to_parse);
				break;
			case 4: 
				load_success = load_meld(0, line_to_parse);
				break;
			case 5:
				load_success = load_player(line_to_parse);
				break;
			case 6:
				load_success = load_player_score(1, line_to_parse);
				break;
			case 7: 
				load_success = load_hand(1,line_to_parse);
				break;
			case 8: 
				load_success = load_meld(1, line_to_parse);
				break;
			case 9: 
				load_success = load_stock(line_to_parse);
				break;
			case 10: 
				load_success = load_discard(line_to_parse);
				break;
			case 11: 
				load_success = load_next_player(line_to_parse);
				break;
			}
		}
	}

	file_to_load.close();
	output_round_info();


	return load_success;

	//https://stackoverflow.com/questions/3946558/c-read-from-text-file-and-separate-into-variable




}
/* *********************************************************************
Function Name: load_round_number
Purpose: To load a round number from a saved file the user inputted.
Parameters: round_string, representing a string to parse containing the round number.
Return Value: bool, representing if loading the round number was successful or not. 
Assistance Received: Since there still might be some information prior to the string being extracted, I used
						   this resource to assist in that: https://stackoverflow.com/questions/28163723/c-how-to-get-substring-after-a-character
********************************************************************* */
bool Round::load_round_number(std::string round_string)
{
	
	std::string round_num = round_string.substr(round_string.find(" ") + 1);
	if (round_num.size() == 0) {
		std::cout << "File load error: The round number is missing!" << std::endl;
		return false;
	}

	if (std::all_of(round_num.begin(), round_num.end(), ::isdigit)) {
		int round_number_converted = std::stoi(round_num);
		set_round_number(round_number_converted);
		return true;
	}
	
	else {
		std::cout << "File load error: the round number isn't numeric!" << std::endl;
		return false;
	}



}
/* *********************************************************************
Function Name: load_player
Purpose: To load the type of player from a saved file the user inputted, by adding to the players vector.
Parameters: player_string, a string representing the string to parse for the type of player.
Return Value: bool, representing if loading the player type was successful or not.
Assistance Received: none
********************************************************************* */
bool Round::load_player(std::string player_string)
{
	if (player_string == "Human:") {
		players.push_back(new Human);
		return true;
	}
	else if (player_string == "Computer:") {
		players.push_back(new Computer);
		return true;
	}
	else {
		std::cout << "Unknown player type!" << std::endl;
		return false;
	}

}

/* *********************************************************************
Function Name: load_player_score
Purpose: To load a player's score from a saved file the user inputted.
Parameters: 
			  score_string, representing a string to parse containing the player's score.
			  player, representing the player's position in players to assign the score to.
Return Value: bool, representing if loading the player's score was successful or not.
Assistance Received: Since there still might be some information prior to the string being extracted, I used
							this resource to assist in that: https://stackoverflow.com/questions/28163723/c-how-to-get-substring-after-a-character
********************************************************************* */
bool Round::load_player_score(int player, std::string score_string)
{
	//https://stackoverflow.com/questions/28163723/c-how-to-get-substring-after-a-character
	std::string player_score = score_string.substr(score_string.find(" ") + 1);

	if (player_score.size() == 0) {
		std::cout << "File load error: The player score is missing!" << std::endl;
		return false;
	}

	if (std::all_of(player_score.begin(), player_score.end(), ::isdigit)) {
		int player_score_converted = std::stoi(player_score);
		players.at(player)->set_player_score(player_score_converted);
		return true;
	}

	else {
		std::cout << "File load error: the player score isn't numeric!" << std::endl;
		return false;
	}
}

/* *********************************************************************
Function Name: string_is_card
Purpose: To validate if a passed string is a valid Card that can be loaded.
Parameters: card_string, a string representing a potential Card that is to be validated as a card.
Return Value: bool, representing if card_string is a valid Card. 
Algorithm: 
			 1. Check if the size of the card_string is 2, as that is how it's displayed in output. If not, return false,
				 as it's not a card.
			 2. Otherwise, break down the card string into rank and suite. Compare against a list of valid ranks and suites,
				 if the strings match up, then the card is valid, so return true. Otherwise, return false.
Local variables: 
			 player_1_pos and player_2_pos, ints which both represent player 1 and player 2's position in the players vector.
			 rank and suite, chars which both represent the rank and suite respectively.
			 rank_list and suite_list, strings which both represent the list of all valid chars for ranks and suits respectively.
Assistance Received: none
********************************************************************* */
bool Round::string_is_card(std::string card_string){
	if (card_string.size() != 2) {
		std::cout << "The selected value is not a valid card!" << std::endl;
		return false;
	}
	
	else {
		int rank_pos = 0; int suit_pos = 1;
		char rank = card_string.at(rank_pos);
		char suite = card_string.at(suit_pos);
		std::string rank_list = "123456789XAJQK";
		std::string suite_list = "HDCS1234";

		if (rank_list.find(rank) != std::string::npos && suite_list.find(suite) != std::string::npos)
			return true;
		else {
			std::cout << "The characters of the string do not contain a valid rank and suite!" << std::endl;
			return false;
		}
	}
}
/* *********************************************************************
Function Name: load_hand
Purpose: To load a player's hand from a saved file that has been inputted.
Parameters:
			  player, representing the player's position in players to assign the score to.
			  hand_string, representing a string to parse the player's hand
Algorithm: 
			  1. Create a substring to get rid of the last whitespace.
			  2. Using an istringstream, extract the contents of the string by using the extraction operator,
				  which will skip every time there's a whitespace. 
			  3. Check if each string extracted is a valid card. If so, add to a vector emulating the hand. 
				  if that is not the case, return false.
			  4. If all strings in the vector have been loaded, return true. 
Local variables: 
			  hand: a string representing the variable hand_string minus an extra whitespace.
			  converted_hand: the vector of Cards that will be the player's hand from the loaded file. 
			  hand_extractor: the isstringstream that will parse through the hand_string variable.
			  card_string: a string extracted from the hand_extractor which represents a particular Card.
Return Value: bool, representing if loading the player's hand was successful or not.
Assistance Received: Since there still might be some information prior to the string being extracted, I used
							this resource to assist in that: https://stackoverflow.com/questions/28163723/c-how-to-get-substring-after-a-character
********************************************************************* */
bool Round::load_hand(int player, std::string hand_string)
{
	std::string hand = hand_string.substr(hand_string.find(" ") + 1);
	std::vector<Card> converted_hand;
	std::istringstream hand_extractor(hand);
	do {
		std::string card_string;
		hand_extractor >> card_string;

		if (card_string=="")
			break;

		if (string_is_card(card_string)) {
			converted_hand.push_back(Card(card_string));
		}

		else {
			return false;
		}

	} while (hand_extractor);
	players.at(player)->set_hand(converted_hand);
	return true;
}
/* *********************************************************************
Function Name: load_meld
Purpose: To load a player's melds from a saved file that has been inputted.
Parameters:
			  player, representing the player's position in players to assign the score to.
			  pre_meld_strings, representing a string to parse the player's hand
Algorithm:
			  1. Create a substring to get rid of the last whitespace in pre_meld_string.
			  2. Using an instringstream with getline which delimits on the character ']', extract each individual meld.
				  additionally, remove each '[' and ']' character within the extracted string. 
			  3. Using an istringstream, extract the contents of the extracted meld string by using the extraction operator,
				  which will skip every time there's a whitespace.
			  3. Check if each string extracted is a valid card. If so, add to a vector of Cards emulating a single meld, which will, after
				  iteration, add to a vector of vector of Cards emulating all the melds the player has.
				  if that is not the case, return false.
			  4. If all strings in the vector of vectors have been loaded successfully, return true.
Local variables:
			  melds: a string representing the variable pre_meld_string minus an extra whitespace.
			  converted_meld: the vector of Cards that will be a single meld in the player's hand from the loaded file.
			  converted_meld_container: the vector of vector of Cards that stores converted_melds, representing the melded 
			  meld_extractor: the isstringstream that will parse through pre_meld_string
			  meld_string: a string extracted from the meld_extractor which represents a particular meld.
			  card_string: a string extracted from the meld_extractor which represents a particular Card.

Return Value: bool, representing if loading the player's melds was successful or not.
Assistance Received: Since there still might be some information prior to the string being extracted, I used
							this resource to assist in that: https://stackoverflow.com/questions/28163723/c-how-to-get-substring-after-a-character
********************************************************************* */
bool Round::load_meld(int player, std::string pre_meld_string)
{
	std::string melds = pre_meld_string.substr(pre_meld_string.find(" ") + 1);
	std::vector<Card> converted_meld;
	std::vector<std::vector<Card>> converted_meld_container;
	std::istringstream meld_extractor(melds);
	std::string meld_string;
	std::string card_string;
	while (getline(meld_extractor, meld_string, ']')) {

		if (meld_string == "" || meld_string == " ")
			break;

		//https://www.tutorialspoint.com/how-to-remove-certain-characters-from-a-string-in-cplusplus
		meld_string.erase(std::remove(meld_string.begin(), meld_string.end(), '['), meld_string.end());
		meld_string.erase(std::remove(meld_string.begin(), meld_string.end(), ']'), meld_string.end());

		std::istringstream card_extractor(meld_string);

		while (card_extractor >> card_string) {
			if (card_string == "")
				break;

			if (string_is_card(card_string)) {
				converted_meld.push_back(Card(card_string));
			}

			else {
				return false;
			}
		}

		converted_meld_container.push_back(converted_meld);
		converted_meld.clear();
		card_extractor.clear();

		meld_extractor.clear();
	}
	players.at(player)->set_meld(converted_meld_container);
	return true;
}

/* *********************************************************************
Function Name: load_stock
Purpose: To load a Round's stock pile from a saved file that has been inputted.
Parameters:
			  stock_string, representing a string to parse the Round's stock pile.
Algorithm:
			  1. Create a substring to get rid of the last whitespace.
			  2. Using an istringstream, extract the contents of the string by using the extraction operator,
				  which will skip every time there's a whitespace.
			  3. Check if each string extracted is a valid card. If so, add to a vector of Cards emulating the stock.
				  if that is not the case, return false.
			  4. If all strings in the vector have been loaded, return true.
Local variables:
			  stock: a string representing the variable stock_string minus an extra whitespace.
			  converted_stock: the vector of Cards that will be the player's hand from the loaded file.
			  stock_extractor: the isstringstream that will parse through the hand_string variable.
			  card_string: a string extracted from the hand_extractor which represents a particular Card.
Return Value: bool, representing if loading the Round's stock pile was successful or not.
Assistance Received: Since there still might be some information prior to the string being extracted, I used
							this resource to assist in that: https://stackoverflow.com/questions/28163723/c-how-to-get-substring-after-a-character
********************************************************************* */
bool Round::load_stock(std::string stock_string)
{
	std::string stock = stock_string.substr(stock_string.find(" ") + 1);
	std::vector<Card> converted_stock;

	std::istringstream stock_extractor(stock);
	do {
		std::string card_string;
		stock_extractor >> card_string;

		if (card_string == "")
			break;

		if (string_is_card(card_string)) {
			converted_stock.push_back(Card(card_string));
		}

		else {
			return false;
		}

	} while (stock_extractor);	
	set_stock_pile(converted_stock);

	return true;
}
/* *********************************************************************
Function Name: load_discard
Purpose: To load a Round's discard pile from a saved file that has been inputted.
Parameters:
			  discard_string, representing a string to parse the Round's discard pile.
Algorithm:
			  1. Create a substring to get rid of the last whitespace.
			  2. Using an istringstream, extract the contents of the string by using the extraction operator,
				  which will skip every time there's a whitespace.
			  3. Check if each string extracted is a valid card. If so, add to a vector of Cards emulating the discard pile.
				  if that is not the case, return false.
			  4. If all strings in the vector have been loaded, return true.
Local variables:
			  discard: a string representing the variable stock_string minus an extra whitespace.
			  converted_discard: the vector of Cards that will be the player's hand from the loaded file.
			  discard_extractor: the isstringstream that will parse through the hand_string variable.
			  card_string: a string extracted from the hand_extractor which represents a particular Card.
Return Value: bool, representing if loading the Round's discard pile was successful or not.
Assistance Received: Since there still might be some information prior to the string being extracted, I used
							this resource to assist in that: https://stackoverflow.com/questions/28163723/c-how-to-get-substring-after-a-character
********************************************************************* */
bool Round::load_discard(std::string discard_string)
{
	std::string discard = discard_string.substr(discard_string.find(" ") + 1);
	 discard = discard_string.substr(discard_string.find(":") + 1);
	std::vector<Card> converted_discard;

	std::istringstream discard_extractor(discard);
	do {
		std::string card_string;
		discard_extractor >> card_string;

		if (card_string == "")
			break;


		if (string_is_card(card_string)) {
			converted_discard.push_back(Card(card_string));
		}

		else {
			return false;
		}


	} while (discard_extractor);

	set_discard_pile(converted_discard);

	return true;
}
/* *********************************************************************
Function Name: load_next_player
Purpose: To load a Round's next player from a saved file the user inputted.
Parameters:
			  next_player_str, representing a string to parse containing the next player.
Algorithm: 
			 1. Get rid of the trailing whitespace in front of next_player_str and reassign it to itself.
			 2. If the next player is Human or Computer, set it to be as such by adding the player position plus 1. Then return true.
			 3. If the next player is neither, return false.
Local variables: none
Return Value: bool, representing if loading the next player was successful or not.
Assistance Received: Since there still might be some information prior to the string being extracted, I used
							this resource to assist in that: https://stackoverflow.com/questions/28163723/c-how-to-get-substring-after-a-character
********************************************************************* */
bool Round::load_next_player(std::string next_player_str) {
	
	next_player_str = next_player_str.substr(next_player_str.find(" ") + 1);
	
	if (next_player_str == "Player: Human") {
		for (int player_pos = 0; player_pos < players.size(); player_pos++) {
			if (players.at(player_pos)->get_player_type() == "Human") {
				set_next_player(player_pos+1);
				break;
			}
		}
		return true;
	}
	else if (next_player_str == "Player: Computer") {
		for (int player_pos = 0; player_pos < players.size(); player_pos++) {
			if (players.at(player_pos)->get_player_type() == "Computer") {
				set_next_player(player_pos+1);
				break;
			}
		}
		return true;
	}
	else {
		std::cout << "File loading error: next player is not Human or Computer!" << std::endl;
		return false;
	}
}
/* *********************************************************************
Function Name: set_stock_pile 
Purpose: A setter for the Round's stock pile.
Parameters:
			  score_pile, representing a vector of Cards for the data member to be set as. 
Return Value: none
Assistance Received: none
********************************************************************* */
void Round::set_stock_pile(std::vector<Card> stock_pile)
{
	stock_and_discard.set_stock_pile(stock_pile);
}
/* *********************************************************************
Function Name: set_discard_pile
Purpose: A setter for the Round's discard pile.
Parameters:
			  discard_pile, representing a vector of Cards for the data member to be set as.
Return Value: none
Assistance Received: none
********************************************************************* */
void Round::set_discard_pile(std::vector<Card> discard_pile)
{
	stock_and_discard.set_discard_pile(discard_pile);
}
/* *********************************************************************
Function Name: save_round
Purpose: Serializes the information of the current round and saves it to a file.
Parameters:
			  discard_pile, representing a vector of Cards for the data member to be set as.
Return Value: none
Assistance Received: I primarily looked into how to reroute output buffers to files.
https://stackoverflow.com/questions/4810516/c-redirecting-stdout
********************************************************************* */
void Round::save_round()
{
	std::string file_name; 
	std::cout << "What would you like to save your file as? Say quit to cancel saving." << std::endl;

	if (file_name == "quit")
		return;

	getline(std::cin, file_name);
	
	std::ofstream out(file_name);
	std::streambuf* coutbuf = std::cout.rdbuf(); //save the old buffer
	std::cout.rdbuf(out.rdbuf()); //reroute output to a file with a  buffer
	
	output_round_info();

	std::cout.rdbuf(coutbuf);  //reset the buffer to standard output
}




