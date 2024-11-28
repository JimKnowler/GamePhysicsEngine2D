#pragma once

struct FVector2
{
    float X;
    float Y;

    const static FVector2 ZeroVector;

    FVector2& operator+=(const FVector2& Other);
    FVector2& operator-=(const FVector2& Other);
    FVector2& operator*=(const float Multiplier);
    FVector2& operator/=(const float Multiplier);

    FVector2 operator+(const FVector2& Other) const;
    FVector2 operator-(const FVector2& Other) const;
    FVector2 operator*(const float Multiplier) const;
    FVector2 operator/(const float Multiplier) const;

    // Calculate Dot Product with another 2D vector
    float Dot(const FVector2& Other) const;

    // Rotate vector around the origin
    FVector2& Rotate(const float Radians);

    // Calculate the length of this vector
    float Length() const;

    // Calculate the length squared of this vector
    float LengthSq() const;

    // Normalise this vector
    FVector2& Normalise();

    // TODO:
    // CrossProduct -> 2D, generates a scalar 
};
