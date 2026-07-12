#include "marino_main.h"

void mrInit
(
    EngineData   *engine,
    LauncherData *launcher
){
    launcher->maxScroll = UINT32_MAX;
}

int32_t mrShutdown
(
    LauncherData *launcher
){
    return 0;
}

void mrUpdate
(
    EngineData   *engine,
    LauncherData *launcher
){
    if(launcher->view == MR_VIEW_DETAIL)
    {
        mrDrawDetailView(engine, launcher);
    }
    else if(launcher->view == MR_VIEW_COVER)
    {
        mrDrawCoverView(engine, launcher);
    }
    else if(launcher->view == MR_VIEW_LIST)
    {
        mrDrawListView(engine, launcher);
    }
    else
    {
        fprintf(stderr, "\033[31;1;7mERROR: invalid view: %u\033[0m\n",
                launcher->view);
    }

    ++launcher->runningFrames;
}

void mrPresent
(
    EngineData   *engine,
    LauncherData *launcher
){
    rvBltBuffer(engine);
    launcher->lastPresentTime = rvQueryTime();
}
