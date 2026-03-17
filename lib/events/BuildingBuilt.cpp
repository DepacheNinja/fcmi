/*
 * BuildingBuilt.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "BuildingBuilt.h"

#include <vcmi/events/EventBus.h>

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

SubscriptionRegistry<BuildingBuilt> * BuildingBuilt::getRegistry()
{
	static auto Instance = std::make_unique<SubscriptionRegistry<BuildingBuilt>>();
	return Instance.get();
}

void BuildingBuilt::defaultExecute(const EventBus * bus,
	const PlayerColor & player, const ObjectInstanceID & townId, int32_t buildingId)
{
	CBuildingBuilt event;
	event.player = player;
	event.townId = townId;
	event.buildingId = buildingId;
	bus->executeEvent(event);
}

CBuildingBuilt::CBuildingBuilt() = default;

bool CBuildingBuilt::isEnabled() const
{
	return true;
}

PlayerColor CBuildingBuilt::getPlayer() const
{
	return player;
}

int32_t CBuildingBuilt::getPlayerIndex() const
{
	return player.getNum();
}

ObjectInstanceID CBuildingBuilt::getTown() const
{
	return townId;
}

int32_t CBuildingBuilt::getBuilding() const
{
	return buildingId;
}

}

VCMI_LIB_NAMESPACE_END
