/*
 * api/netpacks/SetHeroExperience.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "SetHeroExperience.h"

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

VCMI_REGISTER_SCRIPT_API(SetHeroExperienceProxy, "netpacks.SetHeroExperience");

const std::vector<SetHeroExperienceProxy::CustomRegType> SetHeroExperienceProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setHeroId", &SetHeroExperienceProxy::setHeroId, false},
	{"setValue", &SetHeroExperienceProxy::setValue, false},
	{"setMode", &SetHeroExperienceProxy::setMode, false},
	{"toNetpackLight", &PackForClientProxy<SetHeroExperienceProxy>::toNetpackLight, false}
};

int SetHeroExperienceProxy::setHeroId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetHeroExperience> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->id = value;
	return S.retVoid();
}

int SetHeroExperienceProxy::setValue(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetHeroExperience> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->val = value;
	return S.retVoid();
}

int SetHeroExperienceProxy::setMode(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetHeroExperience> object;
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
