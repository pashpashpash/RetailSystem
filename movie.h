#include "product.h"
#include "util.h"
#include <sstream>
#ifndef MOVIE_H
#define MOVIE_H
using namespace std;

class Movie : public Product
{ 
	public: 
		Movie(const string category, const string name, double price, int qty, string genre_, string rating_);
		~Movie() {}
		string get_genre(); 
		string get_rating();
		string displayString() const;
		set<string> keywords() const;
		void dump(std::ostream& os) const;
	private: 
		string genre; 
		string rating;
};
#endif