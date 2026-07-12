#include "marino_main.h"

void mrProcessKeys
(
    RiverControls *controls,
    AsciiKey      key,
    bool          down
){
    if(down)
    {
        controls->ascii = (char)key.raw;
        if(controls->ascii < 0x20 || controls->ascii > 0x7E)
        {
            controls->ascii = 0x00;
        }
    }

}

void mrProcessButtons
(
    LauncherData  *launcher,
    RiverControls *controls,
    uint32_t      button,
    bool          down
){
}

void mrProcessPointer
(
    EngineData *engine,
    uint32_t   x,
    uint32_t   y
){
    Dimensions dim = rvGetWindowSize(engine);

    if(x > dim.width)
    {
        x = dim.width;
    }
    if(y > dim.height)
    {
        y = dim.height;
    }

    engine->controls.pointer.x = (float)x / (float)dim.width;
    engine->controls.pointer.y = (float)y / (float)dim.height;
}

void mrScroll
(
    LauncherData *launcher,
    bool         down
){
    if(down && launcher->scroll < launcher->maxScroll)
    {
        ++launcher->scroll;
    }
    else if(launcher->scroll)
    {
        --launcher->scroll;
    }
}
