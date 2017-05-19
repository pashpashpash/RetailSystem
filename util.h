#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>
using namespace std;

/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates  
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	set<T> returnSet;
	for(typename set<T>::iterator it1 = s1.begin();  it1 != s1.end(); ++it1)
	{
		for(typename set<T>::iterator it2 = s2.begin();  it2 != s2.end(); ++it2)
		{
			if(*it1 == *it2)
			{
				returnSet.insert(*it1);
			}
		}
	}
	return returnSet;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	set<T> returnSet;
	for(typename set<T>::iterator it1 = s1.begin();  it1 != s1.end(); ++it1)
	{
		returnSet.insert(*it1);
	}
	for(typename set<T>::iterator it2 = s2.begin();  it2 != s2.end(); ++it2)
	{
		returnSet.insert(*it2);
	}
	return returnSet;
 }

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) ;

// trim from end
std::string &rtrim(std::string &s) ;

// trim from both ends
std::string &trim(std::string &s) ;
#endif
