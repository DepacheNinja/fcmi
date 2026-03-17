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

#include <vcmi/events/BattleEnded.h>

#include "../GameConstants.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

class DLL_LINKAGE CBattleEnded : public BattleEnded
{
public:
	CBattleEnded();

	bool isEnabled() const override;

	PlayerColor getVictor() const override;
	int32_t getVictorIndex() const override;
	PlayerColor getLoser() const override;
	int32_t getLoserIndex() const override;
	ObjectInstanceID getWinnerHeroId() const override;
	ObjectInstanceID getLoserHeroId() const override;
	int64_t getExpAwarded() const override;
	int32_t getBattleResult() const override;

	PlayerColor victor;
	PlayerColor loser;
	ObjectInstanceID winnerHeroId;
	ObjectInstanceID loserHeroId;
	int64_t expAwarded = 0;
	int32_t battleResultType = 0; // FCMI: 0=NORMAL, 1=ESCAPE, 2=SURRENDER
};

}

VCMI_LIB_NAMESPACE_END
