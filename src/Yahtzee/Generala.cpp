
/************************************************************************/
/* WARNING: QUESTO FILE SARA' BUTTATO AL PIU' PRESTO                    */
/************************************************************************/

#include "Generala.h"
#include "DiceRoller.h"
#include "ScoreValues.h"
#include "ScoreCalculator.h"
#include "GameState.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string.h>

using namespace std;

void hold_all(vector<Die>& dice, bool hold)
{
	for (auto& die : dice)
	{
		die.hold = hold;
	}
}

void print_dice(const vector<Die>& dice)
{
	for (auto& die : dice)
	{
		cout << die.value << " ";
	}
	cout << endl;
	cout << endl;
}

void ChooseScore(GameState &state, Scores::ScoreName name)
{
	cout << "Choose a line with '*' > ";
	string line;
//	getline(cin, line);
	cout << "CHOSEN " << line << endl;
	
	//state.AssignScoreFromPotential(name);
	
	cout << endl;
	cout << "CURRENT SCORES" << endl;
//	cout << state.currentScores;
} 

const size_t Generala::shots_number = 3;


Generala::Generala( IDiceRoller& _roller, const GameConfiguration& conf, YahtzeeWriter *writer ) 
	:	_playerNum(0), dice(conf.NumberOfDice, Die(1)), roller(_roller), 
		yahtzeeWriter(writer), configuration(conf), calculator(conf.MaxDiceValue),
		player_count(0u), current_state_index(1u)
{
	current_turn = Scores::scores_count;
	current_shot = Generala::shots_number;
}


GameState& Generala::state()
{
	return _states[current_state_index];
}

size_t Generala::playerNumber()
{
	return _playerNum;
}

void Generala::playerNumber( size_t n )
{
	auto old = _playerNum;
	_states.resize(n);
	_playerNum = n;
	//yahtzeeWriter->numberOfPlayersChanged(old, _playerNum);
}

int Generala::Start()
{

//	while (current_turn--)
	{
//		for (auto& state : _states)
		{
			state().NewTurn();
			player_count++;
		
//			system("cls");
//			cout << "Player [" << player_count++ << "] Turn: " << turns_number - current_turn << " of " << turns_number << endl;
//			cout << endl;
			//yahtzeeWriter->startTurnFor(player_count, current_turn, configuration.TurnsNumber);



//			while(current_shot--)
			{
//				state().NewShot();
//
//				roller.Roll(dice);
//				print_dice(dice);
//
//				calculator.CheckScore(dice, max_dice_value, state());
//				cout << state().potentialScores;
//				hold_all(dice, false);
//
//				cout << endl;

//				if (current_shot)
//				{
//					cout << "Hold? ('S' if served) > ";
//					string toHold;
//					getline( cin, toHold );
//
//					if (toHold == "S" || toHold == "s")
//					{
//						ChooseScore(state);
//						break;
//					}
//
//					else
//					{
//						istringstream ss(toHold);
//						vector<string> tokens;
//						copy(istream_iterator<string>(ss), istream_iterator<string>(), back_inserter(tokens));
//
//						for (auto& token : tokens)
//						{
//							auto h = stoul(token);
//							if (h < 6)
//							{
//								dice[h-1].hold = true;
//							}
//						}
//					}
//				}
//				else
//				{
//					ChooseScore(state);
//				}
			}
		}
	}
		
	//system("cls");

	size_t player_count = 1u;
	
//	for (auto& state : _states)
//	{
//		cout << "-----" << endl;
//		cout << "Player [" << player_count << "] FINAL SCORE TABLE" << endl;
//		cout << endl;
//		cout << state.currentScores << endl;
//		cout << "Total Score: " << state.currentScores.TotalScore() << endl;
//		cout << endl;
//		player_count++;
//	}
	
	//cout << endl;
	auto worst_best = minmax_element(begin(_states), end(_states), [](const GameState& state1, const GameState& state2) 
		{
			return state1.currentScores.TotalScore() < state2.currentScores.TotalScore();
		});

	if (worst_best.first == worst_best.second)
	{
		cout << "Deuce!" << endl;
	}

	else if (_states.size() > 1)
	{
		cout << "The winner is player " << distance(begin(_states), worst_best.second) + 1 << endl;
		cout << "The worst is player " << distance(begin(_states), worst_best.first) + 1 << endl;
	}

	return 0;
}

void Generala::rollDice()
{
	state().NewShot();

	roller.Roll(dice);
	print_dice(dice);

	//calculator.CheckScore(dice, configuration.MaxDiceValue, state());
	//yahtzeeWriter->showPotentialScores(state().potentialScores);
	hold_all(dice, false);

	cout << endl;

	cout << "Hold? ('S' if served) > ";
}


void Generala::holdDice(vector<int> diceIndex)
{
	for (auto index : diceIndex)
	{
		if (index < 6)
		{
			dice[index-1].hold = true;
		}
	}
}


void Generala::selectScore(Scores::ScoreName score)
{
	if (current_shot)
	{
		cout << "Hold? ('S' if served) > ";
		string toHold;

		if (toHold == "S" || toHold == "s")
		{
			ChooseScore(state(), score);
		}
		else
		{
			istringstream ss(toHold);
			vector<string> tokens;
			copy(istream_iterator<string>(ss), istream_iterator<string>(), back_inserter(tokens));

			for (auto& token : tokens)
			{
				auto h = stoul(token);
				if (h < 6)
				{
					dice[h-1].hold = true;
				}
			}
		}
	}
	else
	{
		ChooseScore(state(), score);
	}

}


