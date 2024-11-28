#include "ShapePolygon.h"

FShapePolygon::FShapePolygon(const std::vector<FVector2>& InVertices) : IShape(EShape::Polygon), VerticesLocal(InVertices)
{
    VerticesWorld = VerticesLocal;
}

FShapePolygon::FShapePolygon(const std::vector<FVector2>& InVertices, EShape Shape) : IShape(Shape), VerticesLocal(InVertices)
{
    VerticesWorld = VerticesLocal;
}

const std::vector<FVector2>& FShapePolygon::GetVerticesLocal() const
{
    return VerticesLocal;
}

const std::vector<FVector2>& FShapePolygon::GetVerticesWorld() const
{
    return VerticesWorld;
}

void FShapePolygon::UpdateWorldTransform(const FVector2& Location, const float Rotation)
{
    const size_t NumVertices = VerticesLocal.size();

    for (size_t i=0; i<NumVertices; i++) 
    {
        FVector2 v = VerticesLocal[i];
        v.Rotate(Rotation);
        v += Location;

        VerticesWorld[i] = v;
    }
}
