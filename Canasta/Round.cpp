#include "Round.h"
int Round::coin_toss()
{
	auto seed1 = std::chrono::system_clock::now().time_since_epoch().count();

	std::random_device dev;
	std::uniform_int_distribution<std::mt19937::result_type> coin(1, 2);

	std::string choice;
	auto flipped_coin = coin(dev);
	std::cout << "Player 2! Heads or Tails?" << std::endl;
	std::cout << "1. Heads" << std::endl;
	std::cout << "2. Tails" << std::endl;
	do {
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore(500, '\n');
		if (choice != "1" && choice != "2")
			std::cout << "That's not a right option, pick 1 or 2..." << std::endl;
		
	}
	while (choice!="1" && choice!="2");


	if (std::stoi(choice) == flipped_coin) {
		std::cout << "Player 1 goes first! They guessed correctly, the value is " << flipped_coin << std::endl;
		return 2;
	}

	else {
		std::cout << "Player 2 goes first! Player 1 guessed incorrectly the value is "<< flipped_coin << std::endl;
		return 1; 
	}

	

	//https://stackoverflow.com/questions/59644856/measuring-time-to-generate-better-random-numbers-in-c

}

void Round::main_round(bool has_loaded_file)
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
			case 1:
				sort_players_hands();
				save_round();
				break;
			case 2:
				continue;
				break;
			case 3:
				continue;
				break;
			case 4:
				round_is_over = true;
				break;
			}

		} while (menu_choice != 4 && menu_choice != 2);
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
	

}


void Round::initial_draw()
{
	//for each player, draw 15 cards from the stockpile.
	int initial_draw_count = 15;
	for (int itr = 0; itr < players.size(); itr++) {
		for (int card = 0; card < initial_draw_count; card++) {
			Card drawn_card = stock_and_discard.draw_from_stock();
			std::string drawn_string = drawn_card.get_card_string();

			if (drawn_string == "3H" || drawn_string == "3D") {
				std::cout << "Lucky you! Player " << itr + 1 << ", you got a red three!" << std::endl;
				players.at(itr)->create_special_meld(drawn_card);
				card--;
			}
			else {
				players.at(itr)->add_to_hand(drawn_card);
			}
		}
	}
}

int Round::get_next_player() const
{
	return next_player;
}

void Round::set_next_player(int next_player)
{
	this->next_player = next_player;
}

void Round::output_round_info()
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

void Round::sort_players_hands()
{
	for (int itr = 0; itr < players.size(); itr++)
		players.at(itr)->sort_hand();
}

int Round::pre_turn_menu()
{
	std::cout << "1. Save the game" << std::endl;
	std::cout << "2. Take the turn" << std::endl;
	std::cout << "3. Advice (ask for help)" << std::endl;
	std::cout << "4. Quit the game" << std::endl;
	return validate_option_based_input(1, 4);
}

void Round::tally_score()
{
	int player_1_score = players.at(0)->get_player_hand().get_total_score();
	int player_2_score = players.at(1)->get_player_hand().get_total_score();

	players.at(0)->add_to_score(player_1_score);
	players.at(1)->add_to_score(player_2_score);


}

void Round::set_round_number(int round_number)
{
	this->round_number = round_number;
}

std::vector<Player*> Round::get_players()
{
	return players;
}

bool Round::load_game()
{
	std::cout << "Please enter the file you wish to load. " << std::endl;
	std::string input_file_name;
	getline(std::cin, input_file_name);
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

bool Round::load_round_number(std::string round_string)
{
	//https://stackoverflow.com/questions/28163723/c-how-to-get-substring-after-a-character
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

bool Round::load_player_score(int player, std::string round_string)
{
	//https://stackoverflow.com/questions/28163723/c-how-to-get-substring-after-a-character
	std::string player_score = round_string.substr(round_string.find(" ") + 1);



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

bool Round::string_is_card(std::string card_string)
{
	if (card_string.size() != 2) {
		std::cout << "The selected value is not a valid card!" << std::endl;
		return false;
	}
	else {
		char rank = card_string.at(0);
		char suite = card_string.at(1);

		std::string rank_list = "123456789XAJQK";
		std::string suite_list = "HDCS12345678";

		if (rank_list.find(rank) != std::string::npos && suite_list.find(suite) != std::string::npos)
			return true;
		else {
			std::cout << "The characters of the string do not contain a valid rank and suite!" << std::endl;
			return false;
		}


	}



}

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

	//std::reverse(converted_stock.begin(), converted_stock.end());
	
	set_stock_pile(converted_stock);

	return true;
}

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

	//std::reverse(converted_discard.begin(), converted_discard.end());
	set_discard_pile(converted_discard);

	return true;
}

bool Round::load_next_player(std::string next_player_str) {
	
	next_player_str = next_player_str.substr(next_player_str.find(" ") + 1);
	
	if (next_player_str == "Player: Human") {
		set_next_player(2);
		return true;
	}
	else if (next_player_str == "Player: Computer") {
		set_next_player(1);
		return true;
	}
	else {
		std::cout << "File loading error: next player is not Human or Computer!" << std::endl;
		return false;
	}
}

void Round::set_stock_pile(std::vector<Card> stock_pile)
{
	stock_and_discard.set_stock_pile(stock_pile);
}

void Round::set_discard_pile(std::vector<Card> discard_pile)
{
	stock_and_discard.set_discard_pile(discard_pile);
}

void Round::save_round()
{
	std::string file_name; 
	std::cout << "What would you like to save your file as? Say quit to cancel saving." << std::endl;

	if (file_name == "quit")
		return;

	getline(std::cin, file_name);
	
	std::ofstream out(file_name);
	std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
	
	output_round_info();

	std::cout.rdbuf(coutbuf);  //reset to standard output again


	
	
}




Round::Round()
{
	player_1_score = 0;
	player_2_score = 0;
	next_player = 0;
	round_number = 0;
}

Round::Round(Human player1, Human player2)
{
	players.push_back(&player1);
	players.push_back(&player2);
	player_1_score = 0;
	player_2_score = 0;
	next_player = 0;
	round_number = 0;
}

Round::Round(Human player1, Computer player2)
{
	players.push_back(&player1);
	players.push_back(&player2);
	player_1_score = 0;
	player_2_score = 0;
	next_player = 0;
	round_number = 0;
}

Round::Round(std::vector<Player*> players, int round_number)
{
	this->players = players;
	this->round_number = round_number;
	player_1_score = 0;
	player_2_score = 0;
	next_player = 0;
}



Round::Round(const Round& other_round)
{
	this->next_player = other_round.next_player;
	this->stock_and_discard = other_round.stock_and_discard;
	this->player_1_score = other_round.player_1_score;
	this->player_2_score = other_round.player_2_score;
	this->players = other_round.players;

}

//https://stackoverflow.com/questions/20814703/should-i-delete-static-object-in-c
//empty for now due to the class Game taking care of the anonymous variable. 
Round::~Round()
{
	stock_and_discard.clear_discard();
}
