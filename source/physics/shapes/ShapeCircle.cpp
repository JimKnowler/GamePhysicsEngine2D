#include "ShapeCircle.h"

FShapeCircle::FShapeCircle(float InRadius) : IShape(EShapeType::Circle), Radius(InRadius)
{

}

float FShapeCircle::GetRadius() const
{
    return Radius;
}
