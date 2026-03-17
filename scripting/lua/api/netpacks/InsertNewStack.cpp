/*
 * api/netpacks/InsertNewStack.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "InsertNewStack.h"

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

VCMI_REGISTER_SCRIPT_API(InsertNewStackProxy, "netpacks.InsertNewStack");

const std::vector<InsertNewStackProxy::CustomRegType> InsertNewStackProxy::REGISTER_CUSTOM =
{
	{"new",          &Wrapper::constructor,                                    true},
	{"setArmyId",    &InsertNewStackProxy::setArmyId,                         false},
	{"setSlot",      &InsertNewStackProxy::setSlot,                           false},
	{"setCreatureId",&InsertNewStackProxy::setCreatureId,                     false},
	{"setCount",     &InsertNewStackProxy::setCount,                          false},
	{"toNetpackLight", &PackForClientProxy<InsertNewStackProxy>::toNetpackLight, false}
};

// setArmyId(heroOrGarrisonId) — ObjectInstanceID integer
int InsertNewStackProxy::setArmyId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<InsertNewStack> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->army = value;
	return S.retVoid();
}

// setSlot(slotIndex) — army slot 0–6
int InsertNewStackProxy::setSlot(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<InsertNewStack> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->slot = SlotID(value);
	return S.retVoid();
}

// setCreatureId(creatureTypeId) — integer index of creature type
int InsertNewStackProxy::setCreatureId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<InsertNewStack> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->type = CreatureID(value);
	return S.retVoid();
}

// setCount(quantity) — number of creatures to insert
int InsertNewStackProxy::setCount(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<InsertNewStack> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->count = value;
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
