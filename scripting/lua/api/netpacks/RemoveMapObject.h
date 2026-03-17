/*
 * api/netpacks/RemoveMapObject.h, part of VCMI engine
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

// Wraps RemoveObject — removes a map object by ObjectInstanceID.
// Usage in Lua:
//   local pack = RemoveMapObject.new()
//   pack:setObjId(objectId)   -- ObjectInstanceID integer
//   SERVER:commitPackage(pack)
class RemoveMapObjectProxy : public SharedWrapper<RemoveObject, RemoveMapObjectProxy>
{
public:
	using Wrapper = SharedWrapper<RemoveObject, RemoveMapObjectProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	static int setObjId(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
