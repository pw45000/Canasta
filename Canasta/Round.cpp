#include "Round.h"
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

	

	//https://stackoverflow.com/questions/59644856/measuring-time-to-generate-better-random-numbers-in-c

}

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
	for (int plr_pos = 0; plr_pos < players.size(); plr_pos++)
		players.at(plr_pos)->sort_hand();
}

int Round::pre_turn_menu()
{
	int next_player = get_next_player()-1;
	std::string next_player_type = players.at(next_player)->get_player_type();

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
		return -999;
	}
	
}

void Round::tally_score()
{	
	int player_1_score = players.at(0)->get_player_hand().get_total_score();
	int player_2_score = players.at(1)->get_player_hand().get_total_score();

	if (players.at(0)->get_go_out_decision() == true) {
		player_1_score += 100;
	}
	else if (players.at(1)->get_go_out_decision() == true) {
		player_2_score += 100;
	}
	


	std::cout << "Player 1 (" << players.at(0)->get_player_type()<<") "<< " round score: " << player_1_score << std::endl;
	std::cout << "Player 2 (" << players.at(1)->get_player_type() << ") " << " round score: " << player_2_score << std::endl;


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
		std::string suite_list = "HDCS1234";

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

	next_player = 0;
	round_number = 0;
}

Round::Round(Human player1, Human player2)
{
	players.push_back(&player1);
	players.push_back(&player2);
	next_player = 0;
	round_number = 0;
}

Round::Round(Human player1, Computer player2)
{
	players.push_back(&player1);
	players.push_back(&player2);
	next_player = 0;
	round_number = 0;
}

Round::Round(std::vector<Player*> players, int round_number)
{
	this->players = players;
	this->round_number = round_number;
	next_player = 0;
}



Round::Round(const Round& other_round)
{
	this->next_player = other_round.next_player;
	this->stock_and_discard = other_round.stock_and_discard;
	this->players = other_round.players;

}

//https://stackoverflow.com/questions/20814703/should-i-delete-static-object-in-c
//empty for now due to the class Game taking care of the anonymous variable. 
Round::~Round()
{
	stock_and_discard.clear_discard();
}
