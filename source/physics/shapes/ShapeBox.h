#pragma once

#include "ShapePolygon.h"

class FShapeBox : public FShapePolygon 
{
public:
    FShapeBox(float Width, float Height);

private:
    float Width;
    float Height;
};
