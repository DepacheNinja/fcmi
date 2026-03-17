/*
 * api/netpacks/SetStackType.h, part of VCMI engine
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

// FCMI: SetStackType Lua proxy — changes the creature type in an existing army slot.
// Equivalent to ERM HE:C (change creature type in hero slot).
// Usage:
//   local pack = SetStackType.new()
//   pack:setArmyId(heroId)      -- ObjectInstanceID of the hero
//   pack:setSlot(0)             -- army slot index (0-6)
//   pack:setCreatureId(typeId)  -- target CreatureID (integer)
//   SERVER:commitPackage(pack)
class SetStackTypeProxy : public SharedWrapper<SetStackType, SetStackTypeProxy>
{
public:
	using Wrapper = SharedWrapper<SetStackType, SetStackTypeProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	static int setArmyId(lua_State * L);
	static int setSlot(lua_State * L);
	static int setCreatureId(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
