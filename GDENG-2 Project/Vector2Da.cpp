#include "Vector2Da.h"

#include "Debug.h"

Vector2Da::Vector2Da() :
	XMFLOAT2{0.0f, 0.0f}
{
}

Vector2Da::Vector2Da(const float x,
                   const float y) :
	XMFLOAT2{x, y}
{
}

Vector2Da::Vector2Da(const XMFLOAT2& v) :
	XMFLOAT2{v}
{
}

Vector2Da::~Vector2Da() = default;

Vector2Da::operator DirectX::XMVECTOR() const
{
	return XMLoadFloat2(this);
}

bool Vector2Da::operator==(const Vector2Da& v) const
{
	using namespace DirectX;
	const XMVECTOR v1 = XMLoadFloat2(this);
	const XMVECTOR v2 = XMLoadFloat2(&v);
	return XMVector2Equal(v1, v2);
}

bool Vector2Da::operator!=(const Vector2Da& v) const
{
	using namespace DirectX;
	const XMVECTOR v1 = XMLoadFloat2(this);
	const XMVECTOR v2 = XMLoadFloat2(&v);
	return XMVector2NotEqual(v1, v2);
}

Vector2Da& Vector2Da::operator+=(const Vector2Da& v)
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR v2     = XMLoadFloat2(&v);
	const XMVECTOR result = XMVectorAdd(v1, v2);
	XMStoreFloat2(this, result);
	return *this;
}

Vector2Da& Vector2Da::operator-=(const Vector2Da& v)
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR v2     = XMLoadFloat2(&v);
	const XMVECTOR result = XMVectorSubtract(v1, v2);
	XMStoreFloat2(this, result);
	return *this;
}

Vector2Da& Vector2Da::operator*=(const Vector2Da& v)
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR v2     = XMLoadFloat2(&v);
	const XMVECTOR result = XMVectorMultiply(v1, v2);
	XMStoreFloat2(this, result);
	return *this;
}

Vector2Da& Vector2Da::operator*=(const float s)
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR result = XMVectorScale(v1, s);
	XMStoreFloat2(this, result);
	return *this;
}

Vector2Da& Vector2Da::operator/=(const float s)
{
	using namespace DirectX;
	Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
	XMStoreFloat2(this, result);
	return *this;
}

Vector2Da Vector2Da::operator+() const
{
	return *this;
}

Vector2Da Vector2Da::operator-() const
{
	return Vector2Da(-x, -y);
}

Vector2Da operator+(const Vector2Da& v1,
                   const Vector2Da& v2)
{
	using namespace DirectX;
	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
	Vector2Da result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2Da operator-(const Vector2Da& v1,
                   const Vector2Da& v2)
{
	using namespace DirectX;
	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
	Vector2Da result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2Da operator*(const Vector2Da& v1,
                   const Vector2Da& v2)
{
	using namespace DirectX;
	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
	Vector2Da result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2Da operator*(const Vector2Da& v,
                   const float s)
{
	using namespace DirectX;
	const XMVECTOR tempV1     = XMLoadFloat2(&v);
	const XMVECTOR tempResult = XMVectorScale(tempV1, s);
	Vector2Da result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2Da operator/(const Vector2Da& v1,
                   const Vector2Da& v2)
{
	using namespace DirectX;
	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
	Vector2Da result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2Da operator/(const Vector2Da& v,
                   const float s)
{
	using namespace DirectX;
	Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
	const XMVECTOR v1         = XMLoadFloat2(&v);
	const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
	Vector2Da result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

float Vector2Da::length() const
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR result = XMVector2Length(v1);
	return XMVectorGetX(result);
}

float Vector2Da::lengthSquared() const
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR result = XMVector2LengthSq(v1);
	return XMVectorGetX(result);
}

float Vector2Da::dot(const Vector2Da& v) const
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR v2     = XMLoadFloat2(&v);
	const XMVECTOR result = XMVector2Dot(v1, v2);
	return XMVectorGetX(result);
}

Vector2Da Vector2Da::cross(const Vector2Da& v) const
{
	using namespace DirectX;
	const XMVECTOR v1         = XMLoadFloat2(this);
	const XMVECTOR v2         = XMLoadFloat2(&v);
	const XMVECTOR tempResult = XMVector2Cross(v1, v2);

	Vector2Da result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

void Vector2Da::normalize()
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR result = XMVector2Normalize(v1);
	XMStoreFloat2(this, result);
}

float Vector2Da::distance(const Vector2Da& v1,
                         const Vector2Da& v2)
{
	using namespace DirectX;
	const XMVECTOR x1     = XMLoadFloat2(&v1);
	const XMVECTOR x2     = XMLoadFloat2(&v2);
	const XMVECTOR net    = XMVectorSubtract(x2, x1);
	const XMVECTOR result = XMVector2Length(net);
	return XMVectorGetX(result);
}

float Vector2Da::distanceSquared(const Vector2Da& v1,
                                const Vector2Da& v2)
{
	using namespace DirectX;
	const XMVECTOR x1     = XMLoadFloat2(&v1);
	const XMVECTOR x2     = XMLoadFloat2(&v2);
	const XMVECTOR net    = XMVectorSubtract(x2, x1);
	const XMVECTOR result = XMVector2LengthSq(net);
	return XMVectorGetX(result);
}
