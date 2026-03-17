/*
 * ApplyDamage.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include <vcmi/events/ApplyDamage.h>

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

class DLL_LINKAGE CApplyDamage : public ApplyDamage
{
public:
	CApplyDamage(BattleStackAttacked * pack_, bool luckyHit_, bool rangedAttack_, bool ballistaDmg_, std::shared_ptr<battle::Unit> target_);

	bool isEnabled() const override;
	int64_t getInitialDamage() const override;
	int64_t getDamage() const override;
	void setDamage(int64_t value) override;
	const battle::Unit * getTarget() const override;
	bool isLucky() const override;
	bool isRanged() const override;
	bool isBallistaDmg() const override;
private:
	int64_t initialDamage;

	BattleStackAttacked * pack;
	bool luckyHit;
	bool rangedAttack;
	bool ballistaDmg;
	std::shared_ptr<battle::Unit> target;
};

}

VCMI_LIB_NAMESPACE_END
