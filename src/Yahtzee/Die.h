#pragma once

struct Die
{
	Die(unsigned short pValue, bool pHold = false);

	unsigned short value;
	bool hold;
};

bool operator==(const Die& first, const Die& second);