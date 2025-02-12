#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

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
    // convert raw words to lower case
    // construct words from raw words, stopping at spaces or punctuation
    // if the word has 2 or more characters, add it to our set
    // loop through all of raw words
    rawWords = convToLower(trim(rawWords));
    set<string> words;
    string word = "";

    for (size_t i=0; i<rawWords.length(); i++) {
        char currChar = rawWords[i];
        if (currChar == ' ' || currChar == '.' || currChar == '\'' ||
            currChar == '!' || currChar == '?' || currChar == ';') {
            if (word.length() >= 2) {
                words.insert(word);
            }
            word = "";
        } else {
            word += currChar;
        }
    }
    
    // add the last word if valid
    if (word.length() >= 2) {
        words.insert(word);
    }

    return words;
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
