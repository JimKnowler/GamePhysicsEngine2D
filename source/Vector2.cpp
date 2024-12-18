#include "Vector2.h"

#include <math.h>

const FVector2 FVector2::ZeroVector = {
    .X = 0.0f,
    .Y = 0.0f
};

FVector2& FVector2::operator+=(const FVector2& Other)
{
    X += Other.X;
    Y += Other.Y;

    return *this;
}

FVector2& FVector2::operator-=(const FVector2& Other)
{
    X -= Other.X;
    Y -= Other.Y;

    return *this;
}

FVector2& FVector2::operator*=(const float Multiplier)
{
    X *= Multiplier;
    Y *= Multiplier;

    return *this;
}

FVector2& FVector2::operator/=(const float Multiplier)
{
    X /= Multiplier;
    Y /= Multiplier;

    return *this;
}

FVector2 FVector2::operator+(const FVector2& Other) const
{
    FVector2 Result = {
        .X = X + Other.X,
        .Y = Y + Other.Y
    };

    return Result;
}

FVector2 FVector2::operator-(const FVector2& Other) const
{
    FVector2 Result = {
        .X = X - Other.X,
        .Y = Y - Other.Y
    };

    return Result;
}

FVector2 FVector2::operator*(const float Multiplier) const
{
    FVector2 Result = {
        .X = X * Multiplier,
        .Y = Y * Multiplier
    };

    return Result;
}

FVector2 FVector2::operator/(const float Multiplier) const
{
    FVector2 Result = {
        .X = X / Multiplier,
        .Y = Y / Multiplier
    };

    return Result;
}

FVector2 FVector2::operator-() const 
{
    FVector2 Result = *this * -1.0f;

    return Result;
}

float FVector2::Dot(const FVector2& Other) const
{
    return (X * Other.X) + (Y * Other.Y);
}

float FVector2::Cross(const FVector2& Other) const
{
    return (X * Other.Y) - (Y * Other.X);
}

FVector2& FVector2::Rotate(const float Radians)
{
    const float Sin = sinf(Radians);
    const float Cos = cosf(Radians);

    *this = {
        .X = (Cos * X) - (Sin * Y),
        .Y = (Sin * X) + (Cos * Y)
    };

    return *this;
}

float FVector2::Length() const
{
    const float LenSq = Dot(*this);
    const float Len = sqrtf(LenSq);
    
    return Len;
}

float FVector2::LengthSq() const 
{
    float LenSq = Dot(*this);

    return LenSq;
}

FVector2& FVector2::Normalise()
{
    const float Len = Length();
    if (Len > 0.0f) 
    {
        *this /= Len;
    }

    return *this;
}

FVector2 FVector2::Normal() const 
{
    FVector2 N = {
        .X = Y,
        .Y = -X
    };

    return N;
}
