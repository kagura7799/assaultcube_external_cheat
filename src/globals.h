#pragma once

#include "memory.h"
#include <map>

namespace Globals
{
	extern Memory mem;

	extern std::map<std::string, bool> cheatStatus;

	extern bool godMode;
	extern bool noRecoil;
};