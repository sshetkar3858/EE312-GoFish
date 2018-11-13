// DOCUMENT HERE
 #include "player.h"

 using namespace std;

// constructors
Player::Player() {
  myName = ""; // DEFAULT
  srand(time(0));
}

void Player::addCard(Card c) {
  myHand.push_back(c);
  srand(time(0));
}

void Player::bookCards(Card c1, Card c2) {
  myBook.push_back(c1);
  myBook.push_back(c2);
}

bool Player::checkHandForBook(Card &c1, Card &c2) {
  for(int i = 0; i<getHandSize()-1; i++) {
    for(int j = i+1; j<getHandSize(); j++) {
      if(myHand[i].getRank() == myHand[j].getRank()) {
        c1 = myHand[i];
        c2 = myHand[j];
        return true;
      }
    }
  }
  return false;
  // what to populate c1 and c2 if false?
}

bool Player::rankInHand(Card c) const {
  bool found = false;
  int i = 0;
  while(i < getHandSize() && !found) {
    if(myHand[i].getRank() == c.getRank())
      found = true;
    i++;
  }
  return found;
}


Card Player::chooseCardFromHand() const {
  if(getHandSize() != 0)
    return myHand[rand() % myHand.size()]; // idk better strat?
  else
    return Card(1, Card::spades); // ask for ace spades if you don't have anything?
}

bool Player::cardInHand(Card c) const {
  bool found = false;
  int i = 0;
  while(i<getHandSize() && !found) {
    if(myHand[i] == c)
      found = true;
    i++;
  }
  return found;
}

Card Player::removeCardFromHand(Card c) {
  int i = 0;
  bool found = false;
  while(i < getHandSize() && !found) {
    if(myHand[i] == c) {
      myHand.erase(myHand.begin() + i);
      found = true;
    }
    i++;
  }
  return c;
}

string Player::showHand() const {
  string hand = "";
  for(int i = 0; i<getHandSize(); i++) {
    hand += (myHand[i].toString() + " ");
  }
  return hand;
}
string Player::showBooks() const {
  string book = "";
  for(int i = 0; i<getBookSize(); i++) {
    book += (myBook[i].toString() + " ");
  }
  return book;
}

int Player::getHandSize() const {
  return myHand.size();
}
int Player::getBookSize() const {
  return myBook.size();
}

bool Player::checkHandForPair(Card &c1, Card &c2) {
  for(int i = 0; i<getHandSize()-1; i++) {
    for(int j = i+1; j<getHandSize(); j++) {
      if(myHand[i] == myHand[j]) {
        c1 = myHand[i];
        c2 = myHand[j];
        return true;
      }
    }
  }
  return false;
  // what to populate c1 and c2 if false?
}

bool Player::sameRankInHand(Card c) const {
  bool found = false;
  int i = 0;
  while(i < getHandSize() && !found) {
    if(myHand[i].getRank() == c.getRank())
      found = true;
    i++;
  }
  return found;
}
