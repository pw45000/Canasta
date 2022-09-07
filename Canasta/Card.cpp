#include "Card.h"

Card::Card() : face(0), suit(0), point_value(0) {
	this->string_representation = "NULL";
};

Card::Card(int suit, int face) {
	translate_to_symbolic_rep(face , suit);
	calculate_point_value(this->face, this->suit);
}

Card::Card(char face, char suit, std::string string_reprensentation, int point_value) : 
	face(face), suit(suit), point_value(point_value)
{
	this->string_representation = string_reprensentation;
};

void Card::calculate_point_value(char face, char suit) {
	switch (face) {
	case 'A':
	case '2':
		this->point_value = 20;
		break;
	case '3':
		if (suit == 'D' || suit == 'H')
			this->point_value = 100;
		else
			this->point_value = 5;
		break;
	case '4': 
	case '5':
	case '6':
	case '7':
		this->point_value = 5;
		break;
	case '8': 
	case '9': 
	case '10': 
	case 'J':
	case 'Q':
	case 'K': 
		this->point_value = 10;
		break;
	}
}

void Card::translate_to_symbolic_rep(int face, int suit) {
	
	switch (suit) {
	case 0: 
		this->suit = 'h';
		break;
	case 1: 
		this->suit = 'd';
		break;
	case 2: 
		this->suit = 'c';
		break;
	case 3: 
		this->suit = 's';
		break;
	}

	if (face < 10) {
		//We're adding an offset due to ASCII encoding.
		this->face = static_cast<char> (face+48);
	}
	else {
		switch (face) {
		case 10: 
			this->face = 'x';
			break;
		case 11:
			this->face = 'a';
			break;
		case 12: 
			this->face = 'j';
			break;
		case 13: 
			this->face = 'q';
			break;
		case 14: 
			this->face = 'k';
			break;
		}
	}
	this->string_representation.push_back(this->face);
	this->string_representation.push_back(this->suit);
	//https://stackoverflow.com/questions/51017979/joining-two-characters-in-c
}



