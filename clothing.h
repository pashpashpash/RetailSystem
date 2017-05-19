#include "product.h"
#include "util.h"
#include <sstream>
#ifndef CLOTHING_H
#define CLOTHING_H
using namespace std;

class Clothing : public Product
{
	public: 
		Clothing(const string category, const string name, double price, int qty, string brand_, string size_);
		~Clothing() { }
		string get_brand(); 
		string get_size();
		string displayString() const;
		set<string> keywords() const;
		void dump(std::ostream& os) const;
	private: 
		string brand; 
		string size;
};
#endif

