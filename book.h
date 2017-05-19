#include "product.h"
#include "util.h"
#include <sstream>
#ifndef BOOK_H
#define BOOK_H
using namespace std;
class Book : public Product
{ 
	public: 
		Book(const string category, const string name, double price, int qty, string ISBN_, string author_);
		~Book() {}
		string get_ISBN();
		string get_author();
		string displayString() const;
		set<string> keywords() const;
		void dump(std::ostream& os) const;
	private:
		string ISBN;
		string author;
};
#endif