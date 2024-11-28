#include "ShapePolygon.h"

FShapePolygon::FShapePolygon(const std::vector<FVector2>& InVertices) : IShape(EShape::Polygon), Vertices(InVertices)
{

}

FShapePolygon::FShapePolygon(const std::vector<FVector2>& InVertices, EShape Shape) : IShape(Shape), Vertices(InVertices)
{

}

const std::vector<FVector2>& FShapePolygon::GetVertices() const
{
    return Vertices;
}
