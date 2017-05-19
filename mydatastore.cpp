#include <sstream>
#include <iomanip>
#include "mydatastore.h"
#include "util.h"
#include "db_parser.h"
#include "product.h"
#include <map>
#include <stdlib.h>
#include <limits>
#include "heap.h"

using namespace std;

/**
 * Adds a product to the data store
 */
void MyDataStore::addProduct(Product* p)
{
    productList.push_back(p);
    set<string> keywordsList;
    keywordsList = p->keywords();

    for(set<string>::iterator it1 = keywordsList.begin();  it1 != keywordsList.end(); ++it1)
    {
        string keyword = *it1;
        if(searchMap.find(keyword) == searchMap.end()) //if keyword has not been added before
        {
            set<Product*> listOfMatchingProducts;
            listOfMatchingProducts.insert(p);
            pair<string, set<Product*> > myPair(keyword, listOfMatchingProducts);
            searchMap.insert(myPair);
        }

        else //if keyword has been added to the map, then we need to add a pointer of this class to the list of products that the keyword matched to. 
        {
            std::map<string, set<Product*> >::iterator it = searchMap.find(keyword);
            it->second.insert(p); //adds p to the list of matching product pointers (if duplicate, it will be ignored)
        }
    }
}
MyDataStore::~MyDataStore()
{
    for(int i = 0; i < (int)productList.size(); i++)
    {
        delete(productList.at(i));
    }
    for(int i = 0; i < (int)userList.size(); i++)
    {
        delete(userList.at(i));
    }
}
/**
 * Adds a user to the data store
 */
void MyDataStore::addUser(User* u)
{
    userList.push_back(u);
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    std::vector<Product*> returnVec;
    std::set<string> termsList;
    for(int i = 0; i < (int)terms.size(); i++)
    {
        termsList.insert(terms.at(i));
    }

    if(type == 0)
    {
        vector<set<Product*> > mapResults;
        for(set<string>::iterator it = termsList.begin(); it != termsList.end(); ++it) //for each keyword, generate a list of Product* and add that list to a vector
        {
            if(searchMap.find(*it) != searchMap.end()) //match found
            {
                std::map<string, set<Product*> >::iterator it2 = searchMap.find(*it); 
                set<Product*> matchingProductSet = it2->second;
                mapResults.push_back(matchingProductSet);  
            }
        }

        set<Product*> returnSet;
        for(int i = 0; i < (int)mapResults.size(); i++) 
        {
            if(i == 0)
            {
                returnSet = mapResults.at(0); //start first set to intersect with
            }
            else
            {
                returnSet = setIntersection(returnSet, mapResults.at(i)); //continuously setIntersect all the sets in the mapResults vector. 
            }
        }

        for(set<Product*>::iterator it = returnSet.begin(); it != returnSet.end(); ++it) //convert the returnSet to a vector for return
        {
            returnVec.push_back(*it);
        }
    }
    else if(type == 1)
    {
        vector<set<Product*> > mapResults;
        for(set<string>::iterator it = termsList.begin(); it != termsList.end(); ++it) //for each keyword, generate a list of Product* and add that list to a vector
        {
            if(searchMap.find(*it) != searchMap.end()) //match found
            {
                std::map<string, set<Product*> >::iterator it2 = searchMap.find(*it); 
                set<Product*> matchingProductSet = it2->second;
                mapResults.push_back(matchingProductSet);  
            }
        }

        set<Product*> returnSet;
        for(int i = 0; i < (int)mapResults.size(); i++) 
        {
            if(i == 0)
            {
                returnSet = mapResults.at(0); //start first set to intersect with
            }
            else
            {
                returnSet = setUnion(returnSet, mapResults.at(i)); //continuously setUnion all the sets in the mapResults vector. 
            }
        }

        for(set<Product*>::iterator it = returnSet.begin(); it != returnSet.end(); ++it) //convert the returnSet to a vector for return
        {
            returnVec.push_back(*it);
        }
    }
    return returnVec;
}

/**
 * Reproduce the database file from the current Products and User values
 */
void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << endl;
    for(int i=0; i < (int)productList.size(); i++)
    {
        productList.at(i)->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for(int i =0; i < (int)userList.size(); i++)
    {
        userList.at(i)->dump(ofile);
    }
    ofile << "</users>" << endl;
    ofile << "<reviews>" << endl;
    for(int i =0; i < (int)allReviews.size(); i++)
    {
    	ofile << allReviews.at(i)->prodName << endl;
    	ofile << allReviews.at(i)->rating << ' ' << allReviews.at(i)->username << ' ' << allReviews.at(i)->date  << ' ' << allReviews.at(i)->reviewText << endl;
    }
    ofile << "</reviews>" << endl;
}  

void MyDataStore::addReview(Review* r)
{

	string productName = r->prodName;
    Product * p = NULL;
	for(int i = 0; i < (int)productList.size(); i++)
	{

		if(productName == productList.at(i)->getName()) //match found
		{
			productList.at(i)->addReview(r);
			allReviews.push_back(r);
            p = productList.at(i);
            User* a = findUserByName(r->username);
            if(a != NULL)
            {
                a->reviews.insert(p);
            }
			return;
		}
	}

    
	allReviews.push_back(r);
}

