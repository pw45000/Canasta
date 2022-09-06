#pragma once
class Card {
public: 
	Card();
	
	
	enum Suit : unsigned char {Hearts = 'H', Clubs = 'C', Spades = 'S', Diamond = 'D',};
	enum Rank : unsigned char {
		Begin, One = '1', Two = '2', Three = '3', Four = '4', Five = '5', 
		Six = '6', Seven = '7', Eight = '8', Nine = '9', Ten = 'X',
		Ace = 'A', Jack = 'J', Queen = 'Q', King = 'K', End
	};
	Card(Card::Suit suit, Card::Rank rank );

private: 
	unsigned char rank;
	unsigned char suit;
};