/*
 * api/netpacks/SetSecSkill.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "SetSecSkill.h"

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

VCMI_REGISTER_SCRIPT_API(SetSecSkillProxy, "netpacks.SetSecSkill");

const std::vector<SetSecSkillProxy::CustomRegType> SetSecSkillProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setHeroId", &SetSecSkillProxy::setHeroId, false},
	{"setSkill", &SetSecSkillProxy::setSkill, false},
	{"setValue", &SetSecSkillProxy::setValue, false},
	{"setMode", &SetSecSkillProxy::setMode, false},
	{"toNetpackLight", &PackForClientProxy<SetSecSkillProxy>::toNetpackLight, false}
};

int SetSecSkillProxy::setHeroId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetSecSkill> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->id = value;
	return S.retVoid();
}

int SetSecSkillProxy::setSkill(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetSecSkill> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->which = SecondarySkill(value);
	return S.retVoid();
}

int SetSecSkillProxy::setValue(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetSecSkill> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->val = static_cast<ui16>(value);
	return S.retVoid();
}

int SetSecSkillProxy::setMode(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetSecSkill> object;
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
