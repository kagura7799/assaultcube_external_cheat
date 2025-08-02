#include "globals.h"

namespace Globals
{
	Memory mem;

	std::map<std::string, bool> cheatStatus
	{
		{"godMode", false},
		{"noRecoil", false},
	};

	bool godMode = false;
	bool noRecoil = false;
};