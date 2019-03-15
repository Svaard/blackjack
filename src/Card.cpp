/* 
 * Card class constructs card objects to fill our deck with
 */
#include <string>
#include "Card.h"
using namespace std;

string names[] = {
    "Ace",
    "Two",
    "Three",
    "Four",
    "Five",
    "Six",
    "Seven",
    "Eight",
    "Nine",
    "Ten",
    "Jack",
    "Queen",
    "King"
};

/*
 * Constructor for the card object
 * @parm num is the number of the card we are constructing
 */
Card:: Card(int num) : num(num) {}

const int Card:: getValue() {
    if(num < 11){
        return num;
    }
    else{
        return 10;
    }
}

/*
 * Getter for the name of the card
 */
string Card:: getName() {
    return names[num - 1];
}

/*
 * Function to return boolean indicating if the card is an ace or not
 */
bool Card:: isAce() {
    return num == 1;
}

/*
 * Getter number of card
 */
int Card:: getNum(){
    return num;
}

/*
 * Operator overloading to add cards together so we can get sum later
 */
void Card:: operator=(Card* b){
    num = b->getNum();
}
