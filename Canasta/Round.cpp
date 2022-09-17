#include "Round.h"
int Round::coin_toss()
{
	auto seed1 = std::chrono::system_clock::now().time_since_epoch().count();

	std::random_device dev;
	std::uniform_int_distribution<std::mt19937::result_type> coin(1, 2);

	std::string choice;
	auto flipped_coin = coin(dev);
	std::cout << "Player 1! Heads or Tails?" << std::endl;
	std::cout << "1. Heads" << std::endl;
	std::cout << "2. Tails" << std::endl;
	do {
		std::cin >> choice;
		if (choice != "1" && choice != "2")
			std::cout << "That's not a right option, pick 1 or 2..." << std::endl;
		
	}
	while (choice!="1" && choice!="2");


	if (std::stoi(choice) == flipped_coin) {
		std::cout << "Player 1 goes first! They guessed correctly, the value is " << flipped_coin << std::endl;
		return 1;
	}

	else {
		std::cout << "Player 2 goes first! Player 1 guessed incorrectly the value is "<< flipped_coin << std::endl;
		return 2; 
	}

	

	//https://stackoverflow.com/questions/59644856/measuring-time-to-generate-better-random-numbers-in-c

}

void Round::main_round()
{
	auto player1 = players.at(0);
	auto player2 = players.at(1);


	if (player1->get_score() == player2->get_score()) {
		//the coin toss decides which player is going next.
		//so, we'll need to set the result for it's return.
		set_next_player(coin_toss());
	}

	initial_draw();
	output_round_info();
	
	if (next_player == 1) {
		player1->play(stock_and_discard);
		//we'll need to increment next player to pass the turn.
		next_player++;
	}

	else {
		player2->play(stock_and_discard);
		//since 2 is bigger than 1, we'll need to decrement 
		//to get the next player to be 1.
		next_player--;
	}

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
	std::cout << "   Score: " << player_1->get_score() << std::endl;
	
	std::cout << "   Hand: ";
	player_1_hand.print_hand();
	std::cout << "   Melds: ";
	player_1_hand.print_melds();
	std::cout << "\n" << std::endl;


	player_2->print_player_type();
	std::cout << "   Score: " << player_2->get_score() << std::endl;

	std::cout << "   Hand: ";
	player_2_hand.print_hand();
	std::cout << "   Melds: ";
	player_2_hand.print_melds();
	std::cout << "\n" << std::endl;

	std::cout << "Stock: ";
	stock_and_discard.print_stock_pile();
	std::cout << "Discard Pile:";
	stock_and_discard.print_top_of_discard_pile();


	std::cout << "Next Player: ";
	(next_player == 1) ? player_1->print_player_type() : player_2->print_player_type();
	std::cout << std::endl;

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
//empty for now due to this.
Round::~Round()
{
	players.clear();
}
