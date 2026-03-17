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
};

}
}

VCMI_LIB_NAMESPACE_END