vector<pair<string, double> > MyDataStore::makeSuggestion()
{

    vector<pair<string, double> > returnVec;
    map<string, double> similarUsers = dijkstra();
    
    for(int i = 0; i < (int)productList.size(); i++)
    {
        vector<Review*> reviews = productList.at(i)->reviewList;
        set<User*> userReviewSet;
        double totalRating = 0;
        double totalSum = 0;
        for(int j = 0; j< (int)reviews.size(); j++)
        {
            double sim = 1;
            string name = reviews.at(j)->username;
            User* user = findUserByName(name);
            if(user != NULL)
            {
                userReviewSet.insert(user);
            }
            if(user != loggedInUser)
            {
                sim = similarUsers[user->getName()];
            }
            double rating = (double)reviews.at(j)->rating;
            totalRating = totalRating + (1-sim)*rating;
            totalSum = totalSum + 1 - sim;

        }  //once this for loop ends, we've assembled all of the user*'s that have left reviews on a particular product.
        if(userReviewSet.find(loggedInUser) == userReviewSet.end())
        {

            //cout << "totalRating = " << totalRating << " totalSim = " << totalSum << endl;
            double finalRating = totalRating/totalSum;
            if(totalRating == 0 && totalSum == 0)
            {
                finalRating = 0;
            }
            //cout << "FinL rating" << finalRating << endl;
            returnVec.push_back(std::make_pair(productList.at(i)->getName(), finalRating));

        }
    }
    return returnVec;
}

map<string, double> MyDataStore::dijkstra()
{
    map<string, double> returnMap;
    map<string, map<string, double> > userGraph = findSimilarityMap();
    Heap<string> pq; 
    double infinity = std::numeric_limits<double>::infinity();
    pq.push(0.0, loggedInUser->getName());
    for(int i = 0; i < (int)userList.size(); i++)
    {
        if(userList.at(i) != loggedInUser)
        {
            pq.push(infinity, userList.at(i)->getName());
        }
    }

    //returnMap = userGraph[loggedInUser->getName()];
    while(!pq.empty())
    {
        string topUser = pq.top().second;
        //returnMap[topUser] = pq.top().first;
        User* ignorethisUser = findUserByName(topUser);
        pq.pop();
        for(int i = 0; i < (int)userList.size(); i++)
        {
            if(userList.at(i) != ignorethisUser)
            {
                string neighborUser = userList.at(i)->getName();

                double similarity = userGraph[ignorethisUser->getName()][neighborUser];

                pq.decreaseKey(similarity, neighborUser);
                if(!pq.empty())
                {
                    returnMap[neighborUser] = pq.top().first;

                }
            }
        }
    }


    return returnMap;
}

map<string, map<string, double> >  MyDataStore::findSimilarityMap()
{
    map<string, map<string, double> > returnMap; //map of Users as keys and maps of all other users and their weights as values.
    for(int i = 0; i < (int)userList.size(); i++)
    {
        map<string, double> tMap;
        for(int j = 0; j < (int) userList.size(); j++)
        {
            if(i != j)
            {
               
                tMap[userList.at(j)->getName()] = findSimilarity(userList.at(i), userList.at(j));
                
            }
        }
        returnMap[userList.at(i)->getName()] = tMap;
    }
    return returnMap;
}

double MyDataStore::findSimilarity(User* a, User* b)
{
    double returndouble = 0;
    set<Product*> userAReviews = a->reviews;
    set<Product*> userBReviews = b->reviews;
    set<Product*> resultSet = setIntersection(userAReviews, userBReviews);

    double similaritySum = 0;
    if(resultSet.size() == 0)
    {
        return 1.0; //no similarity
    }
    
    for(set<Product*>::iterator it = resultSet.begin(); it != resultSet.end(); ++it)
    {
        Review* userARating = findReview(*it, a);
        Review* userBRating = findReview(*it, b);
        if (userARating != NULL && userBRating != NULL)
        {
            double r1 = (double)userARating->rating;
            double r2 = (double)userBRating->rating;
            double similarity = (double)abs(r1 - r2)/4;
            similaritySum = similaritySum + similarity;
        }

    }
    returndouble = similaritySum/resultSet.size();


    return returndouble;
}

Review* MyDataStore::findReview(Product* product, User* user)
{
    Review* returnRev = NULL;
    vector<Review*> reviewList = product->reviewList;
    for(int i = 0; i < (int)reviewList.size(); i++)
    {
        if(reviewList.at(i)->username == user->getName())
        {
            return reviewList.at(i);
        }
    }

    return returnRev;
}

User* MyDataStore::findUserByName(string findName)
{
    User* returnUser = NULL;
    vector<User*> allUsers = userList;
    for(int i =0; i<(int)allUsers.size(); i++)
    {
        if(findName == allUsers.at(i)->getName())
        {
            returnUser = allUsers.at(i);
        }
    }
    return returnUser;
}