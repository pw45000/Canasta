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
