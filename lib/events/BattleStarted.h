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

#include <vcmi/events/BattleStarted.h>

#include "../GameConstants.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

class DLL_LINKAGE CBattleStarted : public BattleStarted
{
public:
	CBattleStarted();

	bool isEnabled() const override;
	int32_t getAttackerPlayer() const override;
	int32_t getAttackerHeroId() const override;
	int32_t getDefenderPlayer() const override;
	int32_t getDefenderHeroId() const override;

	PlayerColor attackerPlayer;
	PlayerColor defenderPlayer;
	ObjectInstanceID attackerHeroId;
	ObjectInstanceID defenderHeroId;
};

}

VCMI_LIB_NAMESPACE_END
