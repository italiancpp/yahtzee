#include "PlayerConfiguration.h"

DicePlayerConfiguration::DicePlayerConfiguration( size_t shotsNumber )
	: NumberOfShots(shotsNumber)
{

}

DicePlayerConfiguration DicePlayerConfiguration::DEFAULT_PLAYER_CONFIGURATION = DicePlayerConfiguration(3u);