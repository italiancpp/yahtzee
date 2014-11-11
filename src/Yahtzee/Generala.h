#pragma once

#include "GameState.h"
#include "Die.h"
#include "DiceRoller.h"
#include "ScoreCalculator.h"
#include <vector>
#include "YahtzeeWriter.h"
#include "GameConfiguration.h"

class Generala
{
	size_t _playerNum;
	
	std::vector<GameState> _states;
	size_t current_turn;
		
	static const size_t shots_number; // TODO: move to config object for player 

	size_t player_count;
	size_t current_state_index;
	size_t current_shot;

	std::vector<Die> dice;
	IDiceRoller& roller; // TODO: move to player (e.g. player X has a special roller)
	
	YahtzeeWriter *yahtzeeWriter;
	ScoreCalculator calculator;
	const GameConfiguration& configuration;

public:

	Generala(IDiceRoller& _roller, const GameConfiguration& conf, YahtzeeWriter *writer);

	GameState& state();
	size_t playerNumber();
	void playerNumber(size_t n);
	int Start();
    void rollDice();
	void selectScore(Scores::ScoreName score);
	void holdDice(std::vector<int> diceIndex);

	// interfaccia minimale che potremmo realizzare
	void StartGame(); // inizia il gioco (e.g. setta il primo turno)
	void _rollDice(); // tira i dadi per giocatore corrente e calcola il punteggio
	void _holdDice(const std::vector<int>& diceToHold); // fa hold di alcuni dadi
	void endTurn(Scores::ScoreName score); // fine turno giocatore corrente
	std::string getWinner();
		// utils
		size_t numberOfPlayers() const;
};

