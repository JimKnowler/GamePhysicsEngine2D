#pragma once

#include "Contact.h"

struct FCollisionDetection
{
    // Detect whether bodies A and B are colliding
    // @param OutContact Contact information for collision between A & B (if colliding)
    // @return true if colliding
    static bool DetectCollision(FBody* A, FBody* B, FContact& OutContact);
};
