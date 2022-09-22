/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Cansta P1*
* Class : class numberand name here*
* Date : 9/28/22*
*********************************************************** */

#pragma once
#include <string>
#include <vector>

class Card {
public: 
	Card();
	Card(int suit, int face);
	Card(char face, char suit, std::string string_reprensentation, int point_value);
	Card(std::string string_representation);
	void translate_to_symbolic_rep(int face, int value);
	void calculate_point_value(char face, char value);
	
	char get_card_face() const;
	char get_card_suit() const;
	std::string get_card_string() const;
	int get_point_value() const;

	bool isWild() const;
	bool isSpecial() const; 
	bool isNatural() const;
	bool is_red_three() const;
	bool get_has_transferred() const;


	int get_numeric_value() const;

	void set_has_transferred(bool has_transferred);

private:  
	char face;
	char suit;
	std::string string_representation;
	int point_value;
	bool has_transferred;
};

//one of the only functions not added within the class. This is because we need a binary comparison.
bool operator== (const Card card1, const Card card2);
bool operator< (const Card card1, const Card card2);