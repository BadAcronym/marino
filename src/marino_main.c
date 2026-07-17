#include "marino_main.h"

#define bufsize     8192
#define PATH_MAXLEN 4096

#include "pd_path.h"

f_internal void readEntries
(
    LauncherData *launcher,
    const char   *path_expanded
){
    FILE *file = fopen(path_expanded, "rb");
    if(!file)
    {
        fprintf(stderr, "\033[33;3mWARNING: could not open library data.\033[0m\n");
        return;
    }

    uint64_t entrycount = 0;

    char buf[bufsize];
    while(fgets(buf, bufsize, file))
    {
        StringView buffer;
        buffer.data = buf;
        buffer.size = bufsize;

        ++entrycount;
    }

    file = freopen(path_expanded, "r", file);
    for(uint64_t i = 0; fgets(buf, bufsize, file); ++i)
    {
        StringView buffer;
        buffer.data = buf;
        buffer.size = bufsize;

        char *namebuf = calloc(4096, 1);
        launcher->entries[i].name = cstr_sv_cpy(buf, namebuf);
        if(launcher->entries[i].name.size)
        {
            launcher->entries[i].name.size -= 1;
        }
    }
    fclose(file);

    #ifdef DEBUG
    for(uint64_t i = 0; i < entrycount; ++i)
    {
        fprintf(stderr, "found entry %lu: "PRI_SV"\n",
                i, ARG_SV(launcher->entries[i].name));
    }
    #endif
}

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

    readEntries(launcher, path_expanded);

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
