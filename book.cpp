#include "book.h"
using namespace std;

Book::Book(const string category, const string name, double price, int qty, string ISBN_, string author_) : Product(category, name, price, qty)
{
	cout << "Constructing Book: " << name << endl;
	ISBN = ISBN_;
	author = author_;
}
string Book::get_ISBN()
{
	return ISBN;
} 
string Book::get_author()
{
	return author;
}
string Book::displayString() const
{
	ostringstream strs;
	strs << name_ << '\n' << "Author: " << author << " ISBN: " << ISBN << '\n' << price_ << " " << qty_ << " left." << endl;
	string returnString;
	returnString = strs.str();

	//returnString = category_ + '\n' + name_ + '\n' + price_ + '\n' + qty_ + '\n' + genre + '\n' + rating;
	return returnString;
}
set<string> Book::keywords() const
{
	set<string> returnSet;
	set<string> nameSet = parseStringToWords(name_);
	set<string> ISBNSet;
	ISBNSet.insert(ISBN);
	set<string> authorSet = parseStringToWords(author);
	set<string> tempSet = setUnion(authorSet, nameSet); 
	returnSet = setUnion(tempSet, ISBNSet); 
	return returnSet;
}
void Book::dump(std::ostream& os) const
{
	Product::dump(os);
	os << author << '\n' << ISBN << endl;
}