/* 
 * Blackjack Tester class, includes gameplay and menu function
 */
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>
#include <ctime>
#include "Player.h"
#include "Account.h"
#include "Card.h"
using namespace std;

vector<Card> deck;
bool faceUp;
map<int, Account> accounts;
void hit(Player&);
void splitHit(Player&);
void deal(Player&, Player&);
void altSwap(Card&, Card&);
void shuffle();
void generateDeck();
Card getCard();
void calculateScore(Player&, Player);
void menu(Player&, Player&);
void game(Player&);
bool validInput();

int main() {
    srand((unsigned int) time(NULL));
    string player;
    cout << "Are you a new player? (y/n)> ";
    cin >> player;
    if(player == "y"){
        Player p = Player(false);
        cout << "How much money would you like to start your account with? ($1 - $1,000,000)\n> ";
        double money = 0;
        do {
            cin >> money;
        }
        while(!validInput());
        while(money < 1 || money > 1000000){
            cout << "You have entered an invalid amount, please try again: " << endl;
            do {
                cin >> money;
            }
            while(!validInput());
        }
        Account a = Account(money);
        while(accounts.count(a.getAccountNumber()) > 0){
            a.setAccountNumber(a.getAccountNumber() + 1);
        }
        cout << "Your account number is " << a.getAccountNumber() << endl;
        accounts.emplace(a.getAccountNumber(), a);
        p.setMoney(a.getMoney());
        cout << "You have $" << (int) p.getMoney() << " in your account. What would you like to do? " << endl;
        game(p);
        a.setMoney(p.getMoney());
        cout << "Your account balance is: $" << (int) a.getMoney() << "\nGoodbye." << endl;
    }
    else {
        if(accounts.size() > 0){
            Player p = Player(false);
            cout << "Please enter your account number\n> ";
            int num;
            do {
                cin >> num;
            }
            while(!validInput());
            try{
                Account temp = accounts.at(num);
                p.setMoney(temp.getMoney());
                cout << "You have " << p.getMoney() << " in your account." << endl;
                game(p);
            }
            catch(const out_of_range& oor){
                cerr << "Out of Range error: " << oor.what() << endl;
                main();
            }
        }
        else{
            cout << "We did not find any existing accounts." << endl;
            main();
        }
    }
    return 0;
}

/*
 * Function for hitting to hand
 * @param &p is player pointer whose hand we hit to
 */
void hit(Player &p){
    p.addCard(getCard());
}

/*
 * Function to split players hanbd
 * @param &p is player pointer whose hand we are splitting
 */
void splitHit(Player &p){
    p.addSplitCard(getCard());
}

/*
 * Deals card to the player and dealer
 * @param &p is pointer for the player we deal to
 * @param &d is pointer for the dealer we deal to
 */
void deal(Player &p, Player &d){
    for(int i = 0; i < 2; i++){
        p.addCard(getCard());
        d.addCard(getCard());
    }
}

/*
 * Swaps cards
 * @param &a is card we swap with card b
 * @param &b is the card we swap with card a
 */
void altSwap(Card &a, Card &b){
    Card temp = a;
    a = b;
    b = temp;
}

/*
 * Function to shuffle the deck
 */
void shuffle(){
    for (int k = 0; k < deck.size(); k++) {
        int r = k + rand() % (deck.size() - k);
        altSwap(deck[k], deck[r]);
    }
}

/*
 * Function to generate the deck
 */
void generateDeck(){
    deck = vector<Card>();
    for(int i = 1; i < 14; i++){
        deck.push_back(Card(i));
        deck.push_back(Card(i));
        deck.push_back(Card(i));
        deck.push_back(Card(i));
    }
    shuffle();
}

/*
 * Gets card from deck, remove it from deck and returns it so we can use it to deal
 */
Card getCard(){
    Card c = deck.back();
    deck.pop_back();
    return c;
}

