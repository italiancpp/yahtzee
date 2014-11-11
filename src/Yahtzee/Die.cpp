#include "Die.h"

Die::Die( unsigned short pValue, bool pHold /*= false*/ ) : value(pValue), hold(pHold)
{

}
bool operator==( const Die& first, const Die& second )
{
	return	first.value == second.value &&
			first.hold == second.hold;
}


