/*
 * BuildingBuilt.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include <vcmi/events/BuildingBuilt.h>

#include "../GameConstants.h"

VCMI_LIB_NAMESPACE_BEGIN

namespace events
{

class DLL_LINKAGE CBuildingBuilt : public BuildingBuilt
{
public:
	CBuildingBuilt();

	bool isEnabled() const override;

	PlayerColor getPlayer() const override;
	int32_t getPlayerIndex() const override;
	ObjectInstanceID getTown() const override;
	int32_t getBuilding() const override;

	PlayerColor player;
	ObjectInstanceID townId;
	int32_t buildingId = 0;
};

}

VCMI_LIB_NAMESPACE_END
