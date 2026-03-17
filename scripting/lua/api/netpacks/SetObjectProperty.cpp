/*
 * api/netpacks/SetObjectProperty.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "SetObjectProperty.h"

#include "../../LuaStack.h"
#include "../../../../lib/networkPacks/PacksForClient.h"

#include "../Registry.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
namespace netpacks
{

VCMI_REGISTER_SCRIPT_API(SetObjectPropertyProxy, "netpacks.SetObjectProperty");

const std::vector<SetObjectPropertyProxy::CustomRegType> SetObjectPropertyProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setId", &SetObjectPropertyProxy::setId, false},
	{"setOwner", &SetObjectPropertyProxy::setOwner, false},
	{"toNetpackLight", &PackForClientProxy<SetObjectPropertyProxy>::toNetpackLight, false}
};

int SetObjectPropertyProxy::setId(lua_State * L)
{
	LuaStack S(L);

	std::shared_ptr<SetObjectProperty> object;
	if(!S.tryGet(1, object))
		return S.retVoid();

	ObjectInstanceID id;
	if(!S.tryGet(2, id))
		return S.retVoid();

	object->id = id;
	return S.retVoid();
}

// FCMI: sets what=OWNER and identifier=PlayerColor(playerIndex)
// playerIndex: 0-7 (PlayerColor integer index)
int SetObjectPropertyProxy::setOwner(lua_State * L)
{
	LuaStack S(L);

	std::shared_ptr<SetObjectProperty> object;
	if(!S.tryGet(1, object))
		return S.retVoid();

	int32_t playerIdx = -1;
	if(!S.tryGet(2, playerIdx))
		return S.retVoid();

	object->what = ObjProperty::OWNER;
	object->identifier = PlayerColor(playerIdx);
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
