#include <ostream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "ConsoleWriter.h"
#include "../Yahtzee/Yahtzee.h"
#include "../Yahtzee/GameConfiguration.h"

using namespace std;

// TODO -> C'è ancora nei nomi generala, andrebbe sistituito con yahtzee
// TODO -> Se non premo h o s o r, ora è come se premessi r, avrebbe senso insistere e richiedere una scelta
// TODO -> Se non ci sono più tiri disponibili si deve chiedere quale score scegliere, ora tira un eccezione
// TODO -> Occorre stampare diversamente la tabella dello score per dare la posizione dello score
// TODO -> Non è possibile 'resettare' i dati che si erano tenuti il giro prima
// TODO -> Se assegni uno score già presente tira una eccezzione
// TODO -> Non viene controllato che si inserisca il numero corretto del dado (si può dire di tenere il dato 12)
// TODO -> Avrebbe senso stampare prima i dadi e poi il potential score, per fare questo ha senso fare un test


void ConsoleWriter::startTurnFor(DicePlayer &player, size_t currentTurn)
{
	cout << "Inizia il turno (" << currentTurn << ") per il giocatore '" << player.Name() << "'" << endl;
}

void ConsoleWriter::newGameCreated(const std::vector<DicePlayer> &players, size_t totalTurns)
{
	cout << "Inizio GAME!!!" << endl;
}

void ConsoleWriter::scoreCalculated(const ScoreTable &scores)
{
	cout << "*************************************" << endl;
	cout << "* Score                             *" << endl;
	cout << "*************************************" << endl;
	cout << scores << endl;
	cout << endl;
}

void ConsoleWriter::diceRolled(const std::vector<Die> &dice, size_t currentShot, size_t remainingShots)
{
	cout << "*************************************" << endl;
	cout << "* Dadi                              *" << endl;
	cout << "*************************************" << endl;
	cout << "Tiro numero: " << currentShot << " - Rimanenti: " << remainingShots << endl;
	cout << "Valore:    ";
	for_each(begin(dice), end(dice), [](const Die die) {
		cout << die.value << " ";
	});
	cout << endl;
	cout << "           ";
	for_each(begin(dice), end(dice), [](const Die die) {
		cout << (die.hold? " " : "^") << " ";
	});
	cout << endl;
	cout << "Posizione: ";
	for(int i = 0; i < dice.size(); i++)
	{
		cout << i+1 << " ";
	}
	cout << endl;
	cout << endl;
}

void ConsoleWriter::endTurnFor(DicePlayer &player, const ScoreTable &currentScores, size_t justEndedTurn)
{
	cout << "Fine del turno per " << player.Name() << endl;
	cout << "Punteggio " << currentScores << endl;
	cout << "Turni terminati " << justEndedTurn << endl;
}

void ConsoleWriter::gameOver()
{
	cout << "GAME OVER!!!!!" << endl;
}

void ConsoleWriter::run()
{
	auto playerNumber = getPlayerNumber();
	auto players = createPlayers(playerNumber);

	GameConfiguration yahtzeeConfig(5, 6, 13);
	Yahtzee yahtzee(players, yahtzeeConfig, *this);

	yahtzee.newGame();
	while(true)
	{
		try
		{
			yahtzee.rollDice();
		}
		catch(...)
		{
			cout << "Hai finito i tiri! Scegli uno score!" << endl;
			selectScore(yahtzee);
			continue;
		}

		cout << "s + Enter -> Selezioni lo score " << endl;
		cout << "h + Enter -> Selezioni i dadi da tenere" << endl;
		cout << "r + Enter -> Lancia i dadi" << endl;
		cout << "> ";

		string cmd;
		bool done = false;
		while(!done)
		{
			done = true;
			cin >> cmd;

			if (cmd == "s")
			{
				selectScore(yahtzee);
			}
			else if (cmd == "h")
			{
				selectDieToHold(yahtzee);
			}
			else if (cmd != "r")
			{
				cout << "Non capisco :( > "; 
				done = false;
			}
		}
		
	}
}

int ConsoleWriter::getPlayerNumber()
{
	int playerNumber = 0;
	cout << "Quanti giocatori vogliono giocare? ";
	cin >> playerNumber;
	return playerNumber;
}

std::vector<DicePlayer> ConsoleWriter::createPlayers(int number)
{
	std::vector<DicePlayer> players;
	string playerName;
	for (int i = 0; i < number; ++i)
	{
		cout << "Nome del giocatore " << i+1 << "> ";
		cin >> playerName;
		auto player = DicePlayer(playerName, GameConfiguration::DEFAULT_DICE_ROLLER);
		players.push_back(player);
	}

	return players;

}

void ConsoleWriter::selectScore(Yahtzee &yahtzee)
{
	cout << "Scrivi la posizione dello score da tenere (1, 2, etc ..) > ";
	bool done = false;
	int scoreIndex;
	while (!done)
	{
		cin >> scoreIndex;
		try
		{
			yahtzee.selectScore((Scores::ScoreName)(scoreIndex - 1));
			done = true;
		}
		catch(...)
		{
			cout << "Hai gia' selezionato questo score...scegli di nuovo > ";
		}
	}
}


template<typename T>
ostream& operator<<(ostream& stream, const vector<T> &values)
{
	for_each(values.begin(), values.end(), [&](const T &v) {
		stream << v << " ";
	});
	return stream;
//	for (int i=0; i<table.scores.size(); ++i)
//		stream << score_names[i] << " -> " << table.scores[i].value << (table.scores[i].assigned ? "" : " *") << std::endl;
//	return stream;
}

void ConsoleWriter::selectDieToHold(Yahtzee &yahtzee)
{

	cin.ignore();
	cout << "Scrivi le posizioni dei dadi da tenere (1 2 etc ...) ";
	string dieIndex;
	getline(cin, dieIndex);

	vector<string> tokens;
	istringstream iss(dieIndex);
//	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
	istream_iterator<string> eos;
	for(istream_iterator<string> iit(iss); iit != eos; ++iit)
	{
		tokens.push_back(*iit);
	}

	std::vector<int> diceToHold;
	for (auto& token : tokens)
	{
		auto h = stoul(token);
		if (h < 6)
		{
			diceToHold.push_back(h - 1);
		}
	}

	yahtzee.holdDice(diceToHold);
}


