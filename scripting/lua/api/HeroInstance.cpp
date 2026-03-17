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
};

}
}

VCMI_LIB_NAMESPACE_END

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
