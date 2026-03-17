/*
 * api/netpacks/SetAvailableCreatures.h, part of VCMI engine
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

// FCMI: SetAvailableCreatures Lua proxy — sets creature type/count offered by a dwelling.
// Used for Refugee Camp Sync (option 200): makes all camps offer the same creature.
// Usage:
//   local pack = SetAvailableCreatures.new()
//   pack:setDwellingId(objectId)             -- ObjectInstanceID of the dwelling
//   pack:setCreature(level, creatureId, count) -- set creature at given 0-based level
//   SERVER:commitPackage(pack)
class SetAvailableCreaturesProxy : public SharedWrapper<SetAvailableCreatures, SetAvailableCreaturesProxy>
{
public:
	using Wrapper = SharedWrapper<SetAvailableCreatures, SetAvailableCreaturesProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	static int setDwellingId(lua_State * L);
	static int setCreature(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
