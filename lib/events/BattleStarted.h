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
	int32_t getAttackerArmyId() const override;  // FCMI: army object ID (neutral creature objectId or heroId)
	int32_t getDefenderPlayer() const override;
	int32_t getDefenderHeroId() const override;
	int32_t getDefenderArmyId() const override;  // FCMI: army object ID (neutral creature objectId or heroId)
	int32_t getBattleId() const override;         // FCMI: BattleID for SetStackEffect use

	PlayerColor attackerPlayer;
	PlayerColor defenderPlayer;
	ObjectInstanceID attackerHeroId;
	ObjectInstanceID defenderHeroId;
	ObjectInstanceID attackerArmyId;  // FCMI: army object (hero or map neutral creature)
	ObjectInstanceID defenderArmyId;  // FCMI: army object (hero or map neutral creature)
	BattleID battleId;                // FCMI: battle ID
};

}

VCMI_LIB_NAMESPACE_END
