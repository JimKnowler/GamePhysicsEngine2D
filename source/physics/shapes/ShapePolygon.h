#pragma once

#include "physics/IShape.h"
#include "Vector2.h"

#include <vector>

class FShapePolygon : public IShape
{
public:
    // initialise with vertices in local space
    // NOTE: vertices assumes clockwise winding order
    FShapePolygon(const std::vector<FVector2>& Vertices);

    // Get Vertices, in local space
    const std::vector<FVector2>& GetVerticesLocal() const;

    // Get Vertices, in world space
    const std::vector<FVector2>& GetVerticesWorld() const;

    // >> IShape
    virtual void UpdateWorldTransform(const FVector2& Location, const float Rotation) override;
    // << IShape

    static float FindMinSeparation(const FShapePolygon* A, const FShapePolygon* B, FVector2& OutPoint, FVector2& OutNormal);

protected:
    FShapePolygon(const std::vector<FVector2>& Vertices, EShapeType ShapeType);

private:
    std::vector<FVector2> VerticesLocal;
    std::vector<FVector2> VerticesWorld;
};
