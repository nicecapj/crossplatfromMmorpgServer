#include "Creature.h"
#include<gtest\gtest.h>

Creature::Creature()
{
	int value = 3;
	EXPECT_TRUE(value > 3);
	EXPECT_FALSE(value > 3);

	EXPECT_EQ(value, 3);

	EXPECT_STREQ("ninja", "nanja");

}


Creature::~Creature()
{
}