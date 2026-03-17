/*
 * api/netpacks/ChangeStackCount.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "ChangeStackCount.h"

#include "../../LuaStack.h"
#include "../../../../lib/networkPacks/PacksForClient.h"
#include "../../../../lib/constants/EntityIdentifiers.h"

#include "../Registry.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
namespace netpacks
{

VCMI_REGISTER_SCRIPT_API(ChangeStackCountProxy, "netpacks.ChangeStackCount");

const std::vector<ChangeStackCountProxy::CustomRegType> ChangeStackCountProxy::REGISTER_CUSTOM =
{
	{"new",          &Wrapper::constructor,                                       true},
	{"setArmyId",    &ChangeStackCountProxy::setArmyId,                          false},
	{"setSlot",      &ChangeStackCountProxy::setSlot,                            false},
	{"setCount",     &ChangeStackCountProxy::setCount,                           false},
	{"setMode",      &ChangeStackCountProxy::setMode,                            false},
	{"toNetpackLight", &PackForClientProxy<ChangeStackCountProxy>::toNetpackLight, false}
};

// setArmyId(heroOrGarrisonId) — ObjectInstanceID integer
int ChangeStackCountProxy::setArmyId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<ChangeStackCount> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->army = value;
	return S.retVoid();
}

// setSlot(slotIndex) — army slot 0–6
int ChangeStackCountProxy::setSlot(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<ChangeStackCount> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->slot = SlotID(value);
	return S.retVoid();
}

// setCount(quantity) — creature count delta (relative) or exact count (absolute)
int ChangeStackCountProxy::setCount(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<ChangeStackCount> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->count = value;
	return S.retVoid();
}

// setMode(absValue) — false=relative delta (default), true=set absolute count
int ChangeStackCountProxy::setMode(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<ChangeStackCount> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	bool absValue = false;
	S.tryGet(2, absValue);
	object->mode = absValue ? ChangeValueMode::ABSOLUTE : ChangeValueMode::RELATIVE;
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
