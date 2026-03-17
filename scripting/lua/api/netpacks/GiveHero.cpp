/*
 * api/netpacks/GiveHero.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "GiveHero.h"

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

VCMI_REGISTER_SCRIPT_API(GiveHeroProxy, "netpacks.GiveHero");

const std::vector<GiveHeroProxy::CustomRegType> GiveHeroProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setHeroId", &GiveHeroProxy::setHeroId, false},
	{"setPlayer", &GiveHeroProxy::setPlayer, false},
	{"toNetpackLight", &PackForClientProxy<GiveHeroProxy>::toNetpackLight, false}
};

int GiveHeroProxy::setHeroId(lua_State * L)
{
	LuaStack S(L);

	std::shared_ptr<GiveHero> object;
	if(!S.tryGet(1, object))
		return S.retVoid();

	ObjectInstanceID id;
	if(!S.tryGet(2, id))
		return S.retVoid();

	object->id = id;
	return S.retVoid();
}

int GiveHeroProxy::setPlayer(lua_State * L)
{
	LuaStack S(L);

	std::shared_ptr<GiveHero> object;
	if(!S.tryGet(1, object))
		return S.retVoid();

	int32_t playerIdx = -1;
	if(!S.tryGet(2, playerIdx))
		return S.retVoid();

	object->player = PlayerColor(playerIdx);
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
