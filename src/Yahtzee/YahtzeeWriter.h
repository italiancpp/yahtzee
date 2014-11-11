#pragma once
#include <vector>
#include "Die.h"

class ScoreTable;
class DicePlayer;


class YahtzeeWriter
{
public:
	virtual void newGameCreated(const std::vector<DicePlayer>& players, size_t totalTurns) = 0;
	virtual void startTurnFor(DicePlayer& player, size_t currentTurn) = 0;
	virtual void scoreCalculated(const ScoreTable& scores) = 0;
	virtual void diceRolled(const std::vector<Die>& dice, size_t currentShot, size_t remainingShots) = 0;
	virtual void endTurnFor(DicePlayer& player, const ScoreTable& currentScores, size_t justEndedTurn) = 0;
	virtual void gameOver() = 0;
};