#include "user.h"
using namespace std;

User::User() : name_("unknown"), balance_(0.0), type_(1), hashNum_(0.0)
{

}
User::User(std::string name, double balance, int type, unsigned int hashNum) :
    name_(name), balance_(balance), type_(type), hashNum_(hashNum)
{

}

User::~User()
{

}


std::string User::getName() const
{
    return name_;
}

double User::getBalance() const
{
    return balance_;
}
unsigned int User::getHashNum() const
{
    return hashNum_;
}

void User::deductAmount(double amt)
{
    balance_ -= amt;
}

void User::dump(std::ostream& os)
{
    os << name_ << " "  << balance_ << " " << type_ << " " << hashNum_ << endl;
}

void User::addToCart(Product* cartProduct)
{
	cart.push_back(cartProduct);
}
void User::buyCart()
{
	deque<Product*>::iterator it = cart.begin(); 
	while(it != cart.end())
	{
		it = cart.begin();
		for(it; it != cart.end(); ++it) 
		{
			int quantity = (*it)->getQty();
			if(quantity >= 1) //in stock
			{
				int price = (*it)->getPrice();
				if (price <= balance_) //if user has enough money
				{
					balance_ = balance_-price;
					(*it)->subtractQty(1);
					cart.erase(it);
					break;
				}
			}
		}
	}
}
void User::printCart()
{
	int num = 1;
	for(deque<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) 
	{
		cout << "Cart Item #" << num <<  endl;
		cout << (*it)->displayString();
		num++;
	}
}
void User::deleteCartItem(Product* productTodelete)
{
	for(deque<Product*>::iterator it = cart.begin(); it != cart.end(); ++it) 
	{
		if((*it)->getName() == productTodelete->getName())
		{
			cart.erase(it);
			return;
		}
	}
}