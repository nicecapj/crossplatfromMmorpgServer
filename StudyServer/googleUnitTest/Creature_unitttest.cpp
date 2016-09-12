#include "Creature.h"
#include <gtest\gtest.h>

void Creature::CheckValidate()
{
}

TEST(CreatureType, QuickTypeUser)
{
	Creature creature;
	int dex = creature.GetDex();

	EXPECT_GT(dex, 10);
}

TEST(CreatureType, StrongTypeUser)
{
	Creature creature;
	int dex = creature.GetStr();

	EXPECT_GT(dex, 40);
}