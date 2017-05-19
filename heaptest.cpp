#include "heap.h"
#include "gtest/gtest.h"
#include <sstream>
using namespace std;
class HeapTest : public testing::Test {
protected:

    HeapTest()
    {

    }

    virtual ~HeapTest()
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

TEST_F(HeapTest, Push) 
{
	Heap<int> myHeap;
	cout << "Pushing 1" << endl;
	myHeap.push(1.0, 1);
	EXPECT_EQ(1, myHeap.top());
	cout << myHeap.top() << endl;
	cout << "Pushing 2" << endl;
	myHeap.push(2.0, 2);
	EXPECT_EQ(1, myHeap.top());
	cout << myHeap.top() << endl;
	cout << "Pushing 3" << endl;
	myHeap.push(3.0, 3);
	EXPECT_EQ(1, myHeap.top());
	cout << myHeap.top() << endl;
	cout << "Pushing 4" << endl;
	myHeap.push(4.0, 4);
	EXPECT_EQ(1, myHeap.top());
	cout << myHeap.top() << endl;
	cout << "Popping" << endl;
	myHeap.pop();
	EXPECT_EQ(2, myHeap.top());
	cout << myHeap.top() << endl;
	cout << "Popping" << endl;
	myHeap.pop();
	EXPECT_EQ(3, myHeap.top());
	cout << myHeap.top() << endl;
	cout << "Popping" << endl;
	myHeap.pop();
	EXPECT_EQ(4, myHeap.top());
	cout << myHeap.top() << endl;
	cout << "Popping" << endl;
	myHeap.pop();
	EXPECT_EQ(true, myHeap.empty());
	// myHeap.push(8);
	// EXPECT_EQ(8, myHeap.top());	
	// myHeap.push(11);
	// EXPECT_EQ(8, myHeap.top());	
	// myHeap.push(12);
	// EXPECT_EQ(8, myHeap.top());	
	// myHeap.push(7);
	// EXPECT_EQ(7, myHeap.top());	
}

TEST_F(HeapTest, PopOne) 
{
	Heap<int> myHeap();
	// myHeap.push(9);
	// myHeap.pop();
	// EXPECT_EQ(0, myHeap.store_.size());	
}

TEST_F(HeapTest, PopMultiple) 
{
	Heap<int> myHeap();
	// myHeap.push(9);
	// myHeap.pop();
	// myHeap.push(9);
	// EXPECT_EQ(9, myHeap.top());	
	// myHeap.pop();
	// EXPECT_EQ(0, myHeap.store_.size());	
	// myHeap.push(8);
	// myHeap.push(9);
	// myHeap.pop();
	// EXPECT_EQ(9, myHeap.top());	
	// myHeap.pop();
	// EXPECT_EQ(0, myHeap.store_.size());
}