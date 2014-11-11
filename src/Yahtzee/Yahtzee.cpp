#include "Yahtzee.h"
#include "YahtzeeWriter.h"
#include "GameConfiguration.h"
#include <stdexcept>
#include <algorithm>

using namespace std;

Yahtzee::Yahtzee( const std::vector<DicePlayer>& _players, const GameConfiguration& _conf, YahtzeeWriter& _writer )
	:	players(_players), playerStates(_players.size()), 
		configuration(_conf), writer(_writer),
		currentPlayerIndex(0u), currentTurnNumber(0u),
		dice(_conf.NumberOfDice, 1), scoreCalculator(_conf.MaxDiceValue)
{

}

void Yahtzee::newGame()
{
	playerStates.clear(); playerStates.resize(players.size());
	currentTurnNumber = 1u;
	writer.newGameCreated(players, configuration.TurnsNumber);
	playerStates[currentPlayerIndex].NewTurn();
	writer.startTurnFor(players[currentPlayerIndex], currentTurnNumber);
}

GameState& Yahtzee::CurrentState()
{
	return playerStates[currentPlayerIndex];
}

void Yahtzee::rollDice()
{
	if (!CurrentPlayerHasMoreShots())
		throw domain_error("Current player does not have more shots");

	CurrentState().NewShot();
	players[currentPlayerIndex].RollDice(dice);
	scoreCalculator.CheckScore(dice, CurrentState().IsFirstShot(), CurrentState().potentialScores);
	writer.scoreCalculated(CurrentState().potentialScores);
	writer.diceRolled(dice, CurrentState().GetShotNumber(), players[currentPlayerIndex].MaxNumberOfShots() - CurrentState().GetShotNumber());
}

void Yahtzee::holdDice( const std::vector<int>& diceToHold )
{
	for (int i=0; i<diceToHold.size(); ++i)
		dice[diceToHold[i]].hold = true;
}

void Yahtzee::selectScore( Scores::ScoreName score )
{
	CurrentState().AssignScoreFromPotential(score);
	writer.endTurnFor(players[currentPlayerIndex], CurrentState().currentScores, currentTurnNumber);
	ResetDice();
	currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
	if (currentPlayerIndex == 0) // Verifico che il turno sia finito...
	{
		++currentTurnNumber;
		// verifico che il gioco sia finito
		if (currentTurnNumber > configuration.TurnsNumber) 
		{
			writer.gameOver();
			return;
		}
	}
	playerStates[currentPlayerIndex].NewTurn();
	writer.startTurnFor(players[currentPlayerIndex], currentTurnNumber);
}

std::string Yahtzee::getWinner()
{
	return "";
}

size_t Yahtzee::numberOfPlayers() const
{
	return players.size();
}

void Yahtzee::ResetDice()
{
	for (int i=0; i<dice.size(); ++i)
		dice[i].hold = false;
}

bool Yahtzee::CurrentPlayerHasMoreShots() const
{
	return players[currentPlayerIndex].MaxNumberOfShots() > playerStates[currentPlayerIndex].GetShotNumber();
}

bool PlayerIsBetterThanOther(const std::pair<const DicePlayer*, const ScoreTable*>& one, const std::pair<const DicePlayer*, const ScoreTable*>& other) 
{
	return one.second->TotalScore() > other.second->TotalScore();
}

std::vector<std::pair<const DicePlayer*, const ScoreTable*>> Yahtzee::getRank() const
{
	std::vector<std::pair<const DicePlayer*, const ScoreTable*>> rank;
	for(int i=0; i<players.size(); ++i)
	{
		rank.push_back(make_pair(&players[i], &playerStates[i].currentScores));
	}
	sort(begin(rank), end(rank), PlayerIsBetterThanOther);
	return rank;
}
