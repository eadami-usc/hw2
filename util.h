#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    // iterate through s1
    // try to find each element from s1 in s2
    // if it exists, add it to the intersection set

    std::set<T> intersectionSet;

    for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it) {
        typename std::set<T>::iterator it2 = s2.find(*it);
        if (it2 != s2.end()) {
            intersectionSet.insert(*it2);
        }
    }

    return intersectionSet;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    // insert every element from s1 and s2 into union set

    std::set<T> unionSet;

    for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it) {
        unionSet.insert(*it);
    }
    for (typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it) {
        unionSet.insert(*it);
    }

    return unionSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
