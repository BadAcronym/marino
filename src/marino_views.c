#include "marino_main.h"

extern void mrDrawDetailView
(
    EngineData   *engine,
    LauncherData *launcher
){
    rvCompositeSettings comp = {0};
    comp.pictop     = RV_PICTOP_OVER;
    comp.src        = &engine->planes[MR_PLANE_BACKGROUND];
    comp.dst        = &engine->backbuffer;
    comp.cropHeight = 3840;
    comp.cropWidth  = 2160;

    rvCompositeImage(engine, &comp);
}

extern void mrDrawCoverView
(
    EngineData   *engine,
    LauncherData *launcher
){
}

extern void mrDrawListView
(
    EngineData   *engine,
    LauncherData *launcher
){
}
