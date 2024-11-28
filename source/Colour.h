#pragma once

#include <stdint.h>

struct FColour 
{
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;
    uint8_t A = 255;

    static FColour Red;
    static FColour Green;
    static FColour Blue;
    static FColour Yellow;
    static FColour Purple;
    static FColour Black;
    static FColour White;
};
