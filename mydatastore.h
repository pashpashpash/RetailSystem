#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include "product.h"
#include "user.h"
#include "datastore.h"
using namespace std;

/**
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */
class MyDataStore : public DataStore {
public:
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

    std::vector<Product*> productList;
    std::vector<User*> userList;
    std::vector<Review*> allReviews;
    void addReview(Review* r);
    User* loggedInUser;
    vector<pair<string, double> > makeSuggestion();
    map<string, double> dijkstra();
    User* findUserByName(std::string findName);
    map<string, map<string, double> > findSimilarityMap();
    double findSimilarity(User* a, User* b);
    Review* findReview(Product* product, User* user);



private:
    map<string, std::set<Product*> > searchMap;
};

#endif
