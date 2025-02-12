#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
    // delete all products
    for (Product* p : products_) {
        delete p;
    }
    
    // delete all users
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        delete it->second;
    }
}

void MyDataStore::addProduct(Product* p) {
    // when we add products, we will add the product to each of its keywords in our map
    for (string keyword : p->keywords()) {
        keyword_to_products_[keyword].insert(p);
    }
    products_.push_back(p);
}

void MyDataStore::addUser(User* u) {
    // add users as keys in a map of users to carts
    users_[convToLower(u->getName())] = u;
    users_to_cart_[u];
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type) {
    // Get the product set for each term
    // if type 0, then intersect each set
    // if type 1, then union each set
    set<Product*> result;
    bool firstTerm = true;

    for (string term : terms) {
        map<string, set<Product*>>::iterator it = keyword_to_products_.find(convToLower(term));
        if (it != keyword_to_products_.end()) {
            set<Product*> productSet = it->second;
            if (firstTerm) {
                result = productSet;
                firstTerm = false;
            } else {
                if (type == 0) {
                    result = setIntersection(result, productSet);
                } else {
                    result = setUnion(result, productSet);
                }
            }
        }
    }

    return vector<Product*>(result.begin(), result.end());
}

void MyDataStore::addToCart(std::string username, std::vector<Product*> hits, int hit_result_index) {
    // find the user of the provided username
    // find the product at the hit_result_index
    // add the product to user's cart
    // handle invalids
    map<string, User*>::iterator it = users_.find(convToLower(username));
    hit_result_index--;

    if (it == users_.end() || hit_result_index < 0 || hit_result_index >= (int) hits.size()) {
        cout << "Invalid request" << endl;
        return;
    }

    User* user = it->second;
    Product* product = hits[hit_result_index];
    users_to_cart_[user].push_back(product);
}

void MyDataStore::viewCart(std::string username) {
    // find the user of the provided username
    // print the cart of the user
    // handle invalids
    map<string, User*>::iterator it = users_.find(convToLower(username));

    if (it == users_.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    User* user = it->second;
    deque<Product*> cart = users_to_cart_[user];
    int counter = 1;

    for (Product* product : cart) {
        cout << "Item " << counter << endl;
        cout << product->displayString() << endl;
        counter++;
    }
}

void MyDataStore::buyCart(std::string username) {
    // find the user of the provided username
    // iterate through the user's cart
    // if product is in stock and user has enough money, buy the product
    // if not, continue through cart
    // handle invalids
    map<string, User*>::iterator it = users_.find(convToLower(username));

    if (it == users_.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    User* user = it->second;
    deque<Product*> cart = users_to_cart_[user];
    deque<Product*> remaining_cart;

    for (Product* product : cart) {
        if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
            product->subtractQty(1);
            user->deductAmount(product->getPrice());
        } else {
            remaining_cart.push_back(product);
        }
    }

    users_to_cart_[user] = remaining_cart;
}

void MyDataStore::dump(ostream& ofile) {
    // dump products to database file
    ofile << "<products>" << endl;
    for (Product* product : products_) {
        product->dump(ofile);
    }
    ofile << "</products>" << endl;

    // dump users to database file
    ofile << "<users>" << endl;
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;
}
