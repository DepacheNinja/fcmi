/*
 * api/netpacks/EraseHeroArtifact.cpp, part of VCMI engine
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "EraseHeroArtifact.h"

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

VCMI_REGISTER_SCRIPT_API(EraseHeroArtifactProxy, "netpacks.EraseHeroArtifact");

const std::vector<EraseHeroArtifactProxy::CustomRegType> EraseHeroArtifactProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setHeroId", &EraseHeroArtifactProxy::setHeroId, false},
	{"addSlot", &EraseHeroArtifactProxy::addSlot, false},
	{"toNetpackLight", &PackForClientProxy<EraseHeroArtifactProxy>::toNetpackLight, false}
};

int EraseHeroArtifactProxy::setHeroId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<BulkEraseArtifacts> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	ObjectInstanceID value;
	if(S.tryGet(2, value))
		object->artHolder = value;
	return S.retVoid();
}

int EraseHeroArtifactProxy::addSlot(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<BulkEraseArtifacts> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = -1;
	if(S.tryGet(2, value) && value >= 0)
		object->posPack.push_back(ArtifactPosition(value));
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
