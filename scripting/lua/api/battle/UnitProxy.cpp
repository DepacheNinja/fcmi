/*
 * UnitProxy.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"

#include "UnitProxy.h"

#include "../../LuaStack.h"
#include "../../LuaCallWrapper.h"
#include "../Registry.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
namespace battle
{

VCMI_REGISTER_SCRIPT_API(UnitProxy, "battle.Unit")

// FCMI: getCreatureId — returns integer CreatureID for the unit's creature type.
// Useful in ApplyDamage handlers to implement creature-type-specific damage rules,
// e.g. creature hate pairs (Angels vs Liches) or elemental protection checks.
static int unitGetCreatureId(lua_State * L)
{
	LuaStack S(L);
	const Unit * unit = nullptr;
	if(!S.tryGet(1, unit)) return S.retNil();
	S.clear();
	S.push(unit->creatureId().getNum());
	return 1;
}

// FCMI: hasBonusFromSpell(spellId) — returns true if the unit currently has an
// active bonus sourced from the given spell (by integer SpellID index).
// Use to check whether a Protection/buff spell is active on a unit in ApplyDamage handlers.
// Example: unit:hasBonusFromSpell(31) checks for active "Protection from Fire" (index 31).
static int unitHasBonusFromSpell(lua_State * L)
{
	LuaStack S(L);
	const Unit * unit = nullptr;
	int32_t spellId = -1;
	if(!S.tryGet(1, unit)) return S.retNil();
	if(!S.tryGet(2, spellId)) return S.retNil();
	S.clear();
	S.push(unit->getBonusBearer()->hasBonusFrom(BonusSource::SPELL_EFFECT, BonusSourceID(SpellID(spellId))));
	return 1;
}

const std::vector<UnitProxy::CustomRegType> UnitProxy::REGISTER_CUSTOM =
{
	{"getMinDamage", LuaMethodWrapper<Unit, decltype(&ACreature::getMinDamage), &ACreature::getMinDamage>::invoke, false},
	{"getMaxDamage", LuaMethodWrapper<Unit, decltype(&ACreature::getMaxDamage), &ACreature::getMaxDamage>::invoke, false},
	{"getAttack", LuaMethodWrapper<Unit, decltype(&ACreature::getAttack), &ACreature::getAttack>::invoke, false},
	{"getDefense", LuaMethodWrapper<Unit, decltype(&ACreature::getDefense), &ACreature::getDefense>::invoke, false},
	{"isAlive", LuaMethodWrapper<Unit, decltype(&Unit::alive), &Unit::alive>::invoke, false},
	{"unitId", LuaMethodWrapper<Unit, decltype(&IUnitInfo::unitId), &IUnitInfo::unitId>::invoke, false},
	{"getCreatureId", unitGetCreatureId, false},
	{"hasBonusFromSpell", unitHasBonusFromSpell, false},
};

}
}
}

VCMI_LIB_NAMESPACE_END
