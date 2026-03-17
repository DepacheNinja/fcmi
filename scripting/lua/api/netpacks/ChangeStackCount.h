/*
 * api/netpacks/ChangeStackCount.h, part of VCMI engine
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

// FCMI: ChangeStackCount Lua proxy — changes creature count in an existing army slot.
// Usage:
//   local pack = ChangeStackCount.new()
//   pack:setArmyId(heroId)   -- ObjectInstanceID of the hero
//   pack:setSlot(0)           -- army slot index (0–6)
//   pack:setCount(10)         -- creature count delta (or absolute if setMode(true))
//   pack:setMode(false)       -- false=relative (add/sub), true=absolute (set exact)
//   SERVER:commitPackage(pack)
class ChangeStackCountProxy : public SharedWrapper<ChangeStackCount, ChangeStackCountProxy>
{
public:
	using Wrapper = SharedWrapper<ChangeStackCount, ChangeStackCountProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	static int setArmyId(lua_State * L);
	static int setSlot(lua_State * L);
	static int setCount(lua_State * L);
	static int setMode(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
