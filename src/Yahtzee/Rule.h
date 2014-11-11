#pragma once

#include <functional>
#include "Histogram.h"
#include "GameState.h"

typedef std::function<void(const Histogram&, GameState&)> Rule;