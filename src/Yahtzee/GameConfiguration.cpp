#include "GameConfiguration.h"
#include "ScoreValues.h"

static const unsigned short DEFAULT_DICE_NUMBER = 5;
static const unsigned short DEFAULT_MAX_DICE_VALUE = 6;

GameConfiguration::GameConfiguration( size_t numOfDice, unsigned short maxDiceValue, size_t turnsNumber )
	: NumberOfDice(numOfDice), MaxDiceValue(maxDiceValue), TurnsNumber(turnsNumber)
{

}

DiceRoller GameConfiguration::DEFAULT_DICE_ROLLER = DiceRoller(DEFAULT_MAX_DICE_VALUE);

GameConfiguration CreateDefaultGameConfiguration()
{
	return GameConfiguration(5u, DEFAULT_MAX_DICE_VALUE, Scores::scores_count);
}
