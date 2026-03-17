/*
 * BattleEnded.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "BattleEnded.h"

#include <vcmi/events/EventBus.h>

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

SubscriptionRegistry<BattleEnded> * BattleEnded::getRegistry()
{
	static auto Instance = std::make_unique<SubscriptionRegistry<BattleEnded>>();
	return Instance.get();
}

void BattleEnded::defaultExecute(const EventBus * bus, const PlayerColor & victor,
	const PlayerColor & loser, const ObjectInstanceID & winnerHeroId,
	const ObjectInstanceID & loserHeroId, int64_t expAwarded)
{
	CBattleEnded event;
	event.victor = victor;
	event.loser = loser;
	event.winnerHeroId = winnerHeroId;
	event.loserHeroId = loserHeroId;
	event.expAwarded = expAwarded;
	bus->executeEvent(event);
}

CBattleEnded::CBattleEnded() = default;

bool CBattleEnded::isEnabled() const
{
	return true;
}

PlayerColor CBattleEnded::getVictor() const
{
	return victor;
}

int32_t CBattleEnded::getVictorIndex() const
{
	return victor.getNum();
}

PlayerColor CBattleEnded::getLoser() const
{
	return loser;
}

int32_t CBattleEnded::getLoserIndex() const
{
	return loser.getNum();
}

ObjectInstanceID CBattleEnded::getWinnerHeroId() const
{
	return winnerHeroId;
}

ObjectInstanceID CBattleEnded::getLoserHeroId() const
{
	return loserHeroId;
}

int64_t CBattleEnded::getExpAwarded() const
{
	return expAwarded;
}

}

VCMI_LIB_NAMESPACE_END
