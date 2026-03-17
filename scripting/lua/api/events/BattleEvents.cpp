/*
 * BattleEvents.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "BattleEvents.h"

#include "../../LuaStack.h"
#include "../../LuaCallWrapper.h"
#include "../Registry.h"
#include "../../../../lib/battle/Unit.h"
#include "SubscriptionRegistryProxy.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
namespace events
{
using ::events::ApplyDamage;
using ::events::BattleEnded;
using ::events::BattleStarted;

VCMI_REGISTER_SCRIPT_API(ApplyDamageProxy, "events.ApplyDamage");
VCMI_REGISTER_SCRIPT_API(BattleEndedProxy, "events.BattleEnded");
VCMI_REGISTER_SCRIPT_API(BattleStartedProxy, "events.BattleStarted");

const std::vector<ApplyDamageProxy::CustomRegType> ApplyDamageProxy::REGISTER_CUSTOM =
{
	{
		"subscribeBefore",
		&SubscriptionRegistryProxy<ApplyDamageProxy>::subscribeBefore,
		true
	},
	{
		"subscribeAfter",
		&SubscriptionRegistryProxy<ApplyDamageProxy>::subscribeAfter,
		true
	},
	{
		"getInitialDamage",
		LuaMethodWrapper<ApplyDamage, decltype(&ApplyDamage::getInitialDamage), &ApplyDamage::getInitialDamage>::invoke,
		false
	},
	{
		"getDamage",
		LuaMethodWrapper<ApplyDamage, decltype(&ApplyDamage::getDamage), &ApplyDamage::getDamage>::invoke,
		false
	},
	{
		"setDamage",
		LuaMethodWrapper<ApplyDamage, decltype(&ApplyDamage::setDamage), &ApplyDamage::setDamage>::invoke,
		false
	},
	{
		"getTarget",
		LuaMethodWrapper<ApplyDamage, decltype(&ApplyDamage::getTarget), &ApplyDamage::getTarget>::invoke,
		false
	},
	// FCMI: getAttacker — returns the attacking Unit proxy (for creature-type-based damage modifiers)
	{
		"getAttacker",
		LuaMethodWrapper<ApplyDamage, decltype(&ApplyDamage::getAttacker), &ApplyDamage::getAttacker>::invoke,
		false
	},
	// FCMI: attack metadata for WOG Luck I (206), Artillery I (201), Piercing Shot (59)
	{
		"isLucky",
		LuaMethodWrapper<ApplyDamage, decltype(&ApplyDamage::isLucky), &ApplyDamage::isLucky>::invoke,
		false
	},
	{
		"isRanged",
		LuaMethodWrapper<ApplyDamage, decltype(&ApplyDamage::isRanged), &ApplyDamage::isRanged>::invoke,
		false
	},
	{
		"isBallistaDmg",
		LuaMethodWrapper<ApplyDamage, decltype(&ApplyDamage::isBallistaDmg), &ApplyDamage::isBallistaDmg>::invoke,
		false
	},
	{
		"getAttackerOwner",
		LuaMethodWrapper<ApplyDamage, decltype(&ApplyDamage::getAttackerOwner), &ApplyDamage::getAttackerOwner>::invoke,
		false
	},
};

const std::vector<BattleEndedProxy::CustomRegType> BattleEndedProxy::REGISTER_CUSTOM =
{
	{"subscribeBefore", &SubscriptionRegistryProxy<BattleEndedProxy>::subscribeBefore, true},
	{"subscribeAfter", &SubscriptionRegistryProxy<BattleEndedProxy>::subscribeAfter, true},
	{"getVictor", LuaMethodWrapper<BattleEnded, decltype(&BattleEnded::getVictorIndex), &BattleEnded::getVictorIndex>::invoke, false},
	{"getLoser", LuaMethodWrapper<BattleEnded, decltype(&BattleEnded::getLoserIndex), &BattleEnded::getLoserIndex>::invoke, false},
	{"getWinnerHeroId", LuaMethodWrapper<BattleEnded, decltype(&BattleEnded::getWinnerHeroId), &BattleEnded::getWinnerHeroId>::invoke, false},
	{"getLoserHeroId", LuaMethodWrapper<BattleEnded, decltype(&BattleEnded::getLoserHeroId), &BattleEnded::getLoserHeroId>::invoke, false},
	{"getExpAwarded", LuaMethodWrapper<BattleEnded, decltype(&BattleEnded::getExpAwarded), &BattleEnded::getExpAwarded>::invoke, false},
	// FCMI: 0=NORMAL, 1=ESCAPE, 2=SURRENDER — lets Lua detect how the battle ended
	{"getBattleResult", LuaMethodWrapper<BattleEnded, decltype(&BattleEnded::getBattleResult), &BattleEnded::getBattleResult>::invoke, false},
};

const std::vector<BattleStartedProxy::CustomRegType> BattleStartedProxy::REGISTER_CUSTOM =
{
	{"subscribeBefore", &SubscriptionRegistryProxy<BattleStartedProxy>::subscribeBefore, true},
	{"subscribeAfter",  &SubscriptionRegistryProxy<BattleStartedProxy>::subscribeAfter,  true},
	{"getAttackerPlayer", LuaMethodWrapper<BattleStarted, decltype(&BattleStarted::getAttackerPlayer), &BattleStarted::getAttackerPlayer>::invoke, false},
	{"getAttackerHeroId", LuaMethodWrapper<BattleStarted, decltype(&BattleStarted::getAttackerHeroId), &BattleStarted::getAttackerHeroId>::invoke, false},
	// FCMI: army object ID — for neutral creatures, the CGCreature map object ID (not hero ID)
	{"getAttackerArmyId", LuaMethodWrapper<BattleStarted, decltype(&BattleStarted::getAttackerArmyId), &BattleStarted::getAttackerArmyId>::invoke, false},
	{"getDefenderPlayer", LuaMethodWrapper<BattleStarted, decltype(&BattleStarted::getDefenderPlayer), &BattleStarted::getDefenderPlayer>::invoke, false},
	{"getDefenderHeroId", LuaMethodWrapper<BattleStarted, decltype(&BattleStarted::getDefenderHeroId), &BattleStarted::getDefenderHeroId>::invoke, false},
	// FCMI: army object ID — for neutral creatures, the CGCreature map object ID (not hero ID)
	{"getDefenderArmyId", LuaMethodWrapper<BattleStarted, decltype(&BattleStarted::getDefenderArmyId), &BattleStarted::getDefenderArmyId>::invoke, false},
	// FCMI: BattleID integer — used with SetStackEffect and GAME:getBattleStacks()
	{"getBattleId", LuaMethodWrapper<BattleStarted, decltype(&BattleStarted::getBattleId), &BattleStarted::getBattleId>::invoke, false},
};

}
}
}


VCMI_LIB_NAMESPACE_END
