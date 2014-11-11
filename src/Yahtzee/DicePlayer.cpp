#include "DicePlayer.h"


DicePlayer::DicePlayer( const std::string& pName, IDiceRoller& r, const DicePlayerConfiguration& conf )
	: name(pName), roller(&r), configuration(conf)
{

}

void DicePlayer::RollDice( std::vector<Die>& dice )
{
	roller->Roll(dice);
}

size_t DicePlayer::MaxNumberOfShots() const
{
	return configuration.NumberOfShots;
}

const std::string& DicePlayer::Name() const
{
	return name;
}
