#pragma once
#include <string>
#include <vector>

class Card {
public: 
	Card();
	Card(int suit, int face);
	Card(char face, char suit, std::string string_reprensentation, int point_value);
	void calculate_point_value(char face, char value);
	void translate_to_symbolic_rep(int face, int value);

private: 
	char face;
	char suit;
	std::string string_representation;
	int point_value;

};