#ifdef CHECK_LEAKS
// #include "../utils/debug-new/DebugNew.h"
#endif
#include "ScoreCalculator.h"

using namespace std;

ScoreCalculator::ScoreCalculator( unsigned short _maxDiceValue ) 
	: maxDiceValue(_maxDiceValue)
{}

ScoreCalculator::~ScoreCalculator()
{}

unsigned short* CalculateRanks(const vector<Die>& dice, unsigned short maxDiceValue)
{
	unsigned short* ranks = new unsigned short[maxDiceValue]();
	for (size_t i = 0u; i<dice.size(); ++i)
	{
		ranks[dice[i].value - 1] += 1;
	}
	return ranks;
}

void CalculateHistogram(unsigned short* ranks, int size, Histogram& histogram)
{
	for (int i = 0; i<size; ++i)
	{
		if (ranks[i]>0)
			histogram[ranks[i]].push_front(i+1);
	}
}

inline bool histogram_has(const Histogram& histogram, unsigned short val)
{
	return histogram.find(val) != end(histogram);
}

inline unsigned short Score(unsigned short score, bool isFirstShot, unsigned short extraIfFirstRoll = 5)
{
	return isFirstShot ? score + extraIfFirstRoll : score;
}

void ScoreCalculator::CheckScore(const std::vector<Die>& dice, bool isFirstShort, ScoreTable& currentTable) const
{
	unsigned short* ranks = CalculateRanks(dice, maxDiceValue);
	Histogram histogram;
	CalculateHistogram(ranks, maxDiceValue, histogram);

	if (histogram_has(histogram, 1))
	{
		for (auto single : histogram.find(1)->second)
		{
			currentTable.AssignScoreIfNotAssigned(DieValueToScore(single), single);
		}
	}

	if (histogram_has(histogram, 2))
	{
		auto pair = histogram.find(2)->second.front();
		currentTable.AssignScoreIfNotAssigned(DieValueToScore(pair), 2 * pair);
	}

	if (histogram_has(histogram, 3))
	{
		auto trisValue = histogram.find(3)->second.front();
		currentTable.AssignScoreIfNotAssigned(DieValueToScore(trisValue), 3 * trisValue);
	}

	if (histogram_has(histogram, 2) && histogram_has(histogram, 3))
	{
		currentTable.AssignScoreIfNotAssigned(Scores::full, Score(30, isFirstShort));
	}

	if (histogram_has(histogram, 4))
	{
		currentTable.AssignScoreIfNotAssigned(Scores::poker, Score(40, isFirstShort));
		auto pokerValue = histogram.find(4)->second.front();
		currentTable.AssignScoreIfNotAssigned(DieValueToScore(pokerValue), 4 * pokerValue);
	}

	if ((histogram.size() == 1) && histogram_has(histogram, 1))
	{
		currentTable.AssignScoreIfNotAssigned(Scores::straight, Score(20, isFirstShort));
	}

	if (histogram_has(histogram, 5))
	{
		currentTable.AssignScoreIfNotAssigned(Scores::yahtzee, Score(50, isFirstShort));
		auto yahtzeeValue = histogram.find(5)->second.front();
		currentTable.AssignScoreIfNotAssigned(DieValueToScore(yahtzeeValue), 5 * yahtzeeValue);
	}
}