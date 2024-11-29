#pragma once

#include "Contact.h"

struct FCollisionResolution
{
    static void ResolveCollision(const FContact& Contact);

private:
    static void ResolveCollisionProjectionMethod(const FContact& Contact);
    static void ResolveCollisionImpulseMethod(const FContact& Contact);
};
