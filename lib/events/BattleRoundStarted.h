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

#include <vcmi/events/BattleRoundStarted.h>

#include "../GameConstants.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

class DLL_LINKAGE CBattleRoundStarted : public BattleRoundStarted
{
public:
	CBattleRoundStarted();

	bool isEnabled() const override;
	int32_t getBattleId() const override;
	int32_t getRound() const override;

	BattleID battleId;
	int32_t round;
};

}

VCMI_LIB_NAMESPACE_END
