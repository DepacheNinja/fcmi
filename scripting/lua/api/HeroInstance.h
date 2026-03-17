/*
 * HeroInstance.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include <vcmi/HeroClass.h>

#include "../LuaWrapper.h"

#include "../../../lib/mapObjects/CGHeroInstance.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{

class HeroInstanceProxy : public OpaqueWrapper<const CGHeroInstance, HeroInstanceProxy>
{
public:
	using Wrapper = OpaqueWrapper<const CGHeroInstance, HeroInstanceProxy>;
	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;
	// FCMI: check if hero has a specific spell in their spellbook
	static int hasSpell(lua_State * L);
	// FCMI: check if hero has a spellbook
	static int hasSpellbook(lua_State * L);
};


}
}

VCMI_LIB_NAMESPACE_END
