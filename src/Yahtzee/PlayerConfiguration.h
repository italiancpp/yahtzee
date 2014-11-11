#pragma once

#include <stdlib.h>

class DicePlayerConfiguration
{
public:
	DicePlayerConfiguration(size_t shotsNumber);

	static DicePlayerConfiguration DEFAULT_PLAYER_CONFIGURATION;

	size_t NumberOfShots; 
};