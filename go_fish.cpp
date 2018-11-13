// FILE: card_demo.cpp
// This is a small demonstration program showing how the bag class is used.
#include <iostream>    // Provides cout and cin
#include <cstdlib>     // Provides EXIT_SUCCESS
#include <fstream>
#include "card.h"
#include "player.h"
#include "deck.h"

using namespace std;


// PROTOTYPES for functions used by this demonstration program:
void dealHand(Deck &d, Player &p, int numCards);




int main()
{
    bool switchPlayer = true; // true = player1, false = player2
    const int numCards = 5;
    ofstream results;
    results.open("gofish_results.txt");

    Player p1("Joe");
    Player p2("Jane");

    Deck d;  //create a deck of cards
    d.shuffle();

    dealHand(d, p1, numCards);
    dealHand(d, p2, numCards);

    cout << p1.getName() <<" has : " << p1.showHand() << endl;
    cout << p2.getName() <<" has : " << p2.showHand() << endl;
    results << p1.getName() <<" has : " << p1.showHand() << endl;
    results << p2.getName() <<" has : " << p2.showHand() << endl << endl;

    // remove all current hands from the players
    Card possibleBook1;
    Card possibleBook2;
    while(p1.checkHandForBook(possibleBook1, possibleBook2)) {
      p1.bookCards(possibleBook1, possibleBook2);
      p1.removeCardFromHand(possibleBook1);
      p1.removeCardFromHand(possibleBook2);
    }

    while(p2.checkHandForBook(possibleBook1, possibleBook2)) {
      p2.bookCards(possibleBook1, possibleBook2);
      p2.removeCardFromHand(possibleBook1);
      p2.removeCardFromHand(possibleBook2);
    }

    cout << p1.getName() <<" has : " << p1.showHand() << endl;
    cout << p2.getName() <<" has : " << p2.showHand() << endl;

    cout << endl << endl;


    while(d.size() != 0 || p1.getHandSize() != 0 || p2.getHandSize() != 0) {
      bool correctChoice = true;

      if(switchPlayer) {
        // player 1 turn
        cout << "Player 1 turn" << endl;
        if(p1.getHandSize() == 0) {
          if(d.size() != 0) {
            Card dealtCard = d.dealCard();
            cout << p1.getName() << " draws " << dealtCard.toString() << endl;
            results << p1.getName() << " draws " << dealtCard.toString() << endl;
            p1.addCard(dealtCard);
          }
        }
        else if(p2.getHandSize() == 0) {
          if(d.size() != 0) {
            Card dealtCard = d.dealCard();
            cout << p1.getName() << " draws " << dealtCard.toString() << endl;
            results << p1.getName() << " draws " << dealtCard.toString() << endl;
            p1.addCard(dealtCard);
          }
        }
        else if(d.size() == 0) {
          Card choiceP1 = p1.chooseCardFromHand();

          cout << p1.getName() << " asks - Do you have a " << choiceP1.rankString(choiceP1.getRank()) << endl;
          results << p1.getName() << " asks - Do you have a " << choiceP1.rankString(choiceP1.getRank()) << endl;
          if(p2.rankInHand(choiceP1)) {
            cout << p2.getName() << " says - Yes. I have a " << choiceP1.rankString(choiceP1.getRank()) << endl;
            results << p2.getName() << " says - Yes. I have a " << choiceP1.rankString(choiceP1.getRank()) << endl;

            Card spades(choiceP1.getRank(), Card::spades);
            Card hearts(choiceP1.getRank(), Card::hearts);
            Card diamonds(choiceP1.getRank(), Card::diamonds);
            Card clubs(choiceP1.getRank(), Card::clubs);
            if(p2.cardInHand(spades))
              p1.addCard(p2.removeCardFromHand(spades));
            if(p2.cardInHand(hearts))
              p1.addCard(p2.removeCardFromHand(hearts));
            if(p2.cardInHand(diamonds))
              p1.addCard(p2.removeCardFromHand(diamonds));
            if(p2.cardInHand(clubs))
              p1.addCard(p2.removeCardFromHand(clubs));

            correctChoice = true;

            cout << p1.getName() << " books the " << choiceP1.rankString(choiceP1.getRank()) << endl;
            results << p1.getName() << " books the " << choiceP1.rankString(choiceP1.getRank()) << endl;
          }
        }
        else {
          correctChoice = true; // enters while loop given other conditions hold


          while(correctChoice && (d.size() != 0 && p2.getHandSize() != 0) && p1.getHandSize() != 0) {
            correctChoice = false; // reset
            // ask other player
            Card choiceP1 = p1.chooseCardFromHand();

            cout << p1.getName() << " asks - Do you have a " << choiceP1.rankString(choiceP1.getRank()) << endl;
            results << p1.getName() << " asks - Do you have a " << choiceP1.rankString(choiceP1.getRank()) << endl;
            if(p2.rankInHand(choiceP1)) {
              cout << p2.getName() << " says - Yes. I have a " << choiceP1.rankString(choiceP1.getRank()) << endl;
              results << p2.getName() << " says - Yes. I have a " << choiceP1.rankString(choiceP1.getRank()) << endl;

              Card spades(choiceP1.getRank(), Card::spades);
              Card hearts(choiceP1.getRank(), Card::hearts);
              Card diamonds(choiceP1.getRank(), Card::diamonds);
              Card clubs(choiceP1.getRank(), Card::clubs);
              if(p2.cardInHand(spades))
                p1.addCard(p2.removeCardFromHand(spades));
              if(p2.cardInHand(hearts))
                p1.addCard(p2.removeCardFromHand(hearts));
              if(p2.cardInHand(diamonds))
                p1.addCard(p2.removeCardFromHand(diamonds));
              if(p2.cardInHand(clubs))
                p1.addCard(p2.removeCardFromHand(clubs));

              correctChoice = true;

              cout << p1.getName() << " books the " << choiceP1.rankString(choiceP1.getRank()) << endl;
              results << p1.getName() << " books the " << choiceP1.rankString(choiceP1.getRank()) << endl;
            }
            else {
              cout << p2.getName() << " says - Go Fish" << endl;
              results << p2.getName() << " says - Go Fish" << endl;
              if(d.size() != 0) {
                Card dealtCard = d.dealCard();
                cout << p1.getName() << " draws " << dealtCard.toString() << endl;
                results << p1.getName() << " draws " << dealtCard.toString() << endl;
                p1.addCard(dealtCard);
              }
              correctChoice = false;
            }

            // book hand if it was drawn
            if(p1.checkHandForBook(possibleBook1, possibleBook2)) {
              p1.bookCards(possibleBook1, possibleBook2);
              p1.removeCardFromHand(possibleBook1);
              p1.removeCardFromHand(possibleBook2);
            }
          }
        }

        // book hand if it was drawn
        if(p1.checkHandForBook(possibleBook1, possibleBook2)) {
          p1.bookCards(possibleBook1, possibleBook2);
          p1.removeCardFromHand(possibleBook1);
          p1.removeCardFromHand(possibleBook2);
        }

        results << endl;

        cout << endl << endl;
        cout << p1.getName() <<" has : " << p1.showHand() << endl;
        cout << p2.getName() <<" has : " << p2.showHand() << endl;
        cout << endl << endl;

        switchPlayer = false;
      }
      else {
        // player 2 turn
        cout << "Player 2 turn" << endl;
        if(p2.getHandSize() == 0) {
          if(d.size() != 0) {
            Card dealtCard = d.dealCard();
            cout << p2.getName() << " draws " << dealtCard.toString() << endl;
            results << p2.getName() << " draws " << dealtCard.toString() << endl;
            p2.addCard(dealtCard);
          }
        }
        else if(p1.getHandSize() == 0) {
          if(d.size() != 0) {
            Card dealtCard = d.dealCard();
            cout << p2.getName() << " draws " << dealtCard.toString() << endl;
            results << p2.getName() << " draws " << dealtCard.toString() << endl;
            p2.addCard(dealtCard);
          }
        }
        else if(d.size() == 0) {
          Card choiceP2 = p2.chooseCardFromHand();

          cout << p2.getName() << " asks - Do you have a " << choiceP2.rankString(choiceP2.getRank()) << endl;
          results << p2.getName() << " asks - Do you have a " << choiceP2.rankString(choiceP2.getRank()) << endl;
          if(p1.rankInHand(choiceP2)) {
            cout << p1.getName() << " says - Yes. I have a " << choiceP2.rankString(choiceP2.getRank()) << endl;
            results << p1.getName() << " says - Yes. I have a " << choiceP2.rankString(choiceP2.getRank()) << endl;

            Card spades(choiceP2.getRank(), Card::spades);
            Card hearts(choiceP2.getRank(), Card::hearts);
            Card diamonds(choiceP2.getRank(), Card::diamonds);
            Card clubs(choiceP2.getRank(), Card::clubs);
            if(p1.cardInHand(spades))
              p2.addCard(p1.removeCardFromHand(spades));
            if(p1.cardInHand(hearts))
              p2.addCard(p1.removeCardFromHand(hearts));
            if(p1.cardInHand(diamonds))
              p2.addCard(p1.removeCardFromHand(diamonds));
            if(p1.cardInHand(clubs))
              p2.addCard(p1.removeCardFromHand(clubs));

            cout << p2.getName() << " books the " << choiceP2.rankString(choiceP2.getRank()) << endl;
            results << p2.getName() << " books the " << choiceP2.rankString(choiceP2.getRank()) << endl;
          }
        }
        else {
          correctChoice = true;

          while(correctChoice && (d.size() != 0 && p1.getHandSize() != 0) && p2.getHandSize() != 0) {
            correctChoice = false; // reset
            // ask other player
            Card choiceP2 = p2.chooseCardFromHand();

            cout << p2.getName() << " asks - Do you have a " << choiceP2.rankString(choiceP2.getRank()) << endl;
            results << p2.getName() << " asks - Do you have a " << choiceP2.rankString(choiceP2.getRank()) << endl;
            if(p1.rankInHand(choiceP2)) {
              cout << p1.getName() << " says - Yes. I have a " << choiceP2.rankString(choiceP2.getRank()) << endl;
              results << p1.getName() << " says - Yes. I have a " << choiceP2.rankString(choiceP2.getRank()) << endl;

              Card spades(choiceP2.getRank(), Card::spades);
              Card hearts(choiceP2.getRank(), Card::hearts);
              Card diamonds(choiceP2.getRank(), Card::diamonds);
              Card clubs(choiceP2.getRank(), Card::clubs);
              if(p1.cardInHand(spades))
                p2.addCard(p1.removeCardFromHand(spades));
              if(p1.cardInHand(hearts))
                p2.addCard(p1.removeCardFromHand(hearts));
              if(p1.cardInHand(diamonds))
                p2.addCard(p1.removeCardFromHand(diamonds));
              if(p1.cardInHand(clubs))
                p2.addCard(p1.removeCardFromHand(clubs));
              correctChoice = true;

              cout << p2.getName() << " books the " << choiceP2.rankString(choiceP2.getRank()) << endl;
              results << p2.getName() << " books the " << choiceP2.rankString(choiceP2.getRank()) << endl;
            }
            else {
              cout << p1.getName() << " says - Go Fish" << endl;
              results << p1.getName() << " says - Go Fish" << endl;

              if(d.size() != 0) {
                Card dealtCard = d.dealCard();
                cout << p2.getName() << " draws " << dealtCard.toString() << endl;
                results << p2.getName() << " draws " << dealtCard.toString() << endl;
                p2.addCard(dealtCard);
              }

              correctChoice = false;
            }

            // book hands if drawn
            if(p2.checkHandForBook(possibleBook1, possibleBook2)) {
              p2.bookCards(possibleBook1, possibleBook2);
              p2.removeCardFromHand(possibleBook1);
              p2.removeCardFromHand(possibleBook2);
            }
          }
        }

        // book hands if drawn
        if(p2.checkHandForBook(possibleBook1, possibleBook2)) {
          p2.bookCards(possibleBook1, possibleBook2);
          p2.removeCardFromHand(possibleBook1);
          p2.removeCardFromHand(possibleBook2);
        }

        results << endl;


        cout << endl << endl;
        cout << p1.getName() <<" has : " << p1.showHand() << endl;
        cout << p2.getName() <<" has : " << p2.showHand() << endl;
        cout << endl << endl;

        switchPlayer = true;
      }

      cout << "DECK SIZE: " << d.size() << endl;
    }

    cout << p1.getName() <<" has : " << p1.getHandSize() << " cards in hand" << endl;
    cout << p2.getName() <<" has : " << p2.getHandSize() << " cards in hand " << endl;

    cout << p1.getName() <<" has : " << p1.showBooks() << endl;
    cout << p2.getName() <<" has : " << p2.showBooks() << endl;

    cout << "card check: " << p1.getHandSize() + p2.getHandSize() + p1.getBookSize() + p2.getBookSize() << endl;

    if(p1.getBookSize() > p2.getBookSize()) {
      cout << p1.getName() << " wins!" << endl;
      results << p1.getName() << " wins!" << endl;
    }
    else {
      cout << p2.getName() << " wins!" << endl;
      results << p2.getName() << " wins!" << endl;
    }

    results.close();

    return EXIT_SUCCESS;
}



void dealHand(Deck &d, Player &p, int numCards)
{
   for (int i=0; i < numCards; i++)
      p.addCard(d.dealCard());
}
