/*
 * api/netpacks/SetStackType.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "SetStackType.h"

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

VCMI_REGISTER_SCRIPT_API(SetStackTypeProxy, "netpacks.SetStackType");

const std::vector<SetStackTypeProxy::CustomRegType> SetStackTypeProxy::REGISTER_CUSTOM =
{
	{"new",          &Wrapper::constructor,                                    true},
	{"setArmyId",    &SetStackTypeProxy::setArmyId,                          false},
	{"setSlot",      &SetStackTypeProxy::setSlot,                            false},
	{"setCreatureId",&SetStackTypeProxy::setCreatureId,                      false},
	{"toNetpackLight", &PackForClientProxy<SetStackTypeProxy>::toNetpackLight, false}
};

// setArmyId(heroOrGarrisonId) — ObjectInstanceID integer
int SetStackTypeProxy::setArmyId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetStackType> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->army = value;
	return S.retVoid();
}

// setSlot(slotIndex) — army slot 0-6
int SetStackTypeProxy::setSlot(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetStackType> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->slot = SlotID(value);
	return S.retVoid();
}

// setCreatureId(creatureTypeId) — integer index of target creature type
int SetStackTypeProxy::setCreatureId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetStackType> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->type = CreatureID(value);
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
