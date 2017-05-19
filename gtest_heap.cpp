#include <random>
#include <queue>

#include "gtest/gtest.h"
#include "/home/student/csci104/hw-pashints/hw8/heap.h"
#include "random.h"

#define RANDOM_HEAP_ARY 0
const int MAX_HEAP_ARY = 26;
const int DEFAULT_HEAP_ARY = 2;

// Declaration for the type of item that will be stored in the heap.
typedef int __ITEM_TYPE_DECL;

// Declaration for the kind of heap that will be tested. Change the type 
// here to change what kind of heap will be tested.
typedef Heap<__ITEM_TYPE_DECL> __PRIORITY_QUEUE_TYPE_DECL;

typedef std::pair<double, __ITEM_TYPE_DECL> __CPP_PRIORITY_QUEUE_ITEM_TYPE_DECL;

struct PairCompGreater
{
	bool operator()(const __CPP_PRIORITY_QUEUE_ITEM_TYPE_DECL& lhs, const __CPP_PRIORITY_QUEUE_ITEM_TYPE_DECL& rhs)
	{
		return lhs.first > rhs.first;
	}
} PairComparator;

// Declaration for the type of std::heap used when checking during stress tests. 
typedef std::priority_queue<__CPP_PRIORITY_QUEUE_ITEM_TYPE_DECL, std::deque<__CPP_PRIORITY_QUEUE_ITEM_TYPE_DECL>, PairCompGreater > __CPP_PRIORITY_QUEUE_TYPE_DECL;

// Declaration for the type of index generator. 
typedef cs104::random_integer_number_generator<int> __RANDOM_INDEX_GENERATOR;

// Declaration for the kind of random number generator. 
typedef cs104::random_integer_number_generator<__ITEM_TYPE_DECL> __RANDOM_NUMBER_GENERATOR;

typedef cs104::random_real_number_generator<double> __RANDOM_DOUBLE_GENERATOR;

// The random seed used to initialize the random number generator. If set to std::random_device()() then the
// tests will truly be random. Otherwise it should be set to some literal integer. 
#define RANDOM_SEED 57821

// Define statements for the various functions that are used when testing
// the linked list. If the interface changes, these define statements are
// useful to rename the function call without replacing calls for every
// instance in the tests. 
#define __EMPTY()                      empty()
#define __PUSH(PRIORITY, ELEMENT)      push(PRIORITY, ELEMENT)
#define __POP()                        pop()
#define __FRONT()                      top()
#define __UPDATE(PRIORITY, ELEMENT)    decreaseKey(PRIORITY, ELEMENT)

#define STRESS_TEST_PUSH_POP_UNTIL_EMPTY(NUMBER_OF_ELEMENTS, HEAP) { \
	int numberOfElementsInserted{ 0 }; \
	__CPP_PRIORITY_QUEUE_TYPE_DECL checker; \
	__RANDOM_NUMBER_GENERATOR randomGenerator{ RANDOM_SEED }; \
	__RANDOM_DOUBLE_GENERATOR randomDoubleGenerator{ RANDOM_SEED }; \
	while(numberOfElementsInserted++ < NUMBER_OF_ELEMENTS) { \
		__ITEM_TYPE_DECL randomNumber{ randomGenerator() }; \
		double randomPriority{ randomDoubleGenerator() }; \
		HEAP.__PUSH(randomPriority, randomNumber); \
		checker.push(std::make_pair(randomPriority, randomNumber)); \
	} \
	while(!checker.empty()) { \
		EXPECT_EQ(checker.top().second, HEAP.__FRONT()); \
		checker.pop(); \
		HEAP.__POP(); \
	} \
}

