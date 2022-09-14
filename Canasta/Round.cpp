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


	if (std::stoi(choice) == coin(dev)) {
		std::cout << "Player 1 goes first! They guessed correctly, the value is " << flipped_coin << std::endl;
		return 1;
	}

	else {
		std::cout << "Player 2 goes first! Player 1 guessed incorrectly the value is "<< flipped_coin << std::endl;
		return 2; 
	}

	

	//https://stackoverflow.com/questions/59644856/measuring-time-to-generate-better-random-numbers-in-c

}

Round::Round()
{
	player_1_score = 0;
	player_2_score = 0;
}

Round::Round(Human player1, Human player2)
{
	players.push_back(&player1);
	players.push_back(&player2);
	player_1_score = 0;
	player_2_score = 0;
}

Round::Round(Human player1, Computer player2)
{
	players.push_back(&player1);
	players.push_back(&player2);
	player_1_score = 0;
	player_2_score = 0;
}

Round::Round(const Round& other_round)
{
	this->next_player = other_round.next_player;
	this->stock_and_discard = other_round.stock_and_discard;
	this->player_1_score = other_round.player_1_score;
	this->player_2_score = other_round.player_2_score;
	this->players = other_round.players;

}

Round::~Round()
{
	for (int itr = 0; itr < players.size(); itr++) {
		delete players.at(itr);
	}
}
