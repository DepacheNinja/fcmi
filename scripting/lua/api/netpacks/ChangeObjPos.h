/*
 * api/netpacks/ChangeObjPos.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "PackForClient.h"

#include "../../../../lib/networkPacks/PacksForClient.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
namespace netpacks
{

// FCMI: Lua wrapper for ChangeObjPos netpack.
// Allows Lua scripts to teleport map objects (monsters, heroes, dwellings) to a new position.
// Used by wog_wandering_monsters.lua to move neutral stacks each week.
//
// Usage:
//   local cop = ChangeObjPos.new()
//   cop:setObjectId(objectId)
//   cop:setPosition(x, y, z)
//   cop:setInitiator(playerIndex)   -- optional, use 255 for neutral/system
//   SERVER:commitPackage(cop)

class ChangeObjPosProxy : public SharedWrapper<ChangeObjPos, ChangeObjPosProxy>
{
public:
	using Wrapper = SharedWrapper<ChangeObjPos, ChangeObjPosProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	// setObjectId(objectInstanceId) — the map object to move
	static int setObjectId(lua_State * L);
	// setPosition(x, y, z) — new visitable tile position; z defaults to 0 (surface)
	static int setPosition(lua_State * L);
	// setInitiator(playerIndex) — player who triggered the move (use 255 for system/neutral)
	static int setInitiator(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
