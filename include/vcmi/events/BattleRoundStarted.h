/*
 * BattleRoundStarted.h, part of VCMI engine
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

class BattleID;

namespace events
{

// FCMI: BattleRoundStarted event — fires at the start of each combat round.
// Exposes the BattleID and current round number (1-indexed).
class DLL_LINKAGE BattleRoundStarted : public Event
{
public:
	using Sub = SubscriptionRegistry<BattleRoundStarted>;
	using PreHandler = Sub::PreHandler;
	using PostHandler = Sub::PostHandler;
	using ExecHandler = Sub::ExecHandler;

	static Sub * getRegistry();
	static void defaultExecute(const EventBus * bus,
		const BattleID & battleId, int32_t round);

	virtual int32_t getBattleId() const = 0;
	virtual int32_t getRound() const = 0;

	friend class SubscriptionRegistry<BattleRoundStarted>;
};

}

VCMI_LIB_NAMESPACE_END
