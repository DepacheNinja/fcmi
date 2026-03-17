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

#include <vcmi/events/HeroHired.h>

#include "../GameConstants.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

class DLL_LINKAGE CHeroHired : public HeroHired
{
public:
	CHeroHired();

	bool isEnabled() const override;

	PlayerColor getPlayer() const override;
	int32_t getPlayerIndex() const override;
	ObjectInstanceID getHero() const override;

	PlayerColor player;
	ObjectInstanceID heroId;
};

}

VCMI_LIB_NAMESPACE_END
