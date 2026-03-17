/*
 * api/netpacks/ChangeSpells.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "ChangeSpells.h"

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

VCMI_REGISTER_SCRIPT_API(ChangeSpellsProxy, "netpacks.ChangeSpells");

const std::vector<ChangeSpellsProxy::CustomRegType> ChangeSpellsProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setHeroId", &ChangeSpellsProxy::setHeroId, false},
	{"addSpell", &ChangeSpellsProxy::addSpell, false},
	{"setLearn", &ChangeSpellsProxy::setLearn, false},
	{"toNetpackLight", &PackForClientProxy<ChangeSpellsProxy>::toNetpackLight, false}
};

int ChangeSpellsProxy::setHeroId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<ChangeSpells> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->hid = value;
	return S.retVoid();
}

int ChangeSpellsProxy::addSpell(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<ChangeSpells> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t spellId = -1;
	if(S.tryGet(2, spellId) && spellId >= 0)
		object->spells.insert(SpellID(spellId));
	return S.retVoid();
}

int ChangeSpellsProxy::setLearn(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<ChangeSpells> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	bool learn = true;
	S.tryGet(2, learn);
	object->learn = learn ? 1 : 0;
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