#define STRESS_TEST_RANDOM_PUSH_POP(NUMBER_OF_ELEMENTS, HEAP) { \
	int numberOfElementsInserted{ 0 }; \
	int numberOfElementsRemoved{ 0 }; \
	__CPP_PRIORITY_QUEUE_TYPE_DECL checker; \
	__RANDOM_NUMBER_GENERATOR randomGenerator{ RANDOM_SEED }; \
	__RANDOM_INDEX_GENERATOR randomIndexGenerator{ RANDOM_SEED }; \
	__RANDOM_DOUBLE_GENERATOR randomDoubleGenerator{ RANDOM_SEED }; \
	while(numberOfElementsInserted < NUMBER_OF_ELEMENTS || numberOfElementsRemoved < NUMBER_OF_ELEMENTS) { \
		int numberOfElementsToPush{ randomIndexGenerator(0, NUMBER_OF_ELEMENTS - numberOfElementsInserted) }; \
		while(numberOfElementsToPush-- > 0) { \
			__ITEM_TYPE_DECL randomNumber{ randomGenerator() }; \
			double randomPriority{ randomDoubleGenerator() }; \
			checker.push(std::make_pair(randomPriority, randomNumber)); \
			HEAP.__PUSH(randomPriority, randomNumber); \
			++numberOfElementsInserted; \
		} \
		if(!checker.empty()) { \
			int numberOfElementsToPop{ randomIndexGenerator(1, checker.size()) }; \
			while(numberOfElementsToPop-- > 0) { \
				EXPECT_EQ(checker.top().second, HEAP.__FRONT()); \
				checker.pop(); \
				HEAP.__POP(); \
				++numberOfElementsRemoved; \
			} \
		} \
	} \
	EXPECT_EQ(NUMBER_OF_ELEMENTS, numberOfElementsInserted); \
	EXPECT_EQ(NUMBER_OF_ELEMENTS, numberOfElementsRemoved); \
}

// Macro to wrap a try catch block and then use a test to check if 
// an exception was caught or not. 
#define TRY_CATCH(CODE, EXCEPTION, SHOULD_CATCH) \
	bool caughtException{ false }; \
	try { \
		CODE; \
	} catch(EXCEPTION& e) { \
		caughtException = true; \
	} \
	EXPECT_EQ(SHOULD_CATCH, caughtException); \

// Testing setup.
class HeapTest : public testing::Test
{
	protected:
		HeapTest()
		{ 
			#if RANDOM_HEAP_ARY
			__RANDOM_NUMBER_GENERATOR randomGenerator{ RANDOM_SEED };
			D_ARY = randomGenerator() % MAX_HEAP_ARY + 3;
			#else
			D_ARY = DEFAULT_HEAP_ARY;
			#endif
		}
		~HeapTest() { }
		virtual void SetUp() { }
		virtual void TearDown() { }

		int D_ARY;
};

// Main function, declared so that flags can be used when testing. 
int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

TEST_F(HeapTest, PushSingleItemCheckEmpty)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	EXPECT_FALSE(heap.__EMPTY());
}

TEST_F(HeapTest, PushSingleItemCheckFront)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	EXPECT_EQ(10, heap.__FRONT());
}

TEST_F(HeapTest, PushSingleElementPopCheckEmpty)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	heap.__POP();
	EXPECT_TRUE(heap.__EMPTY());
}

TEST_F(HeapTest, PushTwoElementsCheckFrontSmaller)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(2.0, 20);
	EXPECT_EQ(10, heap.__FRONT());
}

TEST_F(HeapTest, PushTwoElementsCheckFrontLarger)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(2.0, 20);
	heap.__PUSH(1.0, 10);
	EXPECT_EQ(10, heap.__FRONT());
}

TEST_F(HeapTest, PushTwoElementsSmallerPopCheckFront)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(2.0, 20);
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
}

