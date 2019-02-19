#ifndef Player_h
#define Player_h

#include <vector>
#include <string>
#include "Card.h"
#include "Account.h"

class Player{
private:
    vector<Card> hand;
    vector<Card> splitHand;
    Account account;
    double money;
    double betAmount;
    bool isDealer;
public:
    Player(bool);
    vector<Card> getHand();
    vector<Card> getSplitHand();
    void split();
    void bet(double);
    void setMoney(double);
    double getMoney();
    bool canSplit();
    string printHand();
    string printSplitHand();
    void addCard(Card);
    void addSplitCard(Card);
    int getSum();
    int getSplitSum();
    double getBetAmount();
    void adjustMoney(double);
    Card getFirstCard();
    void clearHands();
};
#endif /* Player_h */
