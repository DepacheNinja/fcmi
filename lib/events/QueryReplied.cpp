/*
 * QueryReplied.cpp, part of VCMI engine
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"

#include "QueryReplied.h"

#include <vcmi/events/EventBus.h>

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

SubscriptionRegistry<QueryReplied> * QueryReplied::getRegistry()
{
	static auto Instance = std::make_unique<SubscriptionRegistry<QueryReplied>>();
	return Instance.get();
}

void QueryReplied::defaultExecute(const EventBus * bus, int32_t queryId, int32_t reply)
{
	CQueryReplied event;
	event.queryId = queryId;
	event.reply = reply;
	bus->executeEvent(event);
}

CQueryReplied::CQueryReplied() = default;

bool CQueryReplied::isEnabled() const
{
	return true;
}

int32_t CQueryReplied::getQueryId() const
{
	return queryId;
}

int32_t CQueryReplied::getReply() const
{
	return reply;
}

}

VCMI_LIB_NAMESPACE_END
