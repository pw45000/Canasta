/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Cansta P1*
* Class : class numberand name here*
* Date : 9/13/22*
*********************************************************** */
#include "Card.h"





/* *********************************************************************
Function Name: Card
Purpose: The default constructor of the Card class. Uses constructor member initilization.
Parameters: none
Return Value: none
Assistance Received: none
********************************************************************* */

Card::Card() : face(0), suit(0), point_value(0) {
	//strings cannot be constructor initialized, 
	//so they need to be set manually.
	this->string_representation = "NULL";
};


/* *********************************************************************
Function Name: Card
Purpose: The default constructor of the Card class.
Parameters: 
				suit: a passed by value integer that represents the suit of the card (0-3).
				face: a passed by value integer that represents the face of the card (2-14), 
				where 11-13 are the royal faces: ace, jack, queen, king. 
Return Value: none
Algorithim: 
				1) The constructor will call translate_to_symbolic_rep, which will turn
				the face and suit integers into their char counterparts, as well as creating a string representation.
				2) The constructor will then call calculate_point_value, which will calculate the point
				value of the card. 
Assistance Received: none
********************************************************************* */

Card::Card(int suit, int face) {
	translate_to_symbolic_rep(face , suit);
	calculate_point_value(this->face, this->suit);
}

/* *********************************************************************
Function Name: Card
Purpose: The "full" constructor of the Card Class. The parameters passed are the full information about the card.
Parameters: 
				suit: an integer that represents the suit of the card (0-3).
				face: an integer that represents the face of the card (2-14),
				where 11-13 are the royal faces: ace, jack, queen, king.
				string_representation: The string representation of the Card passed by value. For instance, a three of hearts
				is 3H.
				point_value: An integer representing the Card's value in points. For instance, if the card is 3H, it will be 
				worth 100 points. 
Return Value: none
Assistance Received: none
********************************************************************* */
Card::Card(char face, char suit, std::string string_reprensentation, int point_value) : 
	face(face), suit(suit), point_value(point_value)
{
	//strings cannot be constructor initialized, 
	//so they need to be set manually.
	this->string_representation = string_reprensentation;
}
Card::Card(const Card& other_card)
{
	point_value = other_card.get_point_value();
	face = other_card.get_card_face();
	suit = other_card.get_card_suit();
	string_representation = other_card.get_card_string();
}

Card Card::operator=(const Card& other_card)
{
	point_value = other_card.get_point_value();
	face = other_card.get_card_face();
	suit = other_card.get_card_suit();
	string_representation = other_card.get_card_string();
	return *this;
}

Card::~Card()
{
	face = '0';
	suit = '0';
	string_representation = "";
	point_value = 0;
}




