/*
 * GameCb.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include <vcmi/scripting/Service.h>

#include "../LuaWrapper.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{

class GameCbProxy : public OpaqueWrapper<const GameCb, GameCbProxy>
{
public:
	using Wrapper = OpaqueWrapper<const GameCb, GameCbProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	// FCMI additions for WOG Lua scripting
	static int getPlayerResource(lua_State * L);
	static int isPlayerHuman(lua_State * L);
	static int getPlayerHeroes(lua_State * L);
	// FCMI: get all spell IDs of a given school level — GAME:getSpellsByLevel(level)
	static int getSpellsByLevel(lua_State * L);
	// FCMI: get town IDs for a player
	static int getPlayerTowns(lua_State * L);
	// FCMI: check if a town has a specific building by subID
	static int townHasBuilding(lua_State * L);
	// FCMI: get the faction ID of a town (0=Castle,1=Rampart,...,8=Conflux)
	static int getTownFaction(lua_State * L);
	// FCMI: get hero map position (returns x, y, z integers)
	static int getHeroPosition(lua_State * L);
	// FCMI: get terrain ID at map coordinates (returns integer TerrainId)
	static int getTerrainAt(lua_State * L);
	// FCMI: get all map object IDs of a given Obj type group (e.g. 54=MONSTER, 17=CREATURE_GENERATOR1)
	static int getMapObjectIds(lua_State * L);
	// FCMI: get the creature ID from a map monster object (Obj::MONSTER, slot 0)
	static int getMonsterCreatureId(lua_State * L);
	// FCMI: get the creature count from a map monster object (Obj::MONSTER, slot 0)
	static int getMonsterCount(lua_State * L);
	// FCMI: get the creature ID offered by a dwelling at a given level (0-based)
	// Returns the first creature ID (index 0) from creatures[level].second, or -1 if unavailable.
	static int getDwellingCreatureId(lua_State * L);
	// FCMI: get the creature count offered by a dwelling at a given level
	// Returns creatures[level].first (available count), or 0 if unavailable.
	static int getDwellingCreatureCount(lua_State * L);
};

}
}

VCMI_LIB_NAMESPACE_END
