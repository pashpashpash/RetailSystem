#include <iostream>
#include <sstream>
#include <cctype>
#include "util.h"
#include <iomanip>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>


using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  set<string> wordSet;
  string word;
  rawWords = convToLower(rawWords);
  for(int i = 0; i < (int)rawWords.size(); ++i) //replaces all punctuation with spaces
  {
    if (ispunct(rawWords[i]))
    {
        rawWords[i] = ' ';
    }
  }

  istringstream parseThis(rawWords);

  while(parseThis >> word) //moves word by word, throws out all words less than 2 characters long.
  {
    if(word.size() >= 2)
    {
        wordSet.insert(word);
    }
  }
  return wordSet;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
