#pragma once
#include <string>
#include <functional>
#include "DiceRoller.h"
#include <vector>
#include "PlayerConfiguration.h"

class DicePlayer
{
public:
	DicePlayer(const std::string& pName, IDiceRoller& r, const DicePlayerConfiguration& conf = DicePlayerConfiguration::DEFAULT_PLAYER_CONFIGURATION);

	void RollDice(std::vector<Die>& dice);
	size_t MaxNumberOfShots() const;
	const std::string& Name() const;	
private:
	std::string name;
	IDiceRoller* roller;
	DicePlayerConfiguration configuration;
};

