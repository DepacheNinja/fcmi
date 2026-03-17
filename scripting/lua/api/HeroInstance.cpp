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

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
VCMI_REGISTER_CORE_SCRIPT_API(HeroInstanceProxy, "HeroInstance");

const std::vector<HeroInstanceProxy::CustomRegType> HeroInstanceProxy::REGISTER_CUSTOM =
{
	{"getStack", LuaMethodWrapper<CGHeroInstance, decltype(&CCreatureSet::getStackPtr), &CCreatureSet::getStackPtr>::invoke, false},
	{"getOwner", LuaMethodWrapper<CGHeroInstance, decltype(&CGObjectInstance::getOwner), &CGObjectInstance::getOwner>::invoke, false},
	{"getLevel", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getLevel), &CGHeroInstance::getLevel>::invoke, false},
	{"getExperience", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getExp), &CGHeroInstance::getExp>::invoke, false},
	{"getAttack", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getAttack), &CGHeroInstance::getAttack>::invoke, false},
	{"getDefense", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getDefense), &CGHeroInstance::getDefense>::invoke, false},
	{"getSpellPower", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getSpellPower), &CGHeroInstance::getSpellPower>::invoke, false},
	{"getKnowledge", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getKnowledge), &CGHeroInstance::getKnowledge>::invoke, false},
	{"getPrimSkillLevel", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getPrimSkillLevel), &CGHeroInstance::getPrimSkillLevel>::invoke, false},
	{"getSecSkillLevel", LuaMethodWrapper<CGHeroInstance, decltype(&CGHeroInstance::getSecSkillLevel), &CGHeroInstance::getSecSkillLevel>::invoke, false},
	{"getId", LuaMethodWrapper<CGHeroInstance, decltype(&CGObjectInstance::getId), &CGObjectInstance::getId>::invoke, false},
};

}
}

VCMI_LIB_NAMESPACE_END
