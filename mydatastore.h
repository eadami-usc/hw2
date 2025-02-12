#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <map>
#include <deque>
#include "datastore.h"
#include "util.h"

class MyDataStore : public DataStore {
public:
    MyDataStore();

    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    // My functions below:

    void addToCart(std::string username, std::vector<Product*> hits, int hit_result_index);

    void viewCart(std::string username);

    void buyCart(std::string username);

private:
    std::vector<Product*> products_;
    std::map<std::string, std::set<Product*>> keyword_to_products_;
    std::map<std::string, User*> users_;
    std::map<User*, std::deque<Product*>> users_to_cart_;
};

#endif