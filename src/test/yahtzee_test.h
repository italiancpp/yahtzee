#pragma once

#include "gtest/gtest.h"
#include "../Yahtzee/YahtzeeWriter.h"
#include "../Yahtzee/ScoreTable.h"
#include "../Yahtzee/DicePlayer.h"
#include <vector>

class MockYahtzeeWriter : public YahtzeeWriter
{
public:
	MockYahtzeeWriter()
		:	called_newGameCreated(0), called_startTurnFor(0),
		called_diceRolled(0), called_scoreCalculated(0), called_endTurnFor(0),
		called_gameOver(0)
	{

	}

	virtual void newGameCreated( const std::vector<DicePlayer>& pPlayers, size_t pTotalTurns ) 
	{
		++called_newGameCreated;
		newGameCreated_players = pPlayers;
		newGameCreated_totalTurns = pTotalTurns;
	}

	virtual void startTurnFor( DicePlayer& player, size_t currentTurn ) 
	{
		++called_startTurnFor;
		startTurnFor_currentTurn = currentTurn;
		startTurnFor_playerName = player.Name();
	}

	virtual void diceRolled( const std::vector<Die>& dice, size_t currentShot, size_t remainingShots ) 
	{
		++called_diceRolled;
		diceRolled_diceValue = dice;
		diceRolled_currentShot = currentShot;
		diceRolled_remaningShots = remainingShots;
	}

	virtual void endTurnFor( DicePlayer& player, const ScoreTable& currentScores, size_t justEndedTurn ) 
	{
		++called_endTurnFor;
		endTurnFor_playerName = player.Name();
		endTurnFor_currentScores = currentScores;
	}

	virtual void scoreCalculated( const ScoreTable& scores ) 
	{
		++called_scoreCalculated;	
		scoreCalculated_scores = scores;
	}

	virtual void gameOver() 
	{
		++called_gameOver;
	}

	// **** member variables to emulate mocks **** //

	// function called counters
	int called_newGameCreated;
	int called_startTurnFor;
	int called_diceRolled;
	int called_scoreCalculated;
	int called_endTurnFor;
	int called_gameOver;

	// functiona called args
	std::vector<DicePlayer> newGameCreated_players;
	size_t newGameCreated_totalTurns;

	size_t startTurnFor_currentTurn;
	std::string startTurnFor_playerName;

	std::vector<Die> diceRolled_diceValue;
	size_t diceRolled_remaningShots;
	size_t diceRolled_currentShot;

	ScoreTable scoreCalculated_scores;

	std::string endTurnFor_playerName;
	ScoreTable endTurnFor_currentScores;
};

class MockDiceRoller : public IDiceRoller
{
public:
	MockDiceRoller()
	{
		for (int i=0; i<5; i++)
		{
			mockedValues[i] = 1;
		}
	}

	void AssignDiceValues(int values[5])
	{
		for (int i=0; i<5; i++)
		{
			mockedValues[i] = values[i];
		}
	}

	void Roll(std::vector<Die>& dice) override
	{
		for (int i=0; i<5; i++)
		{
			dice[i] = mockedValues[i];
		}
	}

	int mockedValues[5];
};

class YahtzeeTest : public ::testing::Test
{
protected:
	std::vector<DicePlayer> CreateOnePlayerAsMarcoWithMockedRoller();

	MockYahtzeeWriter writer;
	MockDiceRoller mockedRoller;
};