/* *********************************************************************
Function Name: calculate_point_value
Purpose: Calculate the point value of each Card. 
Parameters:
				face: a char representing the card's face. An example would be a 1 would be a 1 and K is a King.
				suit: a char representing the card's suite. An example would be a Diamond is D.
Return Value: void
Algorithm:
				1) Make a switch case depending on the face. If it's a 3, seperate the case using and if/else statement.
				2) Assign point value within individual cases. 
Assistance Received: none
********************************************************************* */
void Card::calculate_point_value(char face, char suit) {
	//This switch case uses multiple cases. 
	//Unfortunately, Visual C++ doesn't support case ranges.
	//So I had to put all the cases.
	switch (face) {
	case 'A':
	case '2':
		this->point_value = 20;
		break;
	case '3':
		//Check if the 3 is of a red suite.
		//Otherwise, assign it a black 3's value.
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


/* *********************************************************************
Function Name: translate_to_symbolic_rep
Purpose: Translate the integers representing the face and suit into their char representations and create a
string representation using those two chars. 
Parameters:
				suit: an integer that represents the suit of the card (0-3).
				face: an integer that represents the face of the card (2-14),
				where 11-13 are the royal faces: ace, jack, queen, king
Return Value: void
Local Variables: 
	ascii_offset: An offset used to convert an integer to its respective char. 
Algorithm:
				1) Switch values depending on the suit, assigning a char value based on the number. 
				2) If a face number is under 10, type cast the number plus the ASCII offset
				using static cast. 
				3) If the face number is greater or equal to 10, switch the face depending on the value
				and assign the value accordingly. For instance, 10 will be translated to X. 
				4) Append the two characters into string_representation, so that it can be printed out
				later. 
Assistance Received: In terms of solving the problem of two characters being concatenated to a string, 
I decided to append it based upon this answer: 
https://stackoverflow.com/questions/51017979/joining-two-characters-in-c
********************************************************************* */
void Card::translate_to_symbolic_rep(int face, int suit) {
	
	//Since the program is converting from ints to chars and with
	//the way char arithmetic works, an offset of 48 will be needed to 
	//properly convert an integer to a char. For instance, 1+48=49, which 
	//index corresponds to 1 in ASCII. 
	int ascii_offset = 48;
	
	//This switch case uses multiple cases. 
	//Unfortunately, Visual C++ doesn't support case ranges,
	//So I had to put all the cases.
	switch (suit) {
	case 0: 
		this->suit = 'H';
		break;
	case 1: 
		this->suit = 'D';
		break;
	case 2: 
		this->suit = 'C';
		break;
	case 3: 
		this->suit = 'S';
		break;
	}

	if (face < 10) {
		//I personally used a static cast so as not to lose any data
		//associated with the char, compared to (char) 
		//which might potentially lose data.
		this->face = static_cast<char> (face+ascii_offset);
	}
	else {
		switch (face) {
		case 10: 
			this->face = 'X';
			break;
		case 11:
			this->face = 'A';
			break;
		case 12:
			//IMPORTANT NOTE: J is a Jack, not a Joker.
			this->face = 'J';
			break;
		case 13: 
			this->face = 'Q';
			break;
		case 14: 
			this->face = 'K';
			break;
		}
	}
	//Without string conversion, or the appriopriate char
	//arithmetic, it'll be different convert the two chars into a string,
	//so it's easiest just to use std::string's built in push_back function.
	//Making another string could've also been done, but that seems to just be a 
	//waste of space.
	this->string_representation.push_back(this->face);
	this->string_representation.push_back(this->suit);
}


/* *********************************************************************
Function Name: get_card_face()
Purpose: Selector for the face variable.
Parameters: none
Return Value: face, a char representing the card's face.
Assistance Received: none
********************************************************************* */
char Card::get_card_face() const
{
	return face;
}

/* *********************************************************************
Function Name: get_card_suit()
Purpose: Selector for the suit variable.
Parameters: none
Return Value: suit, a char representing the card's suit.
Assistance Received: none
********************************************************************* */
char Card::get_card_suit() const
{
	return suit;
}

/* *********************************************************************
Function Name: get_card_string()
Purpose: Selector for the string_representation variable.
Parameters: none
Return Value: string_representation, a string representing the card face and suit. 
An example would be a three of hearts being 3H. 
Assistance Received: none
********************************************************************* */
std::string Card::get_card_string() const
{
	return string_representation;
}

/* *********************************************************************
Function Name: get_point_value()
Purpose: Selector for the point_value variable.
Parameters: none
Return Value: point_value, a int representing the card. 
Assistance Received: none
********************************************************************* */
int Card::get_point_value() const
{
	return point_value;
}

/* *********************************************************************
Function Name: isWild()
Purpose: Returns if the current card is a wild card or not. 
Parameters: none
Return Value: bool for if the current card is a wild card or not.
Assistance Received: none
********************************************************************* */
bool Card::isWild() const {
	//Jokers are notated as J1, J2, so their
	//suit is numeric. 
	if (face == '2' || isdigit(suit))
		return true;
	else
		return false;
}

/* *********************************************************************
Function Name: isSpecial()
Purpose: Returns if the current card is a special card
Parameters: none
Return Value: bool for if the current card is a special card or not.
Assistance Received: none
********************************************************************* */
bool Card::isSpecial() const {
	if (face == '3')
		return true;
	else
		return false;
}

/* *********************************************************************
Function Name: isNatural()
Purpose: Returns if the current card is a natural card
Parameters: none
Return Value: bool for if the current card is a natural card or not.
Assistance Received: none
********************************************************************* */
bool Card::isNatural() const {
	return (!(isSpecial() && isWild()));
}

bool Card::is_red_three() const
{
	if (string_representation == "3H" || string_representation == "3D")
		return true;
	else
		return false;
}

bool operator==(const Card card1, const Card card2)
{
	if (card1.get_card_string() == card2.get_card_string())
		return true;
	else
		return false;
}
