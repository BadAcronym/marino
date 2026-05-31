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
    GameData *games;
}
LauncherData;
