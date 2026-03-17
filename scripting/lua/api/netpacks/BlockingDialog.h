/*
 * api/netpacks/BlockingDialog.h, part of VCMI engine
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

// Wraps BlockingDialog — shows a yes/no dialog to a player and assigns a query ID.
// Usage in Lua:
//   local pack = BlockingDialog.new()
//   pack:setPlayer(playerIdx)
//   pack:addText("Do you want to proceed?")
//   local qid = pack:getQueryId()
//   SERVER:commitPackage(pack)
//   -- later handle events.QueryReplied with matching qid
class BlockingDialogProxy : public SharedWrapper<::BlockingDialog, BlockingDialogProxy>
{
public:
	using Wrapper = SharedWrapper<::BlockingDialog, BlockingDialogProxy>;

	static const std::vector<typename Wrapper::CustomRegType> REGISTER_CUSTOM;

	static int constructYesNo(lua_State * L);
	static int setPlayer(lua_State * L);
	static int addText(lua_State * L);
	static int getQueryId(lua_State * L);
};

}
}
}

VCMI_LIB_NAMESPACE_END
