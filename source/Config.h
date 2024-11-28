#pragma once

#include "Colour.h"

struct FConfig 
{
    const char* AppName = "Application";

    FColour BackgroundColour = FColour::Black;
    
    int WindowWidth = 1280;
    
    int WindowHeight = 720;
};
