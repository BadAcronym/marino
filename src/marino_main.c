#include "marino_main.h"

void marino_init
(
    EngineData   *engine,
    LauncherData *launcher
){
    launcher->maxScroll = UINT32_MAX;
}

int32_t marino_shutdown
(
    LauncherData *launcher
){

    return 0;
}

void marino_update
(
    EngineData   *engine,
    LauncherData *launcher
){

    ++launcher->runningFrames;
}

void marino_present
(
    EngineData   *engine,
    LauncherData *launcher
){
    rvBltBuffer(engine);
    launcher->lastPresentTime = rvQueryTime();
}
