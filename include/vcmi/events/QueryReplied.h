/*
 * QueryReplied.h, part of VCMI engine
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "Event.h"
#include "SubscriptionRegistry.h"

VCMI_LIB_NAMESPACE_BEGIN

class QueryID;

namespace events
{

// FCMI: QueryReplied event — fires when the server receives a QueryReply from a player.
// Carries the query ID and the player's reply (0=cancel/no, 1=yes/ok, or component index).
class DLL_LINKAGE QueryReplied : public Event
{
public:
	using Sub = SubscriptionRegistry<QueryReplied>;
	using PreHandler = Sub::PreHandler;
	using PostHandler = Sub::PostHandler;
	using ExecHandler = Sub::ExecHandler;

	static Sub * getRegistry();
	static void defaultExecute(const EventBus * bus, int32_t queryId, int32_t reply);

	virtual int32_t getQueryId() const = 0;
	virtual int32_t getReply() const = 0;

	friend class SubscriptionRegistry<QueryReplied>;
};

}

VCMI_LIB_NAMESPACE_END
