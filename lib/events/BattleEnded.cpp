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
	defaultExecute(bus, victor, loser, winnerHeroId, loserHeroId, expAwarded, 0);
}

// FCMI: overload that also carries the battle result type (0=NORMAL, 1=ESCAPE, 2=SURRENDER)
void BattleEnded::defaultExecute(const EventBus * bus, const PlayerColor & victor,
	const PlayerColor & loser, const ObjectInstanceID & winnerHeroId,
	const ObjectInstanceID & loserHeroId, int64_t expAwarded, int32_t battleResultType)
{
	CBattleEnded event;
	event.victor = victor;
	event.loser = loser;
	event.winnerHeroId = winnerHeroId;
	event.loserHeroId = loserHeroId;
	event.expAwarded = expAwarded;
	event.battleResultType = battleResultType;
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

int32_t CBattleEnded::getBattleResult() const
{
	return battleResultType;
}

}

VCMI_LIB_NAMESPACE_END
