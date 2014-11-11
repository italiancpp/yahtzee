#pragma once

#include <map>
#include <string>
#include <array>
#include "ScoreValues.h"

struct Score
{
	Score()
		: assigned(false), value(0u)
	{

	}
	
	bool assigned;
	unsigned short value;

	bool operator == (const Score & other) const
	{
		return assigned == other.assigned &&
			value == other.value;
	}
};

class ScoreTable
{
public:
	ScoreTable();
	~ScoreTable() {}
	ScoreTable(const ScoreTable& other);

	void AssignScoreIfNotAssigned(Scores::ScoreName scoreName, size_t score, bool markAsAssigned = false);
	bool HasScore(Scores::ScoreName scoreName) const;
	unsigned short GetScoreAt(Scores::ScoreName scoreName) const;
	unsigned short TotalScore() const;

	bool operator==(const ScoreTable& other) const;
	friend std::ostream& operator<<(std::ostream& stream, const ScoreTable& table);
private:
	std::array<Score, Scores::scores_count> scores;
};

std::ostream& operator<<(std::ostream& stream, const ScoreTable& table);