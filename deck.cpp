// DOCUMENT HERE

#include "deck.h"

using namespace std;

// constructors
Deck::Deck() {
  unsigned int currentTime = (unsigned) time(0);
  srand(currentTime); // for shuffling

  myIndex = 0;

  const int numRanks = 13;
  const int numSuits = 4;
  Card::Suit suits[numSuits] = {Card::spades, Card::hearts, Card::diamonds, Card:: clubs};
  for(int rank = 0; rank<numRanks; rank++) {
    for(int suit = 0; suit<numSuits; suit++){
      myCards[myIndex] = Card(rank+1, suits[suit]);
      myIndex++;
    }
  }
  myIndex--; // makes myIndex = 51 or top card
}

void Deck::shuffle() {
  for(int i = 0; i<myIndex; i++) {
    int firstIndex = rand() % SIZE;
    int secondIndex = rand() % SIZE;
    if(secondIndex == firstIndex)
      secondIndex = (secondIndex+1)%SIZE;
    Card temp = myCards[firstIndex];
    myCards[firstIndex] = myCards[secondIndex];
    myCards[secondIndex] = temp;
  }
}

Card Deck::dealCard() {
  const int DECK_FINISHED = -1;
  if(myIndex != DECK_FINISHED) {
    myIndex--;
    return(myCards[myIndex+1]);
  }
  else {
    // WHAT TO DO WHEN YOU CAN'T RETURN
    return Card(1, Card::spades);
  }
}

int Deck::size() const {
  return myIndex+1;
}
