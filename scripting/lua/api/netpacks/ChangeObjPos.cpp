/*
 * api/netpacks/ChangeObjPos.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "ChangeObjPos.h"

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

VCMI_REGISTER_SCRIPT_API(ChangeObjPosProxy, "netpacks.ChangeObjPos");

const std::vector<ChangeObjPosProxy::CustomRegType> ChangeObjPosProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setObjectId", &ChangeObjPosProxy::setObjectId, false},
	{"setPosition", &ChangeObjPosProxy::setPosition, false},
	{"setInitiator", &ChangeObjPosProxy::setInitiator, false},
	{"toNetpackLight", &PackForClientProxy<ChangeObjPosProxy>::toNetpackLight, false}
};

int ChangeObjPosProxy::setObjectId(lua_State * L)
{
	LuaStack S(L);

	std::shared_ptr<ChangeObjPos> object;
	if(!S.tryGet(1, object))
		return S.retVoid();

	ObjectInstanceID id;
	if(!S.tryGet(2, id))
		return S.retVoid();

	object->objid = id;
	return S.retVoid();
}

// setPosition(x, y, z) — z is optional, defaults to 0 (surface level)
int ChangeObjPosProxy::setPosition(lua_State * L)
{
	LuaStack S(L);

	std::shared_ptr<ChangeObjPos> object;
	if(!S.tryGet(1, object))
		return S.retVoid();

	int32_t x = 0, y = 0, z = 0;
	if(!S.tryGet(2, x)) return S.retVoid();
	if(!S.tryGet(3, y)) return S.retVoid();
	S.tryGet(4, z);  // optional

	object->nPos = int3(x, y, z);
	return S.retVoid();
}

// setInitiator(playerIndex) — 0-7 for player, 255 for system/neutral actions
int ChangeObjPosProxy::setInitiator(lua_State * L)
{
	LuaStack S(L);

	std::shared_ptr<ChangeObjPos> object;
	if(!S.tryGet(1, object))
		return S.retVoid();

	int32_t playerIdx = 255;
	S.tryGet(2, playerIdx);
	object->initiator = PlayerColor(playerIdx);
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
