#include <sstream>
#include <iomanip>
#include "movie.h"

using namespace std;

Movie::Movie(const string category,
        const string name,
        double price,
        int qty,
        const string genre,
        const string rating) :
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating) {}

Movie::~Movie() {}

set<string> Movie::keywords() const {
    set<string> keywordSet = parseStringToWords(name_);
    keywordSet.insert(convToLower(genre_));
    return keywordSet;
}

string Movie::displayString() const {
    stringstream ss;
    ss << name_ << "\n";
    ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
    << "\n" << genre_ << "\n" << rating_ << endl;
}

string Movie::getGenre() const {
    return genre_;
}

string Movie::getRating() const {
    return rating_;
}
