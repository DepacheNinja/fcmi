/*
 * api/netpacks/SetObjectProperty.h, part of VCMI engine
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

// FCMI: Lua wrapper for SetObjectProperty netpack.
// Allows Lua scripts to change map object properties such as ownership of towns and mines.
//
// Usage (change town/mine owner):
//   local sop = SetObjectProperty.new()
//   sop:setId(townId)
//   sop:setOwner(playerIndex)   -- 0-7 player index
//   SERVER:commitPackage(sop)
//
// ObjProperty values: OWNER=1, VISITED=2, OBELISK_VISITED=3

class SetObjectPropertyProxy : public SharedWrapper<SetObjectProperty, SetObjectPropertyProxy>
{
public:
	using Wrapper = SharedWrapper<SetObjectProperty, SetObjectPropertyProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	// setId(objectInstanceId) — sets the target object (town, mine, dwelling, etc.)
	static int setId(lua_State * L);
	// setOwner(playerIndex) — convenience: sets what=OWNER and identifier=PlayerColor(playerIndex)
	static int setOwner(lua_State * L);
	// FCMI Phase 2: convenience methods for wog_mithril_spending shrine/witch hut reroll
	// setShrineSpell(spellId) — sets what=SHRINE_SPELL_ID, identifier=NumericID(spellId)
	static int setShrineSpell(lua_State * L);
	// setWitchHutSkill(skillId) — sets what=WITCH_HUT_SKILL_ID, identifier=NumericID(skillId)
	static int setWitchHutSkill(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
