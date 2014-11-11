#pragma once

#include <random>
#include <vector>
#include "Die.h"

class IDiceRoller
{
public:
	virtual void Roll(std::vector<Die>& dice) = 0;
};

class DiceRoller : public IDiceRoller
{
public:
	DiceRoller(unsigned short pMaxDiceValue);
	void Roll(std::vector<Die>& dice) override;

private:
	const unsigned short maxDiceValue;
	std::default_random_engine rengine;
};

