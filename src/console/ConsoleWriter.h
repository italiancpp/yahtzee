#pragma once

#include <vector>
#include <stdlib.h>
#include "../Yahtzee/ScoreTable.h"
#include "../Yahtzee/YahtzeeWriter.h"
#include "../Yahtzee/DicePlayer.h"
#include "../Yahtzee/Yahtzee.h"

class ConsoleWriter : public YahtzeeWriter
{
public:
	virtual void startTurnFor(DicePlayer &player, size_t currentTurn);
	virtual void newGameCreated(const std::vector<DicePlayer> &players, size_t totalTurns);
	virtual void scoreCalculated(const ScoreTable &scores);
	virtual void diceRolled(const std::vector<Die> &dice, size_t currentShot, size_t remainingShots);
	virtual void endTurnFor(DicePlayer &player, const ScoreTable &currentScores, size_t justEndedTurn);
	virtual void gameOver();

	void run();

private:
	int getPlayerNumber();
	std::vector<DicePlayer> createPlayers(int number);
	void selectScore(Yahtzee &yahtzee);
	void selectDieToHold(Yahtzee &yahtzee);
};
