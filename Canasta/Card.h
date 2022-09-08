/* ***********************************************************
* Name:  Patrick Wierzbicki*
* Project : Cansta P1*
* Class : class numberand name here*
* Date : 9/13/22*
*********************************************************** */

#pragma once
#include <string>
#include <vector>

class Card {
public: 
	Card();
	Card(int suit, int face);
	Card(char face, char suit, std::string string_reprensentation, int point_value);
	
	void translate_to_symbolic_rep(int face, int value);
	void calculate_point_value(char face, char value);
	
	char get_card_face() const;
	char get_card_suit() const;
	std::string get_card_string() const;
	int get_point_value() const;


private: 
	char face;
	char suit;
	std::string string_representation;
	int point_value;

};