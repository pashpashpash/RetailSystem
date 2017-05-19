#include "splay.h"
#include "gtest/gtest.h"
#include <sstream>
 using namespace std;
class SplayTest : public testing::Test {
protected:

    SplayTest()
    {

    }

    virtual ~SplayTest()
    {

    }
   
    virtual void SetUp()
    {

    }
    
    virtual void TearDown() 
    {
		// Code here will be called immediately after each test (right
		// before the destructor).
	}
    
};

TEST_F(SplayTest, Push) 
{
	splay_tree<int> mysplay;
	cout << "Inserting 1 through 7" << endl;
	mysplay.insert(1);
	mysplay.insert(2);
	mysplay.insert(3);
	mysplay.insert(4);
	mysplay.insert(5);
	mysplay.insert(6);
	mysplay.insert(7);
	mysplay.print();
	cout << "Finding 1" << endl;
	mysplay.find(1);
	mysplay.print();
	cout << "Finding 3" << endl;
	mysplay.find(3);
	mysplay.print();
	cout << "erasing 3" << endl;
	mysplay.erase(3);
	mysplay.print();

	EXPECT_EQ(1, mysplay.minimum()) << mysplay.minimum() << endl;	
}
