/*
 * api/netpacks/BlockingDialog.cpp, part of VCMI engine
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "BlockingDialog.h"

#include "../../LuaStack.h"
#include "../../../../lib/networkPacks/PacksForClient.h"

#include "../Registry.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace scripting
{
namespace api
{
namespace netpacks
{

VCMI_REGISTER_SCRIPT_API(BlockingDialogProxy, "netpacks.BlockingDialog");

const std::vector<BlockingDialogProxy::CustomRegType> BlockingDialogProxy::REGISTER_CUSTOM =
{
	{"new", &BlockingDialogProxy::constructYesNo, true},
	{"setPlayer", &BlockingDialogProxy::setPlayer, false},
	{"addText", &BlockingDialogProxy::addText, false},
	{"getQueryId", &BlockingDialogProxy::getQueryId, false},
	{"toNetpackLight", &PackForClientProxy<BlockingDialogProxy>::toNetpackLight, false}
};

int BlockingDialogProxy::constructYesNo(lua_State * L)
{
	LuaStack S(L);
	S.clear();
	auto obj = std::make_shared<::BlockingDialog>(true, false);
	S.push(obj);
	return 1;
}

int BlockingDialogProxy::setPlayer(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<::BlockingDialog> object;
	if(!S.tryGet(1, object))
		return S.retVoid();
	PlayerColor value;
	if(S.tryGet(2, value))
		object->player = value;
	return S.retVoid();
}

int BlockingDialogProxy::addText(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<::BlockingDialog> object;
	if(!S.tryGet(1, object))
		return S.retVoid();

	if(lua_isstring(L, 2))
	{
		size_t len = 0;
		const auto *raw = lua_tolstring(L, 2, &len);
		std::string text(raw, len);
		object->text.appendRawString(text);
	}

	return S.retVoid();
}

int BlockingDialogProxy::getQueryId(lua_State * L)
{
	LuaStack S(L);
	std::shared_ptr<::BlockingDialog> object;
	if(!S.tryGet(1, object))
		return S.retNil();
	S.clear();
	S.push(static_cast<int32_t>(object->queryID.getNum()));
	return 1;
}

}
}
}

VCMI_LIB_NAMESPACE_END
