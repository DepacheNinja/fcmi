/*
 * GameCb.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "GameCb.h"

#include <vcmi/Player.h>

#include "../LuaCallWrapper.h"
#include "../LuaStack.h"

#include "../../../lib/callback/IGameInfoCallback.h"
#include "../../../lib/mapObjects/CGHeroInstance.h"
#include "../../../lib/ResourceSet.h"
#include "../../../lib/CPlayerState.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{

// FCMI: get a player's resource amount — GAME:getPlayerResource(playerIndex, resourceType)
// playerIndex: 0-7 integer, resourceType: 0=wood 1=mercury 2=ore 3=sulfur 4=crystal 5=gems 6=gold
int GameCbProxy::getPlayerResource(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	int32_t playerIdx = -1;
	if(!S.tryGet(2, playerIdx)) return S.retNil();
	PlayerColor player(playerIdx);
	GameResID resType;
	if(!S.tryGet(3, resType)) return S.retNil();
	S.clear();
	S.push(object->getResource(player, resType));
	return 1;
}

// FCMI: check if a player is human — GAME:isPlayerHuman(playerIndex)
// playerIndex: 0-7 integer (matches event:getPlayer() return value)
int GameCbProxy::isPlayerHuman(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	int32_t playerIdx = -1;
	if(!S.tryGet(2, playerIdx)) return S.retNil();
	PlayerColor player(playerIdx);
	S.clear();
	const auto * state = object->getPlayerState(player, false);
	S.push(state != nullptr && state->isHuman());
	return 1;
}

VCMI_REGISTER_CORE_SCRIPT_API(GameCbProxy, "Game");

const std::vector<GameCbProxy::CustomRegType> GameCbProxy::REGISTER_CUSTOM =
{
	{"getDate", LuaMethodWrapper<GameCb, decltype(&GameCb::getDate), &GameCb::getDate>::invoke, false},

	{"getHero", LuaMethodWrapper<GameCb, decltype(&GameCb::getHero), &GameCb::getHero>::invoke, false},

	{"getObj", LuaMethodWrapper<GameCb, decltype(&GameCb::getObj), &GameCb::getObj>::invoke, false},

	// FCMI additions: player resource and human check needed for WOG Lua scripts
	{"getPlayerResource", &GameCbProxy::getPlayerResource, false},
	{"isPlayerHuman", &GameCbProxy::isPlayerHuman, false},
};

}
}

VCMI_LIB_NAMESPACE_END
