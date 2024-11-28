#pragma once

#include "physics/IShape.h"

class FShapeCircle : public IShape
{
public:
    FShapeCircle(float Radius);

    float GetRadius() const;

private:
    float Radius;
};

