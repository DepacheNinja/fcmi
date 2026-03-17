/*
 * api/netpacks/InsertNewStack.h, part of VCMI engine
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

// FCMI: InsertNewStack Lua proxy — adds a new creature stack to a hero or garrison army.
// Usage:
//   local pack = InsertNewStack.new()
//   pack:setArmyId(heroId)      -- ObjectInstanceID of the hero
//   pack:setSlot(0)             -- army slot index (0–6)
//   pack:setCreatureId(typeId)  -- CreatureID (integer index of creature type)
//   pack:setCount(25)           -- number of creatures
//   SERVER:commitPackage(pack)
class InsertNewStackProxy : public SharedWrapper<InsertNewStack, InsertNewStackProxy>
{
public:
	using Wrapper = SharedWrapper<InsertNewStack, InsertNewStackProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	static int setArmyId(lua_State * L);
	static int setSlot(lua_State * L);
	static int setCreatureId(lua_State * L);
	static int setCount(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
