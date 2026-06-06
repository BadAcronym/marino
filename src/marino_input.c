#include "marino_main.h"

void marino_processKeys
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

void marino_processButtons
(
    LauncherData  *launcher,
    RiverControls *controls,
    uint32_t      button,
    bool          down
){
}

void marino_processPointer
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

void marino_scroll
(
    LauncherData *launcher,
    bool         down
){
    if(down && launcher->viewScroll < launcher->maxScroll)
    {
        ++launcher->viewScroll;
    }
    else if(launcher->viewScroll)
    {
        --launcher->viewScroll;
    }
}
