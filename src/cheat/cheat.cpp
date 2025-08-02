#include "cheat.h"

bool godModeIsWorking = false;

void handler()
{
	if (Globals::cheatStatus.at("godMode"))
	{
		godMode(414, 414);
		godModeIsWorking = true;
	}
	else
	{
		if (godModeIsWorking)
			godMode(100, 30);

		godModeIsWorking = false;
	}
}

void godMode(int armorHp, int ammo)
{
	Globals::mem.Write<int>(entityOffsets.at("miscellaneous").at("hp"), armorHp);
	Globals::mem.Write<int>(entityOffsets.at("miscellaneous").at("armor"), armorHp);

	for (const auto& weaponOffset : entityOffsets.at("weapon"))
		Globals::mem.Write<int>(weaponOffset.second, ammo);
}	