/*
 * Caluclates score of hands
 * @param &p is the player whose hand we are caluclating score of
 * @param &d is the dealer we are calculating score of
 */
void calculateScore(Player &p, Player d){
    if(p.getSum() > d.getSum()){
        cout << "You won for main hand!" << endl;
        cout << "You win: $" << (int)(p.getBetAmount() * 2) << endl;
        p.adjustMoney(p.getBetAmount() * 2);
    }
    else if(p.getSum() == d.getSum()){
        cout << "You tied with the dealer!" << endl;
        cout << "You get back: $" << (int)(p.getBetAmount() / 2) << endl;
        p.adjustMoney(p.getBetAmount() / 2);
    }
    else{
        if(!p.getSplitHand().empty()) {
            cout << "You lost with your main hand!" << endl;
            cout << "You lost: $" << (int) p.getBetAmount() << endl;
        }
        else {
            cout << "You lose!" << endl;
            cout << "You lost: $" << (int) p.getBetAmount() << endl;
        }
    }
    if(!p.getSplitHand().empty()){
        if(p.getSplitSum() > d.getSum()){
            cout << "You won for split hand!" << endl;
            cout << "You win: $" << (int)(p.getBetAmount() * 2) << endl;
            p.adjustMoney(p.getBetAmount() * 2);
        }
        else if(p.getSplitSum() == d.getSum()){
            cout << "You tied with the dealer!" << endl;
            cout << "You get back: $" << p.getBetAmount() / 2 << endl;
            p.adjustMoney(p.getBetAmount() / 2);
        }
        else{
            cout << "You lost with your split hand!" << endl;
            cout << "You lost: $" << (int) p.getBetAmount() << endl;
        }
    }
}

/*
 * Menu for the blackjack game, check if player want to hit, split, stand, or quit
 * @param &p is player object we enter so we can use it in function calls within the menu
 * @param &d is dealer object we enter for use in function calls within menu
 */
void menu(Player &p, Player &d){
    int num;
    cout << "\nTo hit, enter 1: " << endl;
    cout << "To split, enter 2: " << endl;
    cout << "To stand, enter 3: " << endl;
    cout << "To quit, enter 4:\n$" << (int) p.getMoney() << " > ";
    do {
        cin >> num;
        while(num == 2 && !p.getSplitHand().empty()){
            cout << "You cannot split again! Please enter another option\n> ";
            cin >> num;
        }
    }
    while(!validInput());
    switch (num){
        case 1:
            hit(p);
            cout << "\nYou have: " << p.printHand() << " = " << p.getSum() << endl;
            cout << "Dealer is showing a " << d.getHand()[0].getName() << " and a face down card." << endl;
            if(p.getSum() < 22){
                menu(p, d);
            }
            else{
                cout << "You bust!" << endl;
                cout << "You lose $" << (int) p.getBetAmount() << endl;
                return;
            }
            break;
        case 2:
            if(p.canSplit() && p.getMoney() >= p.getBetAmount()){
                p.split();
                p.adjustMoney(-p.getBetAmount());
                p.addCard(getCard());
                cout << "Your first hand has: " << p.printHand() << " = " << p.getSum() << endl;
                cout << "Dealer is showing a " << d.getHand()[0].getName() << " and a face down card." << endl;
                menu(p, d);
            }
            else if(p.getMoney() < p.getBetAmount()) {
                cout << "You don't have enough money to split!" << endl;
                menu(p, d);
            }
            else {
                cout << "You need two of the same value cards to split!" << endl;
                menu(p, d);
            }
            break;
        case 3:
            if(!p.getSplitHand().empty()){
                p.addSplitCard(getCard());
                bool toHit = true;
                while(toHit) {
                    cout << "Your split hand has: " << p.printSplitHand() << " = " << p.getSplitSum() << endl;
                    cout << "Dealer is showing a " << d.getHand()[0].getName() << " and a face down card." << endl;
                    cout << "Hit to your split hand? (y/n)\n> ";
                    string hit;
                    cin >> hit;
                    if(hit == "y" || hit == "yes"){
                        p.addSplitCard(getCard());
                    }
                    else {
                        toHit = false;
                    }
                    if(p.getSplitSum() > 21){
                        cout << "You busted!" << endl;
                        toHit = false;
                    }
                }
            }
            cout << "You are standing with: " << p.getSum() << endl;
            if(!p.getSplitHand().empty()){
                cout << "You are standing with " << p.getSplitSum() << " for you split hand." << endl;
            }
            cout << "\nDealer has: " << d.printHand() << " = " << d.getSum() << endl;
            while(d.getSum() < 17){
                cout << "Dealer hits..." << endl;
                hit(d);
                cout << "Dealer has: " << d.printHand() << " = " << d.getSum() << endl;
                if(d.getSum() > 21) {
                    cout << "Dealer busts!\n";
                    if(p.getSum() < 22) {
                        cout << "You win $" << (int) p.getBetAmount() * 2 << " for your main hand." << endl;
                        p.adjustMoney(p.getBetAmount() * 2);
                    }
                    if(!p.getSplitHand().empty() && p.getSplitSum() < 22) {
                        cout << "You win $" << (int) p.getBetAmount() * 2 << " for your split hand." << endl;
                        p.adjustMoney(p.getBetAmount() * 2);
                    }
                    return;
                }
            }
            if(d.getSum() > 16) {
                calculateScore(p, d);
            }
            break;
        case 4:
            cout << "Goodbye." << endl;
            exit(0);
        default:
            cout << "You did not enter a valid option." << endl;
            menu(p, d);
    }
}

