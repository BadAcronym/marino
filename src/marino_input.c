#include "marino_main.h"

void mrProcessButtons
(
    LauncherData  *launcher,
    RiverControls *controls,
    uint32_t      button,
    bool          down
){
}

f_internal void processKey_function
(
    RiverControls *controls,
    uint8_t       desired,
    AsciiKey      key,
    uint64_t      bit,
    bool          isDown
){
    if(isDown && key.key == controls->keycodes[desired])
    {
        controls->keymap |= bit;
        return;
    }

    if(key.key == controls->keycodes[desired])
    {
        controls->keymap &= ~bit;
    }
}

#define processKey(kmacro, bitmacro) \
processKey_function(controls, kmacro, key, bitmacro, down)

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

    processKey(MR_KEY_NEWENTRY, MR_BIT_NEWENTRY);
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
