/*
 * api/netpacks/NewStructures.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "NewStructures.h"

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

VCMI_REGISTER_SCRIPT_API(NewStructuresProxy, "netpacks.NewStructures");

const std::vector<NewStructuresProxy::CustomRegType> NewStructuresProxy::REGISTER_CUSTOM =
{
	{"new",          &Wrapper::constructor,                                       true},
	{"setTownId",    &NewStructuresProxy::setTownId,                             false},
	{"addBuilding",  &NewStructuresProxy::addBuilding,                           false},
	{"toNetpackLight", &PackForClientProxy<NewStructuresProxy>::toNetpackLight,   false}
};

// setTownId(townId) — ObjectInstanceID integer of the target town
int NewStructuresProxy::setTownId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<NewStructures> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->tid = value;
	return S.retVoid();
}

// addBuilding(buildingId) — adds one BuildingID integer to the set
int NewStructuresProxy::addBuilding(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<NewStructures> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = -1;
	if(S.tryGet(2, value) && value >= 0)
		object->bid.insert(BuildingID(value));
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
