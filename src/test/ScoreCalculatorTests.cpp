#include "gtest/gtest.h"
#include "../Yahtzee/ScoreCalculator.h"
#include <vector>

using namespace std;

class ScoreCalculatorTests : public testing::Test
{
public:
	ScoreCalculatorTests()
		: calculator(6), dice(5, Die(1))
	{

	}

protected:
	void CheckScoreOnFirstShot(const ScoreTable& expected);
	void CheckScoreOnShotDifferentFromFirst(const ScoreTable& expectedTable);
	
	ScoreCalculator calculator;
	vector<Die> dice;
};

void ScoreCalculatorTests::CheckScoreOnFirstShot(const ScoreTable& expectedTable)
{
	ScoreTable actualTable;
	calculator.CheckScore(dice, true, actualTable);
	ASSERT_EQ(actualTable, expectedTable);
}

void ScoreCalculatorTests::CheckScoreOnShotDifferentFromFirst(const ScoreTable& expectedTable)
{
	ScoreTable actualTable;
	calculator.CheckScore(dice, false, actualTable);
	ASSERT_EQ(actualTable, expectedTable);
}

TEST_F(ScoreCalculatorTests, on_pair)
{
	int diceArr[] = {1,1,3,4,5};
	dice.assign(diceArr, diceArr+5);
	
	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 2);
	expectedTable.AssignScoreIfNotAssigned(Scores::three, 3);
	expectedTable.AssignScoreIfNotAssigned(Scores::four, 4);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);

	CheckScoreOnFirstShot(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_tris)
{
	int diceArr[] = {1,1,1,4,5};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 3);
	expectedTable.AssignScoreIfNotAssigned(Scores::four, 4);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);

	CheckScoreOnFirstShot(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_double_pair)
{
	int diceArr[] = {1,1,3,3,5};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 2);
	expectedTable.AssignScoreIfNotAssigned(Scores::three, 6);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);

	CheckScoreOnFirstShot(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_straight)
{
	int diceArr[] = {1,2,3,4,5};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 1);
	expectedTable.AssignScoreIfNotAssigned(Scores::two, 2);
	expectedTable.AssignScoreIfNotAssigned(Scores::three, 3);
	expectedTable.AssignScoreIfNotAssigned(Scores::four, 4);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);
	expectedTable.AssignScoreIfNotAssigned(Scores::straight, 25);

	CheckScoreOnFirstShot(expectedTable);

	expectedTable.AssignScoreIfNotAssigned(Scores::straight, 20);
	CheckScoreOnShotDifferentFromFirst(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_full)
{
	int diceArr[] = {1,1,3,3,3};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 2);
	expectedTable.AssignScoreIfNotAssigned(Scores::three, 9);
	expectedTable.AssignScoreIfNotAssigned(Scores::full, 35);

	CheckScoreOnFirstShot(expectedTable);

	expectedTable.AssignScoreIfNotAssigned(Scores::full, 30);
	CheckScoreOnShotDifferentFromFirst(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_poker)
{
	int diceArr[] = {1,1,1,1,5};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 4);
	expectedTable.AssignScoreIfNotAssigned(Scores::five, 5);
	expectedTable.AssignScoreIfNotAssigned(Scores::poker, 45);

	CheckScoreOnFirstShot(expectedTable);

	expectedTable.AssignScoreIfNotAssigned(Scores::poker, 40);
	CheckScoreOnShotDifferentFromFirst(expectedTable);
}

TEST_F(ScoreCalculatorTests, on_yahtzee)
{
	int diceArr[] = {1,1,1,1,1};
	dice.assign(diceArr, diceArr+5);

	ScoreTable expectedTable;
	expectedTable.AssignScoreIfNotAssigned(Scores::one, 5);
	expectedTable.AssignScoreIfNotAssigned(Scores::yahtzee, 55);

	CheckScoreOnFirstShot(expectedTable);

	expectedTable.AssignScoreIfNotAssigned(Scores::yahtzee, 50);
	CheckScoreOnShotDifferentFromFirst(expectedTable);
}