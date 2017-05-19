#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <deque>
#include "product.h"
/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    User(std::string name, double balance, int type, unsigned int hashNum);
    virtual ~User();

    double getBalance() const;
    unsigned int getHashNum() const;

    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);

    void addToCart(Product* cartProduct);
    void buyCart();
    void printCart();
    std::deque<Product *> cart;
    void deleteCartItem(Product*);
    std::set<Product*> reviews;

private:
    std::string name_;
    double balance_;
    int type_;
    unsigned int hashNum_;

    //set of reviews this user has left
    //map<User*, double>
    //map<Product*, double>



};
#endif
