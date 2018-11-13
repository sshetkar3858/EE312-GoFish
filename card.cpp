// DOCUMENT HERE

#include "card.h"

using namespace std;

// constructors
Card::Card() {
  // default is ace of spaces
  myRank = 1;
  mySuit = spades;
}

Card::Card(int rank, Suit s) {
  myRank = rank;
  mySuit = s;
}

// functions
string Card::toString() const {
  return (rankString(myRank) + suitString(mySuit));
}
bool Card::sameSuitAs(const Card& c) const {
  return (mySuit == c.mySuit);
}
int Card::getRank() const {
  return myRank;
}
string Card::suitString(Suit s) const {
  string suit;
  switch(s) {
    case spades : suit = "s"; break;
    case hearts : suit = "h"; break;
    case diamonds : suit = "d"; break;
    case clubs : suit = "c"; break;
  }
  return suit;
}
string Card::rankString(int rank) const {
  const int numRanks = 13;
  string ranks[numRanks] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10",
                       "J", "Q", "K"};
  return(ranks[rank-1]); // -1 to offset that A is 1, 2 is 2 etc
}

// relational operators
bool Card::operator == (const Card& rhs) const {
  return(toString() == rhs.toString());
}
bool Card::operator != (const Card& rhs) const {
  return(!(toString() == rhs.toString()));
}

// output stream
ostream& operator << (ostream& out, const Card& c) {
  out << c.toString();
  return out;
}
