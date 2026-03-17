/*
 * api/netpacks/SetPrimarySkill.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "SetPrimarySkill.h"

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

VCMI_REGISTER_SCRIPT_API(SetPrimarySkillProxy, "netpacks.SetPrimarySkill");

const std::vector<SetPrimarySkillProxy::CustomRegType> SetPrimarySkillProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setHeroId", &SetPrimarySkillProxy::setHeroId, false},
	{"setSkill", &SetPrimarySkillProxy::setSkill, false},
	{"setValue", &SetPrimarySkillProxy::setValue, false},
	{"setMode", &SetPrimarySkillProxy::setMode, false},
	{"toNetpackLight", &PackForClientProxy<SetPrimarySkillProxy>::toNetpackLight, false}
};

int SetPrimarySkillProxy::setHeroId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetPrimarySkill> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->id = value;
	return S.retVoid();
}

int SetPrimarySkillProxy::setSkill(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetPrimarySkill> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->which = static_cast<PrimarySkill>(value);
	return S.retVoid();
}

int SetPrimarySkillProxy::setValue(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetPrimarySkill> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = 0;
	if(S.tryGet(2, value))
		object->val = value;
	return S.retVoid();
}

int SetPrimarySkillProxy::setMode(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetPrimarySkill> object;
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
