/* 
 * Player class constructs player object and dealer object, keeps track of money, bets, and hands
 */
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"

/*
 * Constructor for player object
 * @param bool isDealer true if the player object represents a dealer
 */
Player:: Player(bool isDealer){
    this->isDealer = isDealer;
}

/*
 * Getter for the players hand
 */
vector<Card> Player:: getHand(){
    return hand;
}

/*
 * Getter for the players split hand
 */
vector<Card> Player:: getSplitHand(){
    return splitHand;
}

/*
 * Function to split the players hand
 */
void Player:: split(){
    splitHand.push_back(hand.back());
    hand.pop_back();
}

/*
 * Method to bet
 * @param bet is the amount to be bet
 */
void Player:: bet(double bet){
    money -= bet;
    betAmount = bet;
}

/*
 * Setter for money player has
 * @param money is the amount of money
 */
void Player:: setMoney(double money){
    this->money = money;
}

/*
 * Getter for the players money
 */
double Player:: getMoney(){
    return money;
}

/*
 * Returns true if the player is able to split their hand
 */
bool Player:: canSplit(){
    if(splitHand.empty()){
        if(hand.front().getValue() == hand.back().getValue()){
            return true;
        }
    }
    return false;
}

/*
 * Prints the players hand
 */
string Player:: printHand(){
    string s = "";
    for(int i = 0; i < hand.size(); i++){
        string ending = (i == hand.size() - 1) ? "" : ", ";
        s += hand[i].getName() + ending;
    }
    return s;
}

/*
 * Prints the players split hand
 */
string Player:: printSplitHand(){
    string s = "";
    for(int i = 0; i < splitHand.size(); i++){
        string ending = (i == splitHand.size() - 1) ? "" : ", ";
        s += splitHand[i].getName() + ending;
    }
    return s;
}

/*
 * Adds a card to the players hand
 * @param c is the card we want to add to the hand
 */
void Player:: addCard(Card c){
    hand.push_back(c);
}

/*
 * Adds a split card to the players hand
 * c is the card we want to add to the hand
 */
void Player:: addSplitCard(Card c){
    splitHand.push_back(c);
}

/*
 * Calculates sum of players hand
 */
int Player:: getSum(){
    int sum = 0;
    int aces = 0;
    for(int i = 0; i < hand.size(); i++) {
        if(hand[i].getValue() == 1) aces++;
        sum += hand[i].getValue();
    }
    int difference = 21 - sum;
    if(difference > 9 && aces > 0) {
        return sum + 10;
    }
    return sum;
}

/*
 * Calculates sum of players split hand
 */
int Player:: getSplitSum(){
    int sum = 0;
    int aces = 0;
    for(int i = 0; i < splitHand.size(); i++) {
        if(splitHand[i].getValue() == 1) aces++;
        sum += splitHand[i].getValue();
    }
    int difference = 21 - sum;
    if(difference > 9 && aces > 0) {
        return sum + 10;
    }
    return sum;
}

/*
 * Getter for the players bet amount
 */
double Player:: getBetAmount(){
    return betAmount;
}

/*
 * Function to adjust the players money after playing a hand
 * @param amount is the amount we want to adjust the money by
 */
void Player:: adjustMoney(double amount){
    money += amount;
}

/*
 * Function to clear the players hands
 */
void Player:: clearHands() {
    hand.clear();
    splitHand.clear();
}
