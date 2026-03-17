/*
 * api/netpacks/SetStackEffect.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "PackForClient.h"

#include "../../../../lib/networkPacks/SetStackEffect.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
namespace netpacks
{

// FCMI: Lua wrapper for SetStackEffect netpack.
// Allows Lua scripts to apply bonus effects (morale, luck, etc.) to specific
// battle stacks at the start of combat.
//
// Usage:
//   local sse = SetStackEffect.new()
//   sse:setBattleId(event:getBattleId())
//   for _, stack in ipairs(GAME:getBattleStacks(battleId)) do
//       if hasAllyPair(stack.creatureId, armyCreatures) then
//           sse:addBonusToStack(stack.unitId, 4, 1)  -- BonusType::MORALE = 4
//       end
//   end
//   SERVER:commitPackage(sse)

class SetStackEffectProxy : public SharedWrapper<SetStackEffect, SetStackEffectProxy>
{
public:
	using Wrapper = SharedWrapper<SetStackEffect, SetStackEffectProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	// setBattleId(battleIdInt) — sets the battleID for this netpack
	static int setBattleId(lua_State * L);

	// addBonusToStack(unitId, bonusType, val) — adds a ONE_BATTLE bonus to the given stack
	//   unitId:    integer battle unit ID (from GAME:getBattleStacks())
	//   bonusType: integer BonusType enum value (4=MORALE, 5=LUCK, etc.)
	//   val:       integer bonus value (e.g. 1 for +1 morale)
	static int addBonusToStack(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
