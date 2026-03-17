/*
 * api/netpacks/NewStructures.h, part of VCMI engine
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

// FCMI: NewStructures Lua proxy — adds buildings to a town.
// Usage:
//   local pack = NewStructures.new()
//   pack:setTownId(townId)          -- ObjectInstanceID of the town
//   pack:addBuilding(buildingId)    -- BuildingID integer (may be called multiple times)
//   SERVER:commitPackage(pack)
class NewStructuresProxy : public SharedWrapper<NewStructures, NewStructuresProxy>
{
public:
	using Wrapper = SharedWrapper<NewStructures, NewStructuresProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	static int setTownId(lua_State * L);
	static int addBuilding(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
