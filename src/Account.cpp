/* 
 * Account class will construct an account for a player and keep their money safe
 */
#include "Account.h"
#include <random>
using namespace std;

/*
 * Default constructor for the account object
 */
Account:: Account(){
    
}

/*
 * Overloaded constructor for account object
 * @param totalMoney is the amount of money we want the account to start with
 */
Account:: Account(double totalMoney){
    this->totalMoney = totalMoney;
    accountNumber = generateNum();
}

/*
 * Setter for the account number
 * @param accountNumber is the number we want to set as the account number
 */
void Account:: setAccountNumber(int accountNumber){
    this->accountNumber = accountNumber;
}

/*
 * Getter for the account number
 */
int Account:: getAccountNumber(){
    return accountNumber;
}

/*
 * Getter for the money in the account
 */
double Account:: getMoney(){
    return totalMoney;
}

/*
 * Setter for the money in the account
 * @param totalMoney is the amount of money we want to set for the account
 */
void Account:: setMoney(double totalMoney){
    this->totalMoney = totalMoney;
}

/*
 * Random number generator to create unique acount numbers
 */
int Account:: generateNum(){
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(1000000, 9999999); // define the range
    return distr(eng);
}
