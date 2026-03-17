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

#include <vcmi/events/HeroLevelUp.h>

#include "../GameConstants.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

class DLL_LINKAGE CHeroLevelUp : public HeroLevelUp
{
public:
	CHeroLevelUp();

	bool isEnabled() const override;

	PlayerColor getPlayer() const override;
	int32_t getPlayerIndex() const override;
	ObjectInstanceID getHero() const override;
	int getLevel() const override;
	int getPrimarySkillGained() const override;

	PlayerColor player;
	ObjectInstanceID heroId;
	int newLevel = 0;
	int primarySkillGained = 0; // 0=attack,1=defense,2=spellpower,3=knowledge
};

}

VCMI_LIB_NAMESPACE_END
