/*
 * api/netpacks/SetAvailableCreatures.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "SetAvailableCreatures.h"

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

VCMI_REGISTER_SCRIPT_API(SetAvailableCreaturesProxy, "netpacks.SetAvailableCreatures");

const std::vector<SetAvailableCreaturesProxy::CustomRegType> SetAvailableCreaturesProxy::REGISTER_CUSTOM =
{
	{"new",           &Wrapper::constructor,                                            true},
	{"setDwellingId", &SetAvailableCreaturesProxy::setDwellingId,                      false},
	{"setCreature",   &SetAvailableCreaturesProxy::setCreature,                        false},
	{"toNetpackLight", &PackForClientProxy<SetAvailableCreaturesProxy>::toNetpackLight, false}
};

// setDwellingId(objectId) — ObjectInstanceID integer of the target dwelling
int SetAvailableCreaturesProxy::setDwellingId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetAvailableCreatures> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->tid = value;
	return S.retVoid();
}

// setCreature(level, creatureId, count)
// level:      0-based tier index within the dwelling
// creatureId: integer CreatureID to offer at this level
// count:      how many creatures are available to recruit
int SetAvailableCreaturesProxy::setCreature(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<SetAvailableCreatures> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t level = 0;
	int32_t creatureId = -1;
	int32_t count = 0;
	if(!S.tryGet(2, level)) return S.retVoid();
	if(!S.tryGet(3, creatureId)) return S.retVoid();
	S.tryGet(4, count);

	// Expand the creatures vector to fit this level if needed
	while(static_cast<int32_t>(object->creatures.size()) <= level)
		object->creatures.push_back({0, {}});

	object->creatures[level].first = static_cast<uint32_t>(count);
	object->creatures[level].second = { CreatureID(creatureId) };
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
