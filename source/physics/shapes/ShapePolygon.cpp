#include "ShapePolygon.h"

#include <iostream>

FShapePolygon::FShapePolygon(const std::vector<FVector2>& InVertices) : IShape(EShapeType::Polygon), VerticesLocal(InVertices)
{
    VerticesWorld = VerticesLocal;
}

FShapePolygon::FShapePolygon(const std::vector<FVector2>& InVertices, EShapeType InShapeType) : IShape(InShapeType), VerticesLocal(InVertices)
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

float FShapePolygon::FindMinSeparation(const FShapePolygon* A, const FShapePolygon* B, FVector2& OutPoint, FVector2& OutNormal) 
{
    float MaxSeparation = std::numeric_limits<float>::lowest();

    const std::vector<FVector2>& VerticesA = A->GetVerticesWorld();
    const std::vector<FVector2>& VerticesB = B->GetVerticesWorld();

    const size_t NumVerticesA = VerticesA.size();
    const size_t NumVerticesB = VerticesB.size();

    for (size_t i = 0; i < NumVerticesA; i++) 
    {
        float MinSeparation = std::numeric_limits<float>::max();
        
        const FVector2 VertexA = VerticesA[i];
        const FVector2 NextVertexA = VerticesA[(i+1) % NumVerticesA];
        const FVector2 EdgeA = (NextVertexA - VertexA).Normalise();
        const FVector2 Normal = EdgeA.Normal();

        FVector2 MinPoint;
        FVector2 MinNormal;
        
        for (size_t j = 0; j < NumVerticesB; j++)
        {
            const FVector2 VertexB = VerticesB[j];

            const FVector2 AB = VertexB - VertexA;
            const float Separation = AB.Dot(Normal);

            if (Separation < MinSeparation) 
            {
                MinSeparation = Separation;
                MinPoint = VertexB;
                MinNormal = Normal;
            }
        }

        if (MinSeparation > MaxSeparation)
        {
            MaxSeparation = MinSeparation;
            OutPoint = MinPoint;
            OutNormal = MinNormal;
        }
    }

    return MaxSeparation;
}

float FShapePolygon::GetMomentOfIntertia() const
{
    std::cout << "FShapePolygon::GetMomentOfIntertia - not supported!" << std::endl;
    return 0.0f;
}