/*
 * Funtion that contains the gameplay logic for the blackjack game
 * @param &p is player we want to give menu options to
 */
void game(Player &p){
    Player dealer = Player(true);
    while(true){
        generateDeck();
        if(p.getMoney() < 10) {
            cout << "You're broke!" << endl;
            return;
        }
        p.clearHands();
        dealer.clearHands();
        cout << p.printHand() << endl;
        cout << p.printSplitHand() << endl;
        string answer;
        cout << "Would you like to play a hand? You have $" << (int) p.getMoney() << " (y/n)\n> ";
        cin >> answer;
        if(answer == "y" || answer == "yes"){
            double bet = 0;
            cout << "\nHow much would you like to bet? ($10 - $10,000)\n> ";
            do {
                cin >> bet;
            }
            while(!validInput());
            while(true) {
                while(bet < 10 || bet > 10000) {
                    cout << "You have entered an invalid amount, please try again\n> ";
                    do {
                        cin >> bet;
                    }
                    while(!validInput());
                }
                if(bet <= p.getMoney()) break;
                cout << "You don't have enough money in your account, please try a different amount\n> ";
                do {
                    cin >> bet;
                }
                while(!validInput());
            }
            cout << "Betting $" << (int) bet << endl;
            p.bet(bet);
            deal(p, dealer);
            cout << "\nYou have: " << p.printHand() << " = " << p.getSum() << endl;
            cout << "Dealer is showing a " << dealer.getHand()[0].getName() << endl;
            if(p.getSum() == 21){
                cout << "You win!" << endl;
                cout << "You won: " << (int)(p.getBetAmount() * 2) << endl;
                p.adjustMoney(p.getBetAmount() * 2);
            }
            else if(dealer.getSum() == 21){
                cout << "Dealer reveals blackjack! You lose!" << endl;
            }
            else{
                menu(p, dealer);
            }
        }
        else if(answer == "n" || answer == "no"){
            cout << "\nA strange game. The only winning move is not to play." << endl << endl;
            return;
        }
        else{
            cout << "\nYou did not choose a valid option. Please try again." << endl;
        }
    }
}

/*
 * Function to check if we are getting valid input from cin for menu options
 */
bool validInput() {
    if(!cin.fail()) return true;
    cout << "Invalid input! Please try again\n> ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return false;
}
