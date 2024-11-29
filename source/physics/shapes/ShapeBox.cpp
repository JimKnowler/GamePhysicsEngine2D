#include "ShapeBox.h"

FShapeBox::FShapeBox(float InWidth, float InHeight)
    : FShapePolygon({ {-InWidth/2, -InHeight/2}, {InWidth/2, -InHeight/2}, {InWidth/2, InHeight/2}, {-InWidth/2, InHeight/2} }, EShapeType::Box),
    Width(InWidth), Height(InHeight)
{

}

float FShapeBox::GetMomentOfIntertia() const
{
    return (1.0f/12.0f) * ((Width * Width) + (Height * Height));
}