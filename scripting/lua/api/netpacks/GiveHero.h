/*
 * api/netpacks/GiveHero.h, part of VCMI engine
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

// FCMI: Lua wrapper for GiveHero netpack.
// Transfers a hero object to a new player. Used for espionage and diplomacy features.
//
// Usage:
//   local gh = GiveHero.new()
//   gh:setHeroId(heroObjectId)
//   gh:setPlayer(playerIndex)
//   SERVER:commitPackage(gh)

class GiveHeroProxy : public SharedWrapper<GiveHero, GiveHeroProxy>
{
public:
	using Wrapper = SharedWrapper<GiveHero, GiveHeroProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	// setHeroId(objectInstanceId) — the hero object to transfer
	static int setHeroId(lua_State * L);
	// setPlayer(playerIndex) — destination player (0-7)
	static int setPlayer(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
