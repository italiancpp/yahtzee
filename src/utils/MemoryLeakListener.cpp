#include "MemoryLeakListener.h"
#include "debug-new/MemoryLeak.h"


void MemLeakListener::OnTestStart( const ::testing::TestInfo& test_info )
{
	MemoryLeak::start(false);
}

void MemLeakListener::OnTestEnd( const ::testing::TestInfo& test_info )
{
	if(test_info.result()->Passed())
	{
		if (MemoryLeak::stop())
		{
			FAIL() << "Memory leak in " << test_info.test_case_name() << "." << test_info.name() << '\n';
		}
	}
}

