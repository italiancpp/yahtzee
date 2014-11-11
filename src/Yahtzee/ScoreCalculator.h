#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "Rule.h"
#include "Die.h"

class ScoreCalculator
{
public:
	
	ScoreCalculator(unsigned short _maxDiceValue);
	~ScoreCalculator();

	void CheckScore(const std::vector<Die>& dice, bool isFirstShot, ScoreTable& currentTable) const;
private:
	unsigned short maxDiceValue;
};

