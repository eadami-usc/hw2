#include <sstream>
#include <iomanip>
#include "book.h"

using namespace std;

Book::Book(const string category,
        const string name,
        double price,
        int qty,
        const string isbn,
        const string author) :
    Product(category, name, price, qty),
    isbn_(isbn),
    author_(author) {}

Book::~Book() {}

set<string> Book::keywords() const {
    set<string> nameSet = parseStringToWords(name_);
    set<string> authorSet = parseStringToWords(author_);
    set<string> keywordSet = setUnion(nameSet, authorSet);
    keywordSet.insert(isbn_);
    return keywordSet;
}

string Book::displayString() const {
    stringstream ss;
    ss << name_ << "\n";
    ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
    << "\n" << isbn_ << "\n" << author_ << endl;
}

string Book::getISBN() const {
    return isbn_;
}

string Book::getAuthor() const {
    return author_;
}
