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
#include "../../../lib/mapping/TerrainTile.h"
#include "../../../lib/TerrainHandler.h"
#include "../../../lib/gameState/CGameState.h"
#include "../../../lib/mapping/CMap.h"
#include "../../../lib/mapObjects/CGCreature.h"

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

// FCMI: get hero map position — GAME:getHeroPosition(heroId)
// Returns three integers: x, y, z (level). Returns nil if hero not found.
// Useful for terrain-based effects (Magic Plains mana regen, etc.)
int GameCbProxy::getHeroPosition(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	ObjectInstanceID heroId;
	if(!S.tryGet(2, heroId)) return S.retNil();
	S.clear();
	const auto * hero = object->getHero(heroId);
	if(!hero)
		return S.retNil();
	const int3 pos = hero->visitablePos();
	lua_pushinteger(L, pos.x);
	lua_pushinteger(L, pos.y);
	lua_pushinteger(L, pos.z);
	return 3;
}

// FCMI: get terrain name at map position — GAME:getTerrainAt(x, y, z)
// Returns the terrain identifier string (e.g. "grass", "dirt", "magicPlains").
// Common H3 terrains: "dirt", "sand", "grass", "snow", "swamp", "rough",
//   "subterranean", "lava", "water", "rock".
// WOG special terrains (from wake-of-gods maps): "magicPlains", "cloverFields",
//   "fieryFields", "lucidPools", "holyGround", "rockLand", "evilFog", "cursedGround".
// Returns nil if coordinates are out of bounds.
int GameCbProxy::getTerrainAt(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	int32_t x = 0, y = 0, z = 0;
	if(!S.tryGet(2, x)) return S.retNil();
	if(!S.tryGet(3, y)) return S.retNil();
	S.tryGet(4, z);  // optional — defaults to 0 (surface)
	S.clear();
	const int3 pos(x, y, z);
	if(!object->isInTheMap(pos)) return S.retNil();
	const auto * tile = object->getTile(pos, false);
	if(!tile) return S.retNil();
	const auto * terrain = tile->getTerrainID().toEntity(LIBRARY);
	if(!terrain) return S.retNil();
	S.push(terrain->identifier);
	return 1;
}

// FCMI: get the faction ID of a town — GAME:getTownFaction(townId)
// townId: ObjectInstanceID integer (from getPlayerTowns or BuildingBuilt:getTown)
// Returns integer faction ID: 0=Castle,1=Rampart,2=Tower,3=Inferno,4=Necropolis,
//   5=Dungeon,6=Stronghold,7=Fortress,8=Conflux. Returns nil if town not found.
int GameCbProxy::getTownFaction(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	ObjectInstanceID townId;
	if(!S.tryGet(2, townId)) return S.retNil();
	S.clear();
	const auto * town = dynamic_cast<const CGTownInstance*>(object->getObj(townId, false));
	if(!town)
		return S.retNil();
	S.push(town->getFactionID().getNum());
	return 1;
}

// FCMI: enumerate all map object IDs of a given Obj type group — GAME:getMapObjectIds(objTypeGroup)
// objTypeGroup: integer Obj enum value (54=MONSTER, 17=CREATURE_GENERATOR1, 18=CG2, 19=CG3, 20=CG4)
// Returns a Lua table of integer ObjectInstanceIDs.
// Use GAME:getMonsterCreatureId(id) / GAME:getMonsterCount(id) to read neutral monster data.
// Use ChangeStackCount netpack with the returned IDs to modify neutral stack sizes.
int GameCbProxy::getMapObjectIds(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	int32_t objTypeGroup = -1;
	if(!S.tryGet(2, objTypeGroup)) return S.retNil();
	S.clear();

	lua_newtable(L);
	int idx = 1;
	for(const auto * obj : object->gameState().getMap().getObjects())
	{
		if(obj && obj->ID.getNum() == objTypeGroup)
		{
			lua_pushinteger(L, obj->id.getNum());
			lua_rawseti(L, -2, idx++);
		}
	}
	return 1;
}

// FCMI: get creature ID (integer CreatureID) from a map monster — GAME:getMonsterCreatureId(objectId)
// objectId: ObjectInstanceID integer of an Obj::MONSTER map object (from getMapObjectIds(54))
// Returns integer creature ID, or nil if not a monster or stack is empty.
int GameCbProxy::getMonsterCreatureId(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	ObjectInstanceID objectId;
	if(!S.tryGet(2, objectId)) return S.retNil();
	S.clear();
	const auto * creature = dynamic_cast<const CGCreature*>(object->getObj(objectId, false));
	if(!creature) return S.retNil();
	const auto * stack = creature->getStackPtr(SlotID(0));
	if(!stack) return S.retNil();
	S.push(stack->getType()->getIndex());
	return 1;
}

// FCMI: get creature count from a map monster — GAME:getMonsterCount(objectId)
// objectId: ObjectInstanceID integer of an Obj::MONSTER map object (from getMapObjectIds(54))
// Returns integer creature count, or nil if not a monster or stack is empty.
int GameCbProxy::getMonsterCount(lua_State * L)
{
	LuaStack S(L);
	const GameCb * object = nullptr;
	if(!S.tryGet(1, object)) return S.retNil();
	ObjectInstanceID objectId;
	if(!S.tryGet(2, objectId)) return S.retNil();
	S.clear();
	const auto * creature = dynamic_cast<const CGCreature*>(object->getObj(objectId, false));
	if(!creature) return S.retNil();
	const auto * stack = creature->getStackPtr(SlotID(0));
	if(!stack) return S.retNil();
	S.push(static_cast<int32_t>(stack->count));
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
	{"getTownFaction", &GameCbProxy::getTownFaction, false},
	{"getHeroPosition", &GameCbProxy::getHeroPosition, false},
	{"getTerrainAt", &GameCbProxy::getTerrainAt, false},
	{"getMapObjectIds", &GameCbProxy::getMapObjectIds, false},
	{"getMonsterCreatureId", &GameCbProxy::getMonsterCreatureId, false},
	{"getMonsterCount", &GameCbProxy::getMonsterCount, false},
};

}
}

VCMI_LIB_NAMESPACE_END
