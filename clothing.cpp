#include <sstream>
#include <iomanip>
#include "clothing.h"

using namespace std;

Clothing::Clothing(const string category,
        const string name,
        double price,
        int qty,
        const string size,
        const string brand) :
    Product(category, name, price, qty),
    size_(size),
    brand_(brand) {}

Clothing::~Clothing() {}

set<string> Clothing::keywords() const {
    set<string> nameSet = parseStringToWords(name_);
    set<string> brandSet = parseStringToWords(brand_);
    set<string> keywordSet = setUnion(nameSet, brandSet);
    return keywordSet;
}

string Clothing::displayString() const {
    stringstream ss;
    ss << name_ << "\n";
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(ostream& os) const {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ 
    << "\n" << size_ << "\n" << brand_ << endl;
}

string Clothing::getSize() const {
    return size_;
}

string Clothing::getBrand() const {
    return brand_;
}
