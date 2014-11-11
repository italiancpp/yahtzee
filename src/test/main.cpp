#include "gtest/gtest.h"
#include "../utils/MemoryLeakListener.h"

int main(int argc, char* argv[])
{
	using namespace std;
	::testing::InitGoogleTest(&argc, argv);
	::testing::UnitTest::GetInstance()->listeners().Append(new MemLeakListener());
	return RUN_ALL_TESTS();
}
