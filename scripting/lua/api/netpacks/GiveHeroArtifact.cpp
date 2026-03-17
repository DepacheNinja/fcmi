/*
 * api/netpacks/GiveHeroArtifact.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "GiveHeroArtifact.h"

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

VCMI_REGISTER_SCRIPT_API(GiveHeroArtifactProxy, "netpacks.GiveHeroArtifact");

const std::vector<GiveHeroArtifactProxy::CustomRegType> GiveHeroArtifactProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setHeroId", &GiveHeroArtifactProxy::setHeroId, false},
	{"setArtTypeId", &GiveHeroArtifactProxy::setArtTypeId, false},
	{"setSlot", &GiveHeroArtifactProxy::setSlot, false},
	{"toNetpackLight", &PackForClientProxy<GiveHeroArtifactProxy>::toNetpackLight, false}
};

int GiveHeroArtifactProxy::setHeroId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<NewArtifact> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->artHolder = value;
	return S.retVoid();
}

int GiveHeroArtifactProxy::setArtTypeId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<NewArtifact> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = -1;
	if(S.tryGet(2, value) && value >= 0)
		object->artId = ArtifactID(value);
	return S.retVoid();
}

int GiveHeroArtifactProxy::setSlot(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<NewArtifact> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = -1;
	S.tryGet(2, value);
	if(value < 0)
		object->pos = ArtifactPosition::FIRST_AVAILABLE;
	else
		object->pos = ArtifactPosition(value);
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
