#ifndef Account_h
#define Account_h

#include <stdio.h>

class Account{
private:
    double totalMoney;
    int accountNumber;
public:
    Account();
    Account(double);
    void setAccountNumber(int accountNumber);
    int getAccountNumber();
    double getMoney();
    void setMoney(double totalMoney);
    int generateNum();
};

#endif /* Account_h */
