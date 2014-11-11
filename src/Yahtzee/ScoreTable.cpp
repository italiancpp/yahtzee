#include "ScoreTable.h"

#include <numeric>
#include <iostream>
#include <algorithm>

using namespace std;

ScoreTable::ScoreTable()
	: scores()
{
}

ScoreTable::ScoreTable(const ScoreTable& other)
	: scores(other.scores)
{
	
}

unsigned short ScoreTable::TotalScore() const
{
	unsigned short tot = 0;
	for (int i=0; i<scores.size(); ++i)
		tot += scores[i].value;
	return tot;
}

bool ScoreTable::HasScore(Scores::ScoreName scoreName) const 
{
	return scores.at(scoreName).value != 0;
}

void ScoreTable::AssignScoreIfNotAssigned(Scores::ScoreName scoreName, size_t score, bool markAsAssigned)
{
	Score& dieActualScore = scores.at(scoreName);
	if (dieActualScore.assigned && markAsAssigned)
		throw domain_error("ScoreTable: trying to assign an already assigned score");
	if (!dieActualScore.assigned)
	{
		dieActualScore.value = score;
		dieActualScore.assigned = markAsAssigned;
	}
}

bool ScoreTable::operator==( const ScoreTable& other ) const
{
	return scores == other.scores;
}

unsigned short ScoreTable::GetScoreAt( Scores::ScoreName scoreName ) const
{
	return scores[scoreName].value;
}

ostream& operator<<(ostream& stream, const ScoreTable& table)
{
	for (int i=0; i<table.scores.size(); ++i)
		stream << score_names[i] << " -> " << table.scores[i].value << (table.scores[i].assigned ? "" : " *") << std::endl;
	return stream;
}
