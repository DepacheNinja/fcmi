/*
 * HeroLevelUp.h, part of VCMI engine
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

class DLL_LINKAGE HeroLevelUp : public Event
{
public:
	using Sub = SubscriptionRegistry<HeroLevelUp>;
	using PreHandler = Sub::PreHandler;
	using PostHandler = Sub::PostHandler;
	using ExecHandler = Sub::ExecHandler;

	static Sub * getRegistry();
	static void defaultExecute(const EventBus * bus, const PlayerColor & player,
		const ObjectInstanceID & heroId, int level, int primarySkillGained);

	virtual PlayerColor getPlayer() const = 0;
	virtual int32_t getPlayerIndex() const = 0;
	virtual ObjectInstanceID getHero() const = 0;
	virtual int getLevel() const = 0;
	virtual int getPrimarySkillGained() const = 0;

	friend class SubscriptionRegistry<HeroLevelUp>;
};

}

VCMI_LIB_NAMESPACE_END
