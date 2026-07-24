#pragma once

#include "river2D_main.h"
#include "string_view.h"

#define GAMES_LOCAL "marino_entries"

#define MR_VIEW_DETAIL 0
#define MR_VIEW_COVER  1
#define MR_VIEW_LIST   2

#define MR_PLANE_BACKGROUND 0

typedef struct EntryData
{
    uint32_t   UID;
    uint32_t   flags;
    RiverImage *icon;
    RiverImage *cover;
    RiverImage *background;
    StringView name;
    StringView description;
}
EntryData;

typedef struct LauncherData
{
    EntryData *entries;
    RiverTime lastPresentTime;
    uint32_t  scroll;
    uint32_t  maxScroll;
    uint16_t  runningFrames;
    uint8_t   view;
}
LauncherData;

extern void mrInit
(
    EngineData   *engine,
    LauncherData *launcher
);

extern int32_t mrShutdown
(
    LauncherData *launcher
);

extern void mrProcessKeys
(
    RiverControls *controls,
    AsciiKey      ascii,
    bool          down
);

extern void mrProcessButtons
(
    LauncherData  *launcher,
    RiverControls *controls,
    uint32_t      button,
    bool          down
);

extern void mrProcessPointer
(
    EngineData *engine,
    uint32_t   x,
    uint32_t   y
);

extern void mrScroll
(
    LauncherData *launcher,
    bool         down
);

extern void mrUpdate
(
    EngineData   *engine,
    LauncherData *launcher
);

extern void mrPresent
(
    EngineData   *engine,
    LauncherData *launcher
);

extern void mrDrawDetailView
(
    EngineData   *engine,
    LauncherData *launcher
);

extern void mrDrawCoverView
(
    EngineData   *engine,
    LauncherData *launcher
);

extern void mrDrawListView
(
    EngineData   *engine,
    LauncherData *launcher
);
