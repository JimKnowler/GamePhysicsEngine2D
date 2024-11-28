#include "ShapeBox.h"

FShapeBox::FShapeBox(float InWidth, float InHeight)
 : FShapePolygon({ {-InWidth/2, -InHeight/2}, {InWidth/2, -InHeight/2}, {InWidth/2, InHeight/2}, {-InWidth/2, InHeight/2} }, EShape::Box),
   Width(InWidth), Height(InHeight)
{

}
