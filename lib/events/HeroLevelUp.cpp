/*
 * HeroLevelUp.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "HeroLevelUp.h"

#include <vcmi/events/EventBus.h>

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

SubscriptionRegistry<HeroLevelUp> * HeroLevelUp::getRegistry()
{
	static auto Instance = std::make_unique<SubscriptionRegistry<HeroLevelUp>>();
	return Instance.get();
}

void HeroLevelUp::defaultExecute(const EventBus * bus, const PlayerColor & player,
	const ObjectInstanceID & heroId, int level, int primarySkillGained)
{
	CHeroLevelUp event;
	event.player = player;
	event.heroId = heroId;
	event.newLevel = level;
	event.primarySkillGained = primarySkillGained;
	bus->executeEvent(event);
}

CHeroLevelUp::CHeroLevelUp() = default;

bool CHeroLevelUp::isEnabled() const
{
	return true;
}

PlayerColor CHeroLevelUp::getPlayer() const
{
	return player;
}

int32_t CHeroLevelUp::getPlayerIndex() const
{
	return player.getNum();
}

ObjectInstanceID CHeroLevelUp::getHero() const
{
	return heroId;
}

int CHeroLevelUp::getLevel() const
{
	return newLevel;
}

int CHeroLevelUp::getPrimarySkillGained() const
{
	return primarySkillGained;
}

}

VCMI_LIB_NAMESPACE_END
