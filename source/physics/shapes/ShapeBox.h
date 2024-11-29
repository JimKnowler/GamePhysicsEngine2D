#pragma once

#include "ShapePolygon.h"

class FShapeBox : public FShapePolygon 
{
public:
    FShapeBox(float Width, float Height);

    // >> IShape
    virtual float GetMomentOfIntertia() const override;
    // << IShape

private:
    float Width;
    float Height;
};
