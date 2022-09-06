// Debugging
//

#include <iostream>
#include <vector>
#include "Card.h"
int main()
{
   std::vector<Card> x;
   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 13; j++)
         Card card(Card::Suit(i), j);
    }
}
