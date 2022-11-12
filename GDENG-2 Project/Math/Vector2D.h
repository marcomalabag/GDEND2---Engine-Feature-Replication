#pragma once
#include <DirectXMath.h>

struct Vector2D final : DirectX::XMFLOAT2
{
	Vector2D();
	explicit Vector2D(float x,
	                  float y);
	explicit Vector2D(const XMFLOAT2& v);

	~Vector2D();

	Vector2D(const Vector2D&)                = default;
	Vector2D& operator=(const Vector2D& v)   = default;
	Vector2D(Vector2D&&) noexcept            = default;
	Vector2D& operator=(Vector2D&&) noexcept = default;

	explicit operator DirectX::XMVECTOR() const;

	bool operator ==(const Vector2D& v) const;

	bool operator !=(const Vector2D& v) const;

	Vector2D& operator+=(const Vector2D& v);

	Vector2D& operator-=(const Vector2D& v);

	Vector2D& operator*=(const Vector2D& v);

	Vector2D& operator*=(float s);

	Vector2D& operator/=(float s);

	Vector2D operator+() const;

	Vector2D operator-() const;

	[[nodiscard]]
	float length() const;

	[[nodiscard]]
	float lengthSquared() const;

	[[nodiscard]]
	float dot(const Vector2D& v) const;

	[[nodiscard]]
	Vector2D cross(const Vector2D& v) const;

	Vector2D normalize() const;

	[[nodiscard]]
	static float distance(const Vector2D& v1,
	                      const Vector2D& v2);

	[[nodiscard]]
	static float distanceSquared(const Vector2D& v1,
	                             const Vector2D& v2);
};

Vector2D operator+(const Vector2D& v1,
                   const Vector2D& v2);

Vector2D operator-(const Vector2D& v1,
                   const Vector2D& v2);

Vector2D operator*(const Vector2D& v1,
                   const Vector2D& v2);

Vector2D operator*(const Vector2D& v,
                   float s);

Vector2D operator/(const Vector2D& v1,
                   const Vector2D& v2);

Vector2D operator/(const Vector2D& v,
                   float s);
