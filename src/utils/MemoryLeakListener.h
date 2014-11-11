#pragma once
#include "gtest/gtest.h"

class MemLeakListener : public ::testing::EmptyTestEventListener 
{
public:
	void OnTestStart(const ::testing::TestInfo& test_info);
	void OnTestEnd(const ::testing::TestInfo& test_info);
}; 
