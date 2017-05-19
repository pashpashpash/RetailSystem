#include "movie.h"
using namespace std;

Movie::Movie(const string category, const string name, double price, int qty, string genre_, string rating_) : Product(category, name, price, qty)
{
	cout << "Constructing movie: " << name << endl;
	genre = genre_;
	rating = rating_;
}
string Movie::get_genre()
{
	return genre;
} 
string Movie::get_rating()
{
	return rating;
}
string Movie::displayString() const
{
	ostringstream strs;
	strs << name_ << '\n' << "Genre: " << genre << " Rating: " << rating << '\n' << price_ << " " << qty_ << " left." << endl;
	string returnString;
	returnString = strs.str();

	//returnString = category_ + '\n' + name_ + '\n' + price_ + '\n' + qty_ + '\n' + genre + '\n' + rating;
	return returnString;
}
set<string> Movie::keywords() const
{

	set<string> returnSet;
	set<string> nameSet = parseStringToWords(name_);
	set<string> genreSet = parseStringToWords(genre);
	returnSet = setUnion(genreSet, nameSet); 
	return returnSet;
}
void Movie::dump(std::ostream& os) const
{
	Product::dump(os);
	os << genre << '\n' << rating << endl;
}
