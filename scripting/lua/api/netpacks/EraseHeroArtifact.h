/*
 * api/netpacks/EraseHeroArtifact.h, part of VCMI engine
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

// Wraps BulkEraseArtifacts — removes artifacts from specified hero slots.
// Usage in Lua:
//   local pack = EraseHeroArtifact.new()
//   pack:setHeroId(heroId)   -- ObjectInstanceID integer
//   pack:addSlot(slotIdx)    -- ArtifactPosition integer (0-18), call multiple times
//   SERVER:commitPackage(pack)
class EraseHeroArtifactProxy : public SharedWrapper<BulkEraseArtifacts, EraseHeroArtifactProxy>
{
public:
	using Wrapper = SharedWrapper<BulkEraseArtifacts, EraseHeroArtifactProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	static int setHeroId(lua_State * L);
	static int addSlot(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
