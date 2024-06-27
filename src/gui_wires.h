/*******************************************************************************************
*
*   Wires v1.0.0 - Logisim Alternaltive
*
*   MODULE USAGE:
*       #define GUI_WIRES_IMPLEMENTATION
*       #include "gui_wires.h"
*
*       INIT: GuiWiresState state = InitGuiWires();
*       DRAW: GuiWires(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 Cooper Pflaum. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_WIRES_H
#define GUI_WIRES_H

typedef struct {
    bool MENU_BOXActive;
    bool WIRE_COLOR_DROPDOWNEditMode;
    int WIRE_COLOR_DROPDOWNActive;

    Rectangle layoutRecs[3];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiWiresState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiWiresState InitGuiWires(void);
void GuiWires(GuiWiresState *state);


#ifdef __cplusplus
}
#endif

#endif // GUI_WIRES_H

/***********************************************************************************
*
*   GUI_WIRES IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_WIRES_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiWiresState InitGuiWires(void)
{
    GuiWiresState state = { 0 };

    state.MENU_BOXActive = true;
    state.WIRE_COLOR_DROPDOWNEditMode = false;
    state.WIRE_COLOR_DROPDOWNActive = 0;

    state.layoutRecs[0] = (Rectangle){ 16, 16, 376, 496 };
    state.layoutRecs[1] = (Rectangle){ 24, 80, 120, 24 };
    state.layoutRecs[2] = (Rectangle){ 24, 48, 120, 24 };

    // Custom variables initialization

    return state;
}


void GuiWires(GuiWiresState *state)
{
    const char *MENU_BOXText = "MENU";
    const char *WIRE_COLOR_DROPDOWNText = "RED;ORANGE;YELLOW;GREEN;BLUE;PURPLE;WHITE";
    const char *WIRE_COLOR_LABELText = "Wire Colors";
    
    if (state->WIRE_COLOR_DROPDOWNEditMode) GuiLock();

    if (state->MENU_BOXActive)
    {
        state->MENU_BOXActive = !GuiWindowBox(state->layoutRecs[0], MENU_BOXText);
        GuiLabel(state->layoutRecs[2], WIRE_COLOR_LABELText);
        if (GuiDropdownBox(state->layoutRecs[1], WIRE_COLOR_DROPDOWNText, &state->WIRE_COLOR_DROPDOWNActive, state->WIRE_COLOR_DROPDOWNEditMode)) state->WIRE_COLOR_DROPDOWNEditMode = !state->WIRE_COLOR_DROPDOWNEditMode;
    }
    
    GuiUnlock();
}

#endif // GUI_WIRES_IMPLEMENTATION