TEST_F(HeapTest, PushTwoElementsLargerPopCheckFront)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(2.0, 20);
	heap.__PUSH(1.0, 10);
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_10_20_30)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(2.0, 20);
	heap.__PUSH(3.0, 30);
	EXPECT_EQ(10, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(30, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_10_30_20)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(3.0, 30);
	heap.__PUSH(2.0, 20);
	EXPECT_EQ(10, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(30, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_20_10_30)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(2.0, 20);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(3.0, 30);
	EXPECT_EQ(10, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(30, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_20_30_10)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(2.0, 20);
	heap.__PUSH(3.0, 30);
	heap.__PUSH(1.0, 10);
	EXPECT_EQ(10, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(30, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_30_10_20)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(3.0, 30);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(2.0, 20);
	EXPECT_EQ(10, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(30, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_30_20_10)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(3.0, 30);
	heap.__PUSH(2.0, 20);
	heap.__PUSH(1.0, 10);
	EXPECT_EQ(10, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(30, heap.__FRONT());
}

TEST_F(HeapTest, PushTwoElementsUpdatePriorityNoPromotion)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(2.0, 20);
	heap.__UPDATE(0.5, 10);
	EXPECT_EQ(10, heap.__FRONT());
}

TEST_F(HeapTest, PushTwoElementsUpdatePriorityPromotion)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(2.0, 20);
	heap.__UPDATE(0.5, 20);
	EXPECT_EQ(20, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_10_20_30_Update_30_20_10)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(2.0, 20);
	heap.__PUSH(3.0, 30);
	heap.__UPDATE(0.5, 30);
	heap.__UPDATE(0.6, 20);
	EXPECT_EQ(30, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(10, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_10_30_20_Update_20_30_10)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(3.0, 30);
	heap.__PUSH(2.0, 20);
	heap.__UPDATE(0.5, 20);
	heap.__UPDATE(0.6, 30);
	EXPECT_EQ(20, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(30, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(10, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_20_10_30_Update_30_10_20)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(2.0, 20);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(3.0, 30);
	heap.__UPDATE(0.5, 30);
	EXPECT_EQ(30, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(10, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_20_30_10_Update_10_30_20)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(2.0, 20);
	heap.__PUSH(3.0, 30);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(1.5, 30);
	EXPECT_EQ(10, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(30, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_30_10_20_Update_20_10_30)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(3.0, 30);
	heap.__PUSH(1.0, 10);
	heap.__PUSH(2.0, 20);
	heap.__UPDATE(0.5, 20);
	EXPECT_EQ(20, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(10, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(30, heap.__FRONT());
}

TEST_F(HeapTest, PushThreeElements_30_20_10_Update_10_20_30)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	heap.__PUSH(3.0, 30);
	heap.__PUSH(2.0, 20);
	heap.__PUSH(1.0, 10);
	heap.__UPDATE(0.5, 10);
	heap.__UPDATE(0.6, 20);
	heap.__UPDATE(0.7, 30);
	EXPECT_EQ(10, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(20, heap.__FRONT());
	heap.__POP();
	EXPECT_EQ(30, heap.__FRONT());
}

TEST_F(HeapTest, Runtime_Push100Elements_Pop100Elements)
{
	std::cout << "> > > > Runtime test: Operations should increase on the order of O(n * log n) < < < <" << std::endl;
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	STRESS_TEST_RANDOM_PUSH_POP(100, heap);
}

TEST_F(HeapTest, Runtime_Push1000Elements_Pop1000Elements)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	STRESS_TEST_RANDOM_PUSH_POP(1000, heap);
}

TEST_F(HeapTest, Runtime_Push10000Elements_Pop10000Elements)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	STRESS_TEST_RANDOM_PUSH_POP(10000, heap);
}

TEST_F(HeapTest, Runtime_Push100000Elements_Pop100000Elements)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	STRESS_TEST_RANDOM_PUSH_POP(100000, heap);
}

TEST_F(HeapTest, Runtime_Mix100PushAndPopOperations)
{
	std::cout << "> > > > Runtime test: Operations should increase on the order of O(n * log n) < < < <" << std::endl;
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	STRESS_TEST_PUSH_POP_UNTIL_EMPTY(100, heap);
}

TEST_F(HeapTest, Runtime_Mix1000PushAndPopOperations)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	STRESS_TEST_PUSH_POP_UNTIL_EMPTY(1000, heap);
}

TEST_F(HeapTest, Runtime_Mix10000PushAndPopOperations)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	STRESS_TEST_PUSH_POP_UNTIL_EMPTY(10000, heap);
}

TEST_F(HeapTest, Runtime_Mix100000PushAndPopOperations)
{
	__PRIORITY_QUEUE_TYPE_DECL heap(D_ARY);
	STRESS_TEST_PUSH_POP_UNTIL_EMPTY(100000, heap);
}
