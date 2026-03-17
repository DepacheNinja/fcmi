/*
 * HeroInstance.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "HeroInstance.h"

#include "Registry.h"

#include "../LuaStack.h"
#include "../LuaCallWrapper.h"
#include "../../../lib/constants/EntityIdentifiers.h"
#include "../../../lib/entities/artifact/CArtifactSet.h"
#include "../../../lib/entities/artifact/CArtifactInstance.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
VCMI_REGISTER_CORE_SCRIPT_API(HeroInstanceProxy, "HeroInstance");

// Static wrappers for primary stats — AFactionMember has virtual getAttack(bool)/getDefense(bool)
// with different signatures, so we can't add getAttack()/getDefense() to CGHeroInstance without
// hiding the virtual. Use free wrappers calling getPrimSkillLevel() directly instead.
static int heroGetAttack(lua_State * L)
{
	LuaStack S(L);
	const CGHeroInstance * hero = nullptr;
	if(!S.tryGet(1, hero)) return S.retNil();
	S.clear();
	S.push(hero->getPrimSkillLevel(PrimarySkill::ATTACK));
	return 1;
}

static int heroGetDefense(lua_State * L)
{
	LuaStack S(L);
	const CGHeroInstance * hero = nullptr;
	if(!S.tryGet(1, hero)) return S.retNil();
	S.clear();
	S.push(hero->getPrimSkillLevel(PrimarySkill::DEFENSE));
	return 1;
}

static int heroHasSpell(lua_State * L)
{
	LuaStack S(L);
	const CGHeroInstance * hero = nullptr;
	if(!S.tryGet(1, hero)) return S.retNil();
	int32_t spellId = -1;
	if(!S.tryGet(2, spellId)) return S.retNil();
	S.clear();
	S.push(hero->spellbookContainsSpell(SpellID(spellId)));
	return 1;
}

static int heroHasSpellbook(lua_State * L)
{
	LuaStack S(L);
	const CGHeroInstance * hero = nullptr;
	if(!S.tryGet(1, hero)) return S.retNil();
	S.clear();
	S.push(hero->hasSpellbook());
	return 1;
}

// FCMI: getFactionId — returns integer faction ID for the hero's starting faction.
// Faction IDs match H3 faction order: 0=Castle,1=Rampart,2=Tower,3=Inferno,4=Necropolis,
// 5=Dungeon,6=Stronghold,7=Fortress,8=Conflux,9=Neutral.
static int heroGetFactionId(lua_State * L)
{
	LuaStack S(L);
	const CGHeroInstance * hero = nullptr;
	if(!S.tryGet(1, hero)) return S.retNil();
	S.clear();
	S.push(hero->getFactionID().getNum());
	return 1;
}

static int heroGetArtifactAtSlot(lua_State * L)
{
	LuaStack S(L);
	const CGHeroInstance * hero = nullptr;
	if(!S.tryGet(1, hero)) return S.retNil();
	int32_t slotIdx = -1;
	if(!S.tryGet(2, slotIdx)) return S.retNil();
	S.clear();
	if(slotIdx < 0 || slotIdx > 18) { S.push(-1); return 1; }
	const auto * art = hero->getArt(ArtifactPosition(slotIdx));
	if(!art) { S.push(-1); return 1; }
	S.push(art->getTypeId().getNum());
	return 1;
}

const std::vector<HeroInstanceProxy::CustomRegType> HeroInstanceProxy::REGISTER_CUSTOM =
{
	{"getStack", LuaMethodWrapper<CGHeroInstance, decltype(&CCreatureSet::getStackPtr), &CCreatureSet::getStackPtr>::invoke, false},
	{"getOwner", LuaMethodWrapper<CGHeroInstance, decltype(&CGObjectInstance::getOwner), &CGObjectInstance::getOwner>::invoke, false},
	{"getLevel", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getLevel), &CGHeroInstance::getLevel>::invoke, false},
	{"getExperience", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getExp), &CGHeroInstance::getExp>::invoke, false},
	{"getAttack", heroGetAttack, false},
	{"getDefense", heroGetDefense, false},
	{"getSpellPower", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getSpellPower), &CGHeroInstance::getSpellPower>::invoke, false},
	{"getKnowledge", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getKnowledge), &CGHeroInstance::getKnowledge>::invoke, false},
	{"getPrimSkillLevel", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getPrimSkillLevel), &CGHeroInstance::getPrimSkillLevel>::invoke, false},
	{"getSecSkillLevel", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getSecSkillLevel), &CGHeroInstance::getSecSkillLevel>::invoke, false},
	{"getId", LuaMethodWrapper<CGHeroInstance, decltype(&CGObjectInstance::getId), &CGObjectInstance::getId>::invoke, false},
	{"getMana", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getMana), &CGHeroInstance::getMana>::invoke, false},
	{"getManaMax", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::manaLimit), &CGHeroInstance::manaLimit>::invoke, false},
	{"getManaRegen", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::manaRegain), &CGHeroInstance::manaRegain>::invoke, false},
	{"hasSpell", heroHasSpell, false},
	{"hasSpellbook", heroHasSpellbook, false},
	{"getFactionId", heroGetFactionId, false},
	{"getArtifactAtSlot", heroGetArtifactAtSlot, false},
};

}
}

VCMI_LIB_NAMESPACE_END
