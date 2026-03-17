/*
 * HeroHired.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "HeroHired.h"

#include <vcmi/events/EventBus.h>

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

SubscriptionRegistry<HeroHired> * HeroHired::getRegistry()
{
	static auto Instance = std::make_unique<SubscriptionRegistry<HeroHired>>();
	return Instance.get();
}

void HeroHired::defaultExecute(const EventBus * bus,
	const PlayerColor & player, const ObjectInstanceID & heroId)
{
	CHeroHired event;
	event.player = player;
	event.heroId = heroId;
	bus->executeEvent(event);
}

CHeroHired::CHeroHired() = default;

bool CHeroHired::isEnabled() const
{
	return true;
}

PlayerColor CHeroHired::getPlayer() const
{
	return player;
}

int32_t CHeroHired::getPlayerIndex() const
{
	return player.getNum();
}

ObjectInstanceID CHeroHired::getHero() const
{
	return heroId;
}

}

VCMI_LIB_NAMESPACE_END
