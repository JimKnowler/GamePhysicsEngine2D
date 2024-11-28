#pragma once

enum class EShape
{
    Circle,
    Polygon,
    Box
};

class IShape
{
public:
    IShape(EShape Shape);

    EShape GetShape() const;

private:
    EShape Shape;
};
