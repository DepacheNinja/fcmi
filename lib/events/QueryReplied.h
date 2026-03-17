/*
 * QueryReplied.h, part of VCMI engine
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include <vcmi/events/QueryReplied.h>

#include "../GameConstants.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

class DLL_LINKAGE CQueryReplied : public QueryReplied
{
public:
	CQueryReplied();

	bool isEnabled() const override;
	int32_t getQueryId() const override;
	int32_t getReply() const override;

	int32_t queryId = -1;
	int32_t reply = 0;
};

}

VCMI_LIB_NAMESPACE_END
