#pragma once

#include "physics/IShape.h"
#include "Vector2.h"

#include <vector>

class FShapePolygon : public IShape
{
public:
    FShapePolygon(const std::vector<FVector2>& Vertices);

    const std::vector<FVector2>& GetVertices() const;

protected:
    FShapePolygon(const std::vector<FVector2>& Vertices, EShape Shape);

private:
    std::vector<FVector2> Vertices;
};
