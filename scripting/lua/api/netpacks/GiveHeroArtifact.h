/*
 * api/netpacks/GiveHeroArtifact.h, part of VCMI engine
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

// Wraps NewArtifact CPackForClient — creates a new artifact instance on a hero.
// Usage in Lua:
//   local pack = GiveHeroArtifact.new()
//   pack:setHeroId(heroId)      -- ObjectInstanceID integer
//   pack:setArtTypeId(artTypeId) -- ArtifactID integer (artifact TYPE, e.g. 7 = Centaur Axe)
//   pack:setSlot(slotIdx)       -- ArtifactPosition integer (0-18) or -1 for first available
//   SERVER:commitPackage(pack)
class GiveHeroArtifactProxy : public SharedWrapper<NewArtifact, GiveHeroArtifactProxy>
{
public:
	using Wrapper = SharedWrapper<NewArtifact, GiveHeroArtifactProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	static int setHeroId(lua_State * L);
	static int setArtTypeId(lua_State * L);
	static int setSlot(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
