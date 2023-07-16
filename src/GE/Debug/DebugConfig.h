﻿#pragma once

#define DEBUG_IS_ACTIVE_WHEN_RELEASE	0

#define DEBUG_CONSOLE_LOGGING			1
#define DEBUG_COLLIDER_VISUAL			0
#define DEBUG_MEASUREMENT				1

#define DEBUG_IS_ENABLED(feature) (_DEBUG || DEBUG_IS_ACTIVE_WHEN_RELEASE) && feature
