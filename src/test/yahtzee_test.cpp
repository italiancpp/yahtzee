#include "yahtzee_test.h"
#include "../Yahtzee/GameConfiguration.h"
#include "../Yahtzee/Yahtzee.h"

using namespace std;

static const GameConfiguration DEFAULT_GAME_CONFIG = CreateDefaultGameConfiguration();

vector<DicePlayer> CreateOnePlayerAsMarco()
{
	return vector<DicePlayer>(1, DicePlayer("Marco", GameConfiguration::DEFAULT_DICE_ROLLER));
}

vector<DicePlayer> YahtzeeTest::CreateOnePlayerAsMarcoWithMockedRoller()
{
	return vector<DicePlayer>(1, DicePlayer("Marco", mockedRoller));
}

// Tests

TEST_F(YahtzeeTest, on_creation_should_do_nothing)
{
	Yahtzee game(CreateOnePlayerAsMarco(), DEFAULT_GAME_CONFIG, writer);

	ASSERT_EQ( writer.called_newGameCreated, 0 );
}

TEST_F(YahtzeeTest, on_new_game_should_notify_writer)
{
	Yahtzee game(CreateOnePlayerAsMarco(), DEFAULT_GAME_CONFIG, writer);
	game.newGame();

	ASSERT_EQ( writer.called_newGameCreated, 1 );
	ASSERT_EQ( writer.newGameCreated_players.size(), 1 );
}

TEST_F(YahtzeeTest, on_start_turn_should_notify_writer_with_first_player)
{
	Yahtzee game(CreateOnePlayerAsMarco(), DEFAULT_GAME_CONFIG, writer);
	game.newGame();

	ASSERT_EQ( writer.called_startTurnFor, 1 );
	ASSERT_EQ( writer.startTurnFor_currentTurn , 1u );
	ASSERT_STRCASEEQ( writer.startTurnFor_playerName.c_str(), "Marco" );
}

TEST_F(YahtzeeTest, on_roll_dice_should_notify_writer_and_calculate_score)
{
	Yahtzee game(CreateOnePlayerAsMarcoWithMockedRoller(), DEFAULT_GAME_CONFIG, writer);

	int mockedDiceValueArr[5] = {1,1,2,3,4};
	mockedRoller.AssignDiceValues(mockedDiceValueArr);
	vector<Die> mockedDiceValue(mockedDiceValueArr, mockedDiceValueArr + 5);

	ScoreTable expectedScores;
	expectedScores.AssignScoreIfNotAssigned(Scores::one, 2, false);
	expectedScores.AssignScoreIfNotAssigned(Scores::two, 2, false);
	expectedScores.AssignScoreIfNotAssigned(Scores::three, 3, false);
	expectedScores.AssignScoreIfNotAssigned(Scores::four, 4, false);
	
	game.newGame();
	game.rollDice();

	ASSERT_EQ( writer.called_diceRolled, 1 );
	ASSERT_EQ( writer.diceRolled_currentShot , 1u );
	ASSERT_EQ( writer.diceRolled_diceValue , mockedDiceValue );
	ASSERT_EQ( writer.diceRolled_remaningShots, 2);
	ASSERT_EQ( writer.called_scoreCalculated, 1);
	ASSERT_EQ( writer.scoreCalculated_scores, expectedScores );
}

TEST_F(YahtzeeTest, on_roll_dice_three_times_should_remain_no_shots)
{
	int mockedDiceValueArr[5] = {1,1,2,3,4};
	mockedRoller.AssignDiceValues(mockedDiceValueArr);
	Yahtzee game(CreateOnePlayerAsMarcoWithMockedRoller(), DEFAULT_GAME_CONFIG, writer);
	
	game.newGame();
	game.rollDice();
	game.rollDice();
	game.rollDice();

	// e se tiriamo più di tre volte???

	ASSERT_EQ( writer.called_diceRolled, 3 );
	ASSERT_EQ( writer.diceRolled_currentShot , 3u );
	ASSERT_EQ( writer.diceRolled_remaningShots, 0u);
	ASSERT_EQ( writer.called_scoreCalculated, 3);
}

TEST_F(YahtzeeTest, on_select_score_should_assign_scores_to_current_player)
{
	int mockedDiceValueArr[5] = {1,1,1,1,1};
	mockedRoller.AssignDiceValues(mockedDiceValueArr);
	Yahtzee game(CreateOnePlayerAsMarcoWithMockedRoller(), DEFAULT_GAME_CONFIG, writer);

	ScoreTable expectedScores;
	expectedScores.AssignScoreIfNotAssigned(Scores::yahtzee, 55, true);
	
	game.newGame();
	game.rollDice();
	game.selectScore(Scores::yahtzee);

	ASSERT_EQ(writer.endTurnFor_currentScores, expectedScores);
}

