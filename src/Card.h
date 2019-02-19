#ifndef Card_h
#define Card_h

#include <string>
using namespace std;

class Card {
private:
    int num;
public:
    Card(int);
    const int getValue();
    string getName();
    bool isAce();
    int getNum();
    void operator=(Card*);
};

#endif /* Card_h */
