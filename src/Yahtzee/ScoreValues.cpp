#include "ScoreValues.h"

Scores::ScoreName DieValueToScore( unsigned short dieValue )
{
	return static_cast<Scores::ScoreName>(dieValue-1);
}
