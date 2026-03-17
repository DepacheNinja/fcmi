/*
 * HeroHired.h, part of VCMI engine
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

/// Fires after a hero is hired from a town tavern or standalone Tavern object.
class DLL_LINKAGE HeroHired : public Event
{
public:
	using Sub = SubscriptionRegistry<HeroHired>;
	using PreHandler = Sub::PreHandler;
	using PostHandler = Sub::PostHandler;
	using ExecHandler = Sub::ExecHandler;

	static Sub * getRegistry();
	static void defaultExecute(const EventBus * bus,
		const PlayerColor & player, const ObjectInstanceID & heroId);

	virtual PlayerColor getPlayer() const = 0;
	virtual int32_t getPlayerIndex() const = 0;
	virtual ObjectInstanceID getHero() const = 0;

	friend class SubscriptionRegistry<HeroHired>;
};

}

VCMI_LIB_NAMESPACE_END
