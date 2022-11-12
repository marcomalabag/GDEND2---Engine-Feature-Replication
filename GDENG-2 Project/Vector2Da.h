#pragma once
#include <DirectXMath.h>

struct Vector2Da final : public DirectX::XMFLOAT2
{
	Vector2Da();

	explicit Vector2Da(float x,
	                  float y);

	explicit Vector2Da(const XMFLOAT2& v);

	~Vector2Da();

	Vector2Da(const Vector2Da&) = default;

	Vector2Da& operator=(const Vector2Da& v) = default;

	Vector2Da(Vector2Da&&) noexcept = default;

	Vector2Da& operator=(Vector2Da&&) noexcept = default;

	explicit operator DirectX::XMVECTOR() const;

	bool operator ==(const Vector2Da& v) const;

	bool operator !=(const Vector2Da& v) const;

	Vector2Da& operator+=(const Vector2Da& v);

	Vector2Da& operator-=(const Vector2Da& v);

	Vector2Da& operator*=(const Vector2Da& v);

	Vector2Da& operator*=(float s);

	Vector2Da& operator/=(float s);

	Vector2Da operator+() const;

	Vector2Da operator-() const;

	[[nodiscard]]
	float length() const;

	[[nodiscard]]
	float lengthSquared() const;

	[[nodiscard]]
	float dot(const Vector2Da& v) const;

	[[nodiscard]]
	Vector2Da cross(const Vector2Da& v) const;

	void normalize();

	[[nodiscard]]
	static float distance(const Vector2Da& v1,
	                      const Vector2Da& v2);

	[[nodiscard]]
	static float distanceSquared(const Vector2Da& v1,
	                             const Vector2Da& v2);
};

Vector2Da operator+(const Vector2Da& v1,
                   const Vector2Da& v2);

Vector2Da operator-(const Vector2Da& v1,
                   const Vector2Da& v2);

Vector2Da operator*(const Vector2Da& v1,
                   const Vector2Da& v2);

Vector2Da operator*(const Vector2Da& v,
                   float s);

Vector2Da operator/(const Vector2Da& v1,
                   const Vector2Da& v2);

Vector2Da operator/(const Vector2Da& v,
                   float s);
