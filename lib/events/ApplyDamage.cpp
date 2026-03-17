/*
 * ApplyDamage.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include <vcmi/events/EventBus.h>

#include "ApplyDamage.h"
#include "../networkPacks/PacksForClientBattle.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

SubscriptionRegistry<ApplyDamage> * ApplyDamage::getRegistry()
{
	static auto Instance = std::make_unique<SubscriptionRegistry<ApplyDamage>>();
	return Instance.get();
}

void ApplyDamage::defaultExecute(const EventBus * bus, BattleStackAttacked & bsa,
	bool luckyHit, bool rangedAttack, std::shared_ptr<battle::Unit> target)
{
	CApplyDamage event(&bsa, luckyHit, rangedAttack, std::move(target));
	bus->executeEvent(event);
}

CApplyDamage::CApplyDamage(BattleStackAttacked * pack_, bool luckyHit_, bool rangedAttack_, std::shared_ptr<battle::Unit> target_)
	: pack(pack_),
	luckyHit(luckyHit_),
	rangedAttack(rangedAttack_),
	target(std::move(target_))
{
	initialDamage = pack->damageAmount;
}

bool CApplyDamage::isEnabled() const
{
	return true;
}

int64_t CApplyDamage::getInitialDamage() const
{
	return initialDamage;
}

int64_t CApplyDamage::getDamage() const
{
	return pack->damageAmount;
}

void CApplyDamage::setDamage(int64_t value)
{
	pack->damageAmount = value;
}

const battle::Unit * CApplyDamage::getTarget() const
{
	return target.get();
}

bool CApplyDamage::isLucky() const
{
	return luckyHit;
}

bool CApplyDamage::isRanged() const
{
	return rangedAttack;
}


};

VCMI_LIB_NAMESPACE_END
