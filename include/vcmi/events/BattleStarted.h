/*
 * BattleStarted.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "Event.h"
#include "SubscriptionRegistry.h"

VCMI_LIB_NAMESPACE_BEGIN

class PlayerColor;
class ObjectInstanceID;
class BattleID;

namespace events
{

// FCMI: BattleStarted event — fires when a new battle begins, after stacks are placed.
// Exposes both sides' player colors and hero IDs (NONE if side has no hero).
class DLL_LINKAGE BattleStarted : public Event
{
public:
	using Sub = SubscriptionRegistry<BattleStarted>;
	using PreHandler = Sub::PreHandler;
	using PostHandler = Sub::PostHandler;
	using ExecHandler = Sub::ExecHandler;

	static Sub * getRegistry();
	static void defaultExecute(const EventBus * bus,
		const PlayerColor & attacker, const PlayerColor & defender,
		const ObjectInstanceID & attackerHeroId, const ObjectInstanceID & defenderHeroId);
	// FCMI: extended overload that also carries army object IDs for neutral-creature battles
	static void defaultExecute(const EventBus * bus,
		const PlayerColor & attacker, const PlayerColor & defender,
		const ObjectInstanceID & attackerHeroId, const ObjectInstanceID & defenderHeroId,
		const ObjectInstanceID & attackerArmyId, const ObjectInstanceID & defenderArmyId);
	// FCMI: full overload carrying army IDs + battle ID for SetStackEffect use
	static void defaultExecute(const EventBus * bus,
		const PlayerColor & attacker, const PlayerColor & defender,
		const ObjectInstanceID & attackerHeroId, const ObjectInstanceID & defenderHeroId,
		const ObjectInstanceID & attackerArmyId, const ObjectInstanceID & defenderArmyId,
		const BattleID & battleId);

	// Attacker side (army1 / BattleSide::ATTACKER)
	virtual int32_t getAttackerPlayer() const = 0;
	virtual int32_t getAttackerHeroId() const = 0;
	// FCMI: army object ID for attacker (same as heroId if hero present; else map object ID of neutral creature)
	virtual int32_t getAttackerArmyId() const = 0;
	// Defender side (army2 / BattleSide::DEFENDER)
	virtual int32_t getDefenderPlayer() const = 0;
	virtual int32_t getDefenderHeroId() const = 0;
	// FCMI: army object ID for defender (same as heroId if hero present; else map object ID of neutral creature)
	virtual int32_t getDefenderArmyId() const = 0;
	// FCMI: the BattleID for this battle (needed for SetStackEffect netpack)
	virtual int32_t getBattleId() const = 0;

	friend class SubscriptionRegistry<BattleStarted>;
};

}

VCMI_LIB_NAMESPACE_END
