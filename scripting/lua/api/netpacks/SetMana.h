/*
 * api/netpacks/SetMana.h, part of VCMI engine
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

class SetManaProxy : public SharedWrapper<SetMana, SetManaProxy>
{
public:
	using Wrapper = SharedWrapper<SetMana, SetManaProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	static int setHeroId(lua_State * L);
	static int setValue(lua_State * L);
	static int setMode(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
