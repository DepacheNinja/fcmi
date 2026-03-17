/*
 * api/netpacks/SetStackEffect.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "SetStackEffect.h"

#include "../../LuaStack.h"

#include "../Registry.h"

#include "../../../../lib/bonuses/Bonus.h"
#include "../../../../lib/bonuses/BonusEnum.h"
#include "../../../../lib/bonuses/BonusCustomTypes.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
namespace netpacks
{

VCMI_REGISTER_SCRIPT_API(SetStackEffectProxy, "netpacks.SetStackEffect");

const std::vector<SetStackEffectProxy::CustomRegType> SetStackEffectProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setBattleId", &SetStackEffectProxy::setBattleId, false},
	{"addBonusToStack", &SetStackEffectProxy::addBonusToStack, false},
	{"toNetpackLight", &PackForClientProxy<SetStackEffectProxy>::toNetpackLight, false}
};

int SetStackEffectProxy::setBattleId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetStackEffect> object;
	if(!S.tryGet(1, object))
		return S.retVoid();

	int32_t id = -1;
	if(!S.tryGet(2, id))
		return S.retVoid();

	object->battleID = BattleID(id);
	return S.retVoid();
}

int SetStackEffectProxy::addBonusToStack(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetStackEffect> object;
	if(!S.tryGet(1, object))
		return S.retVoid();

	int32_t unitId = -1;
	if(!S.tryGet(2, unitId))
		return S.retVoid();

	int32_t bonusTypeInt = 0;
	if(!S.tryGet(3, bonusTypeInt))
		return S.retVoid();

	int32_t val = 1;
	S.tryGet(4, val);

	// Build a ONE_BATTLE bonus with BonusSource::OTHER (generic script source)
	Bonus bonus(
		BonusDuration::ONE_BATTLE,
		BonusType(bonusTypeInt),
		BonusSource::OTHER,
		val,
		BonusSourceID()
	);

	std::vector<Bonus> bonuses = { bonus };
	object->toAdd.emplace_back(static_cast<uint32_t>(unitId), bonuses);

	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
