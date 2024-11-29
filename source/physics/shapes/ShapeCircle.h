#pragma once

#include "physics/IShape.h"

class FShapeCircle : public IShape
{
public:
    FShapeCircle(float Radius);

    float GetRadius() const;

    // >> IShape
    virtual float GetMomentOfIntertia() const override;
    // << IShape

private:
    float Radius;
};