TEST_F(YahtzeeTest, on_select_score_should_end_turn_for_current_player)
{
	int mockedDiceValueArr[5] = {1,1,1,1,1};
	mockedRoller.AssignDiceValues(mockedDiceValueArr);
	Yahtzee game(CreateOnePlayerAsMarcoWithMockedRoller(), DEFAULT_GAME_CONFIG, writer);
	
	game.newGame();
	game.rollDice();
	game.selectScore(Scores::yahtzee);

	ASSERT_EQ( writer.called_endTurnFor, 1 );
	ASSERT_STRCASEEQ( writer.endTurnFor_playerName.c_str(), "Marco" );
}

TEST_F(YahtzeeTest, on_select_score_should_start_turn_for_other_player)
{
	int mockedDiceValueArr[5] = {1,1,1,1,1};
	mockedRoller.AssignDiceValues(mockedDiceValueArr);	
	DicePlayer player1("Marco", mockedRoller);
	DicePlayer player2("Gianluca", mockedRoller);
	vector<DicePlayer> players; 
	players.push_back(player1); 
	players.push_back(player2); 
	Yahtzee game(players, DEFAULT_GAME_CONFIG, writer);
	
	game.newGame();
	game.rollDice();
	game.selectScore(Scores::yahtzee);

	ASSERT_EQ( writer.called_startTurnFor, 2 );
	ASSERT_EQ( writer.startTurnFor_playerName, "Gianluca" );
	ASSERT_EQ( writer.startTurnFor_currentTurn, 1u );
}

TEST_F(YahtzeeTest, on_select_score_with_only_one_turn_should_call_game_over)
{
	GameConfiguration oneTurnConfig(5, 6, 1);
	Yahtzee game(CreateOnePlayerAsMarco(), oneTurnConfig, writer);
	
	game.newGame();
	game.rollDice();
	game.selectScore(Scores::yahtzee);

	ASSERT_EQ( writer.called_gameOver, 1 );
}

TEST_F(YahtzeeTest, on_select_score_on_already_assign_score_should_fail)
{
	Yahtzee game(CreateOnePlayerAsMarco(), DEFAULT_GAME_CONFIG, writer);

	game.newGame();
	game.rollDice();
	game.selectScore(Scores::yahtzee);
	game.rollDice();
	
	ASSERT_THROW( game.selectScore(Scores::yahtzee), domain_error );
}

// full-game test

TEST_F(YahtzeeTest, on_full_game_two_players_two_turns)
{
	DicePlayer player1("Marco", mockedRoller);
	DicePlayer player2("Gianluca", mockedRoller);
	vector<DicePlayer> players; 
	players.push_back(player1); 
	players.push_back(player2); 
	GameConfiguration oneTurnConfig(5, 6, 2);
	Yahtzee game(players, oneTurnConfig, writer);

	game.newGame();

	// ---- first turn
    
	// first player shot
	{
		int mockedDiceValueArr[5] = {1,2,3,1,1};
		mockedRoller.AssignDiceValues(mockedDiceValueArr);	
	}
	game.rollDice();
	game.selectScore(Scores::one);

	// second player shot
	{
		int mockedDiceValueArr[5] = {2,2,3,4,5};
		mockedRoller.AssignDiceValues(mockedDiceValueArr);	
	}
	game.rollDice();
	game.selectScore(Scores::two);

	// ---- second turn

	// first player shot
	{
		int mockedDiceValueArr[5] = {1,2,3,4,5};
		mockedRoller.AssignDiceValues(mockedDiceValueArr);	
	}
	game.rollDice();
	game.rollDice(); 
	game.selectScore(Scores::straight); // not at first shot

	// second player shot
	{
		int mockedDiceValueArr[5] = {3,3,3,3,2};
		mockedRoller.AssignDiceValues(mockedDiceValueArr);	
	}
	game.rollDice();
	game.rollDice(); 
	game.selectScore(Scores::poker);

	ASSERT_EQ( writer.called_gameOver, 1 );

	std::vector<std::pair<const DicePlayer*, const ScoreTable*>> rank = game.getRank();

	ASSERT_EQ( rank[0].first->Name(), "Gianluca" );
	ASSERT_EQ( rank[0].second->TotalScore(), 44 );
	ASSERT_EQ( rank[1].first->Name(), "Marco" );
	ASSERT_EQ( rank[1].second->TotalScore(), 23 );
}