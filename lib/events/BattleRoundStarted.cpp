/*
 * BattleRoundStarted.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "BattleRoundStarted.h"

#include <vcmi/events/EventBus.h>

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

SubscriptionRegistry<BattleRoundStarted> * BattleRoundStarted::getRegistry()
{
	static auto Instance = std::make_unique<SubscriptionRegistry<BattleRoundStarted>>();
	return Instance.get();
}

void BattleRoundStarted::defaultExecute(const EventBus * bus,
	const BattleID & battleId, int32_t round)
{
	CBattleRoundStarted event;
	event.battleId = battleId;
	event.round = round;
	bus->executeEvent(event);
}

CBattleRoundStarted::CBattleRoundStarted() = default;

bool CBattleRoundStarted::isEnabled() const
{
	return true;
}

int32_t CBattleRoundStarted::getBattleId() const
{
	return battleId.getNum();
}

int32_t CBattleRoundStarted::getRound() const
{
	return round;
}

}

VCMI_LIB_NAMESPACE_END
