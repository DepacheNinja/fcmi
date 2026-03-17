/*
 * api/netpacks/SetMana.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "SetMana.h"

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

VCMI_REGISTER_SCRIPT_API(SetManaProxy, "netpacks.SetMana");

const std::vector<SetManaProxy::CustomRegType> SetManaProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setHeroId", &SetManaProxy::setHeroId, false},
	{"setValue", &SetManaProxy::setValue, false},
	{"setMode", &SetManaProxy::setMode, false},
	{"toNetpackLight", &PackForClientProxy<SetManaProxy>::toNetpackLight, false}
};

int SetManaProxy::setHeroId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetMana> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->hid = value;
	return S.retVoid();
}

int SetManaProxy::setValue(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetMana> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->val = value;
	return S.retVoid();
}

int SetManaProxy::setMode(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetMana> object;
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
