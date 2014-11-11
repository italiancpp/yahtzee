#pragma once
#include <string>
#include <vector>
#include "ScoreValues.h"
#include "DicePlayer.h"
#include "GameState.h"
#include "ScoreCalculator.h"

class GameConfiguration;
class YahtzeeWriter;

class Yahtzee
{
public:
	Yahtzee(const std::vector<DicePlayer>& _players, const GameConfiguration& _conf, YahtzeeWriter& _writer);

	size_t numberOfPlayers() const;
	std::vector<std::pair<const DicePlayer*, const ScoreTable*>> getRank() const;
	std::string getWinner();

	void newGame();
	void rollDice(); 
	void holdDice(const std::vector<int>& diceToHold); 
	void selectScore(Scores::ScoreName score); 
	
private:
	void ResetDice();
	bool CurrentPlayerHasMoreShots() const;
	GameState& CurrentState();
	
	std::vector<DicePlayer> players;
	std::vector<GameState> playerStates;
	const GameConfiguration& configuration;
	YahtzeeWriter& writer;
	ScoreCalculator scoreCalculator;

	// game-state info
	size_t currentPlayerIndex, currentTurnNumber;
	std::vector<Die> dice;
};