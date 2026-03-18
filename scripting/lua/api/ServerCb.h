/*
 * ServerCb.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include <vcmi/ServerCallback.h>

#include "../LuaWrapper.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{

class ServerCbProxy : public OpaqueWrapper<ServerCallback, ServerCbProxy>
{
public:
	using Wrapper = OpaqueWrapper<ServerCallback, ServerCbProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	template<typename NetPack>
	static int apply(lua_State * L);
	static int commitPackage(lua_State * L);
	// FCMI: SERVER:spawnObject(scope, type, subtype, x, y, z [, initiator])
	// Places a mod-registered map object at tile (x, y, z) on the current map.
	// scope/type/subtype are mod identifier strings, e.g. "wog-newage.objects", "wogArtificer", "wogArtificer"
	// initiator is an optional player index (default 255 = neutral/system)
	static int spawnObject(lua_State * L);
};

}
}

VCMI_LIB_NAMESPACE_END
