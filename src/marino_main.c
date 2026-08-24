#include "marino_main.h"

#define bufsize  8192
#define MAX_PATH 4096

#include "pd_path.h"

f_internal void readEntries
(
    LauncherData *launcher,
    const char   *path_expanded
){
    const char header[5] = "mari";

    FILE *file = fopen(path_expanded, "rb");
    if(!file)
    {
        fprintf(stderr, "\033[33;3mWARNING: could not open library data.\033[0m\n");
        return;
    }

    int byte;
    for(uint8_t i = 0; i < 4 && ((byte = fgetc(file)) != EOF); ++i)
    {
        if(byte != header[i])
        {
            fprintf(stderr, "\033[31;1;7mERROR: failed to validate header.\033[0m\n");
        }
    }

    uint64_t entrycount = 0;
    size_t   elements   = 0;

    if((elements = fread(&entrycount, 8, 1, file)) != 1)
    {
        fprintf(stderr, "\033[31;1;7mERROR: failed to read entrycount.\033[0m\n");
        return;
    }

    for(uint64_t i = 0; i < entrycount; ++i)
    {
        EntryData entry = {0};

        if((elements = fread(&entry, sizeof(EntryData), 1, file)) != 1)
        {
            fprintf(stderr, "\033[31;1;7mERROR: failed to read entry %lu."
                    "\033[0m\n", i);
            return;
        }
        #ifdef DEBUG
            fprintf(stderr, "read entry %lu: " PRI_SV "\n", i, ARG_SV(entry.name));
        #endif
    }
    fclose(file);
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

    StringView localdb = cstr_sv(GAMES_LOCAL);
    char path_expanded[MAX_PATH];
    pdExpandPath(localdb, path_expanded);

    readEntries(launcher, path_expanded);

    engine->controls.keycodes[MR_KEY_NEWENTRY] = 'n';

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
