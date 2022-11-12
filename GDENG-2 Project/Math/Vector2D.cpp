#include "Vector2D.h"

#include "Debug.h"

Vector2D::Vector2D() :
	XMFLOAT2{0.0f, 0.0f}
{
}

Vector2D::Vector2D(const float x,
                   const float y) :
	XMFLOAT2{x, y}
{
}

Vector2D::Vector2D(const XMFLOAT2& v) :
	XMFLOAT2{v}
{
}

Vector2D::~Vector2D() = default;

Vector2D::operator DirectX::XMVECTOR() const
{
	return XMLoadFloat2(this);
}

bool Vector2D::operator==(const Vector2D& v) const
{
	using namespace DirectX;
	const XMVECTOR v1 = XMLoadFloat2(this);
	const XMVECTOR v2 = XMLoadFloat2(&v);
	return XMVector2Equal(v1, v2);
}

bool Vector2D::operator!=(const Vector2D& v) const
{
	using namespace DirectX;
	const XMVECTOR v1 = XMLoadFloat2(this);
	const XMVECTOR v2 = XMLoadFloat2(&v);
	return XMVector2NotEqual(v1, v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& v)
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR v2     = XMLoadFloat2(&v);
	const XMVECTOR result = XMVectorAdd(v1, v2);
	XMStoreFloat2(this, result);
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& v)
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR v2     = XMLoadFloat2(&v);
	const XMVECTOR result = XMVectorSubtract(v1, v2);
	XMStoreFloat2(this, result);
	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& v)
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR v2     = XMLoadFloat2(&v);
	const XMVECTOR result = XMVectorMultiply(v1, v2);
	XMStoreFloat2(this, result);
	return *this;
}

Vector2D& Vector2D::operator*=(const float s)
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR result = XMVectorScale(v1, s);
	XMStoreFloat2(this, result);
	return *this;
}

Vector2D& Vector2D::operator/=(const float s)
{
	using namespace DirectX;
	Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR result = XMVectorScale(v1, 1.0f / s);
	XMStoreFloat2(this, result);
	return *this;
}

Vector2D Vector2D::operator+() const
{
	return *this;
}

Vector2D Vector2D::operator-() const
{
	return Vector2D(-x, -y);
}

Vector2D operator+(const Vector2D& v1,
                   const Vector2D& v2)
{
	using namespace DirectX;
	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	const XMVECTOR tempResult = XMVectorAdd(tempV1, tempV2);
	Vector2D result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2D operator-(const Vector2D& v1,
                   const Vector2D& v2)
{
	using namespace DirectX;
	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	const XMVECTOR tempResult = XMVectorSubtract(tempV1, tempV2);
	Vector2D result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2D operator*(const Vector2D& v1,
                   const Vector2D& v2)
{
	using namespace DirectX;
	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	const XMVECTOR tempResult = XMVectorMultiply(tempV1, tempV2);
	Vector2D result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2D operator*(const Vector2D& v,
                   const float s)
{
	using namespace DirectX;
	const XMVECTOR tempV1     = XMLoadFloat2(&v);
	const XMVECTOR tempResult = XMVectorScale(tempV1, s);
	Vector2D result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2D operator/(const Vector2D& v1,
                   const Vector2D& v2)
{
	using namespace DirectX;
	const XMVECTOR tempV1     = XMLoadFloat2(&v1);
	const XMVECTOR tempV2     = XMLoadFloat2(&v2);
	const XMVECTOR tempResult = XMVectorDivide(tempV1, tempV2);
	Vector2D result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2D operator/(const Vector2D& v,
                   const float s)
{
	using namespace DirectX;
	Debug::Assert(s != 0.0f, "Attempting to divide by 0!");
	const XMVECTOR v1         = XMLoadFloat2(&v);
	const XMVECTOR tempResult = XMVectorScale(v1, 1.0f / s);
	Vector2D result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

float Vector2D::length() const
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR result = XMVector2Length(v1);
	return XMVectorGetX(result);
}

float Vector2D::lengthSquared() const
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR result = XMVector2LengthSq(v1);
	return XMVectorGetX(result);
}

float Vector2D::dot(const Vector2D& v) const
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR v2     = XMLoadFloat2(&v);
	const XMVECTOR result = XMVector2Dot(v1, v2);
	return XMVectorGetX(result);
}

Vector2D Vector2D::cross(const Vector2D& v) const
{
	using namespace DirectX;
	const XMVECTOR v1         = XMLoadFloat2(this);
	const XMVECTOR v2         = XMLoadFloat2(&v);
	const XMVECTOR tempResult = XMVector2Cross(v1, v2);

	Vector2D result;
	XMStoreFloat2(&result, tempResult);
	return result;
}

Vector2D Vector2D::normalize() const
{
	using namespace DirectX;
	const XMVECTOR v1     = XMLoadFloat2(this);
	const XMVECTOR normalized = XMVector2Normalize(v1);

	Vector2D result;
	XMStoreFloat2(&result, normalized);
	return result;
}

float Vector2D::distance(const Vector2D& v1,
                         const Vector2D& v2)
{
	using namespace DirectX;
	const XMVECTOR x1     = XMLoadFloat2(&v1);
	const XMVECTOR x2     = XMLoadFloat2(&v2);
	const XMVECTOR net    = XMVectorSubtract(x2, x1);
	const XMVECTOR result = XMVector2Length(net);
	return XMVectorGetX(result);
}

float Vector2D::distanceSquared(const Vector2D& v1,
                                const Vector2D& v2)
{
	using namespace DirectX;
	const XMVECTOR x1     = XMLoadFloat2(&v1);
	const XMVECTOR x2     = XMLoadFloat2(&v2);
	const XMVECTOR net    = XMVectorSubtract(x2, x1);
	const XMVECTOR result = XMVector2LengthSq(net);
	return XMVectorGetX(result);
}
