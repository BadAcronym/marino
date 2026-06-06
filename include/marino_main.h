#pragma once

#include "river2D_main.h"
#include "string_view.h"

typedef struct GameData
{
    uint32_t   UID;
    StringView name;
    RiverImage *icon;
    RiverImage *cover;
    RiverImage *background;
    StringView description;
}
GameData;

typedef struct LauncherData
{
    GameData  *games;
    RiverTime lastPresentTime;
    uint32_t  viewScroll;
    uint32_t  maxScroll;
    uint16_t  runningFrames;
}
LauncherData;

extern void marino_init
(
    EngineData   *engine,
    LauncherData *launcher
);

extern int32_t marino_shutdown
(
    LauncherData *launcher
);

extern void marino_processKeys
(
    RiverControls *controls,
    AsciiKey      ascii,
    bool          down
);

extern void marino_processButtons
(
    LauncherData  *launcher,
    RiverControls *controls,
    uint32_t      button,
    bool          down
);

extern void marino_processPointer
(
    EngineData *engine,
    uint32_t   x,
    uint32_t   y
);

extern void marino_scroll
(
    LauncherData *launcher,
    bool         down
);

extern void marino_update
(
    EngineData   *engine,
    LauncherData *launcher
);

extern void marino_present
(
    EngineData   *engine,
    LauncherData *launcher
);
