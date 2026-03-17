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
#include "../../../lib/mapObjects/CGTownInstance.h"
#include "../../../lib/constants/EntityIdentifiers.h"
#include "../../../lib/ResourceSet.h"
#include "../../../lib/CPlayerState.h"
#include "../../../lib/GameLibrary.h"
#include "../../../lib/spells/CSpellHandler.h"

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

// FCMI: get list of hero IDs for a player — GAME:getPlayerHeroes(playerIndex)
// Returns a Lua table of integer hero IDs (ObjectInstanceID.getNum()).
// Use GAME:getHero(id) to get the hero object.
int GameCbProxy::getPlayerHeroes(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	int32_t playerIdx = -1;
	if(!S.tryGet(2, playerIdx)) return S.retNil();
	PlayerColor player(playerIdx);
	S.clear();
	const auto * state = object->getPlayerState(player, false);
	if(!state)
	{
		lua_newtable(L);
		return 1;
	}
	auto heroes = state->getHeroes();
	lua_newtable(L);
	int idx = 1;
	for(const auto * hero : heroes)
	{
		if(hero)
		{
			lua_pushinteger(L, hero->id.getNum());
			lua_rawseti(L, -2, idx++);
		}
	}
	return 1;
}

// FCMI: get all spell IDs of a given school level — GAME:getSpellsByLevel(level)
// level: 1-5 (spell school level)
// Returns a Lua table of integer spell IDs (SpellID values).
// Use with ChangeSpells netpack to give spells to heroes.
int GameCbProxy::getSpellsByLevel(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	int32_t targetLevel = 1;
	S.tryGet(2, targetLevel);
	S.clear();

	lua_newtable(L);
	int idx = 1;
	for(const auto & spell : LIBRARY->spellh->objects)
	{
		if(spell && spell->getLevel() == targetLevel && !spell->isSpecial())
		{
			lua_pushinteger(L, spell->getId().getNum());
			lua_rawseti(L, -2, idx++);
		}
	}
	return 1;
}

// FCMI: get list of town IDs for a player — GAME:getPlayerTowns(playerIndex)
// Returns a Lua table of integer town IDs (ObjectInstanceID.getNum()).
// Use GAME:getObj(id) to get the ObjectInstance, or GAME:townHasBuilding(id, buildingSubID).
int GameCbProxy::getPlayerTowns(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	int32_t playerIdx = -1;
	if(!S.tryGet(2, playerIdx)) return S.retNil();
	PlayerColor player(playerIdx);
	S.clear();
	const auto * state = object->getPlayerState(player, false);
	if(!state)
	{
		lua_newtable(L);
		return 1;
	}
	auto towns = state->getTowns();
	lua_newtable(L);
	int idx = 1;
	for(const auto * town : towns)
	{
		if(town)
		{
			lua_pushinteger(L, town->id.getNum());
			lua_rawseti(L, -2, idx++);
		}
	}
	return 1;
}

// FCMI: check if a town has a specific building — GAME:townHasBuilding(townId, buildingSubID)
// buildingSubID matches BuildingSubID enum values (MAGES_GUILD_1=0, FORT=7, CITY_HALL=12, etc.)
// Returns true if the building is built, false otherwise.
int GameCbProxy::townHasBuilding(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	ObjectInstanceID townId;
	if(!S.tryGet(2, townId)) return S.retNil();
	int32_t buildingSubID = -1;
	if(!S.tryGet(3, buildingSubID)) return S.retNil();
	S.clear();
	const auto * town = dynamic_cast<const CGTownInstance*>(object->getObj(townId, false));
	if(!town)
	{
		S.push(false);
		return 1;
	}
	S.push(town->hasBuilt(BuildingID(buildingSubID)));
	return 1;
}

VCMI_REGISTER_CORE_SCRIPT_API(GameCbProxy, "Game");

const std::vector<GameCbProxy::CustomRegType> GameCbProxy::REGISTER_CUSTOM =
{
	{"getDate", LuaMethodWrapper<GameCb, decltype(&GameCb::getDate), &GameCb::getDate>::invoke, false},

	{"getHero", LuaMethodWrapper<GameCb, decltype(&GameCb::getHero), &GameCb::getHero>::invoke, false},

	{"getObj", LuaMethodWrapper<GameCb, decltype(&GameCb::getObj), &GameCb::getObj>::invoke, false},

	// FCMI additions: player resource, human check, and hero iteration for WOG Lua scripts
	{"getPlayerResource", &GameCbProxy::getPlayerResource, false},
	{"isPlayerHuman", &GameCbProxy::isPlayerHuman, false},
	{"getPlayerHeroes", &GameCbProxy::getPlayerHeroes, false},
	{"getSpellsByLevel", &GameCbProxy::getSpellsByLevel, false},
	{"getPlayerTowns", &GameCbProxy::getPlayerTowns, false},
	{"townHasBuilding", &GameCbProxy::townHasBuilding, false},
};

}
}

VCMI_LIB_NAMESPACE_END
