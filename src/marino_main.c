#include "marino_main.h"

#define bufsize     8192
#define PATH_MAXLEN 4096

#include "pd_path.h"

void mrInit
(
    EngineData   *engine,
    LauncherData *launcher
){
    rvCreateImage(engine, &engine->planes[MR_PLANE_BACKGROUND], 3840, 2160);
    for(uint64_t i = 0; i < 3840 * 2160; ++i)
    {
        ((uint32_t*)engine->planes[MR_PLANE_BACKGROUND].data)[i] = 0xFF05051F;
    }
    rvSyncImage(engine, &engine->planes[MR_PLANE_BACKGROUND], true);

    char path_expanded[PATH_MAXLEN];
    pdExpandPath(GAMES_LOCAL, path_expanded);

    FILE *file = fopen(path_expanded, "r");
    if(!file)
    {
        fprintf(stderr, "\033[33;3mWARNING: could not open game list."
                "\033[0m\n");
    }

    char buf[bufsize];
    while(fgets(buf, bufsize, file))
    {
        StringView buffer;
        buffer.data = buf;
        buffer.size = bufsize;

        StringView comment_sv  = cstr_sv("//");
        const char *commentloc = sv_find(comment_sv, buffer);
        if(commentloc == buf)
        {
            continue;
        }

        printf(PRI_SV"\n", ARG_SV(buffer));
    }

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
