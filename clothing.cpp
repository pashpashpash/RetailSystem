#include "clothing.h"
using namespace std;

Clothing::Clothing(const string category, const string name, double price, int qty, string brand_, string size_) : Product(category, name, price, qty)
{
	cout << "Constructing Clothing: " << name << endl;
	brand = brand_;
	size = size_;
}
string Clothing::get_brand()
{
	return brand;
} 
string Clothing::get_size()
{
	return size;
}
string Clothing::displayString() const
{
	ostringstream strs;
	strs << name_ << '\n' << "Size: " << size << " Brand: " << brand << '\n' << price_ << " " << qty_ << " left." << endl;
	string returnString;
	returnString = strs.str();

	//returnString = category_ + '\n' + name_ + '\n' + price_ + '\n' + qty_ + '\n' + genre + '\n' + rating;
	return returnString;
}
set<string> Clothing::keywords() const
{

	set<string> returnSet;
	set<string> nameSet = parseStringToWords(name_);
	set<string> brandSet = parseStringToWords(brand);
	returnSet = setUnion(brandSet, nameSet); 
	return returnSet;
}
void Clothing::dump(std::ostream& os) const
{
	Product::dump(os);
	os << size << '\n' << brand << endl;
}