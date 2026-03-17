/*
 * BattleEnded.h, part of VCMI engine
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

namespace events
{

class DLL_LINKAGE BattleEnded : public Event
{
public:
	using Sub = SubscriptionRegistry<BattleEnded>;
	using PreHandler = Sub::PreHandler;
	using PostHandler = Sub::PostHandler;
	using ExecHandler = Sub::ExecHandler;

	static Sub * getRegistry();
	static void defaultExecute(const EventBus * bus, const PlayerColor & victor,
		const PlayerColor & loser, const ObjectInstanceID & winnerHeroId,
		const ObjectInstanceID & loserHeroId, int64_t expAwarded);

	virtual PlayerColor getVictor() const = 0;
	virtual int32_t getVictorIndex() const = 0;
	virtual PlayerColor getLoser() const = 0;
	virtual int32_t getLoserIndex() const = 0;
	virtual ObjectInstanceID getWinnerHeroId() const = 0;
	virtual ObjectInstanceID getLoserHeroId() const = 0;
	virtual int64_t getExpAwarded() const = 0;

	friend class SubscriptionRegistry<BattleEnded>;
};

}

VCMI_LIB_NAMESPACE_END
