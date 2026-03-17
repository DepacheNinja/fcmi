/*
 * BattleStarted.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "BattleStarted.h"

#include <vcmi/events/EventBus.h>

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

SubscriptionRegistry<BattleStarted> * BattleStarted::getRegistry()
{
	static auto Instance = std::make_unique<SubscriptionRegistry<BattleStarted>>();
	return Instance.get();
}

void BattleStarted::defaultExecute(const EventBus * bus,
	const PlayerColor & attacker, const PlayerColor & defender,
	const ObjectInstanceID & attackerHeroId, const ObjectInstanceID & defenderHeroId)
{
	// Backward-compat overload: army IDs same as hero IDs
	defaultExecute(bus, attacker, defender, attackerHeroId, defenderHeroId,
		attackerHeroId, defenderHeroId);
}

void BattleStarted::defaultExecute(const EventBus * bus,
	const PlayerColor & attacker, const PlayerColor & defender,
	const ObjectInstanceID & attackerHeroId, const ObjectInstanceID & defenderHeroId,
	const ObjectInstanceID & attackerArmyId, const ObjectInstanceID & defenderArmyId)
{
	defaultExecute(bus, attacker, defender, attackerHeroId, defenderHeroId,
		attackerArmyId, defenderArmyId, BattleID::NONE);
}

void BattleStarted::defaultExecute(const EventBus * bus,
	const PlayerColor & attacker, const PlayerColor & defender,
	const ObjectInstanceID & attackerHeroId, const ObjectInstanceID & defenderHeroId,
	const ObjectInstanceID & attackerArmyId, const ObjectInstanceID & defenderArmyId,
	const BattleID & battleId)
{
	CBattleStarted event;
	event.attackerPlayer = attacker;
	event.defenderPlayer = defender;
	event.attackerHeroId = attackerHeroId;
	event.defenderHeroId = defenderHeroId;
	event.attackerArmyId = attackerArmyId;
	event.defenderArmyId = defenderArmyId;
	event.battleId = battleId;
	bus->executeEvent(event);
}

CBattleStarted::CBattleStarted() = default;

bool CBattleStarted::isEnabled() const
{
	return true;
}

int32_t CBattleStarted::getAttackerPlayer() const
{
	return attackerPlayer.getNum();
}

int32_t CBattleStarted::getAttackerHeroId() const
{
	return attackerHeroId.getNum();
}

int32_t CBattleStarted::getDefenderPlayer() const
{
	return defenderPlayer.getNum();
}

int32_t CBattleStarted::getDefenderHeroId() const
{
	return defenderHeroId.getNum();
}

int32_t CBattleStarted::getAttackerArmyId() const
{
	return attackerArmyId.getNum();
}

int32_t CBattleStarted::getDefenderArmyId() const
{
	return defenderArmyId.getNum();
}

int32_t CBattleStarted::getBattleId() const
{
	return battleId.getNum();
}

}

VCMI_LIB_NAMESPACE_END
