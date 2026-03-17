/*
 * api/netpacks/RemoveMapObject.cpp, part of VCMI engine
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "RemoveMapObject.h"

#include "../../LuaStack.h"
#include "../../../../lib/networkPacks/PacksForClient.h"
#include "../../../../lib/constants/EntityIdentifiers.h"

#include "../Registry.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
namespace netpacks
{

VCMI_REGISTER_SCRIPT_API(RemoveMapObjectProxy, "netpacks.RemoveMapObject");

const std::vector<RemoveMapObjectProxy::CustomRegType> RemoveMapObjectProxy::REGISTER_CUSTOM =
{
	{"new", &Wrapper::constructor, true},
	{"setObjId", &RemoveMapObjectProxy::setObjId, false},
	{"toNetpackLight", &PackForClientProxy<RemoveMapObjectProxy>::toNetpackLight, false}
};

int RemoveMapObjectProxy::setObjId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<RemoveObject> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	int32_t value = -1;
	if(S.tryGet(2, value))
		object->objectID = ObjectInstanceID(value);
	return S.retVoid();
}

}
}
}

VCMI_LIB_NAMESPACE_END
