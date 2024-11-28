#pragma once

#include "Vector2.h"
#include "Body.h"

struct FContact
{
    FBody* A = nullptr;
    FBody* B = nullptr;

    float Depth = 0.0f;
    FVector2 Normal = FVector2::ZeroVector;
    FVector2 Start = FVector2::ZeroVector;
    FVector2 End = FVector2::ZeroVector;
};
