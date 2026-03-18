/*
 * Environment.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#include "StdInc.h"

#include "../include/vcmi/Environment.h"

VCMI_LIB_NAMESPACE_BEGIN

// Out-of-line definitions for Environment's constructor and virtual destructor.
// Required for MSVC ARM64: __declspec(dllexport) on a class with defaulted special
// members in the header does not emit exported symbols on ARM64, causing LNK2019
// in consumers (e.g. BattleAI.dll) that dllimport them.
Environment::Environment() = default;
Environment::~Environment() = default;

VCMI_LIB_NAMESPACE_END
