#include "Color.h"

#include "Vector3D.h"

Color::Color() :
	XMFLOAT4{0.0f, 0.0f, 0.0f, 1.0f}
{
}

Color::Color(const float red,
             const float green,
             const float blue) :
	XMFLOAT4{red, green, blue, 1.0f}
{
}

Color::Color(const float red,
             const float green,
             const float blue,
             const float alpha) :
	XMFLOAT4{red, green, blue, alpha}
{
}

Color::Color(const Vector3D& rgbColor) :
	XMFLOAT4{rgbColor.x, rgbColor.y, rgbColor.z, 1.0f}
{
}

Color::Color(const XMFLOAT4& rgbaColor) :
	XMFLOAT4{rgbaColor.x, rgbaColor.y, rgbaColor.z, rgbaColor.w}
{
}

Color::operator DirectX::XMVECTOR() const
{
	return XMLoadFloat4(this);
}

bool Color::operator==(const Color& c) const
{
	using namespace DirectX;
	const XMVECTOR c1 = XMLoadFloat4(this);
	const XMVECTOR c2 = XMLoadFloat4(&c);
	return XMColorEqual(c1, c2);
}

bool Color::operator!=(const Color& c) const
{
	using namespace DirectX;
	const XMVECTOR c1 = XMLoadFloat4(this);
	const XMVECTOR c2 = XMLoadFloat4(&c);
	return XMColorNotEqual(c1, c2);
}

Color& Color::operator+=(const Color& c)
{
	using namespace DirectX;
	const XMVECTOR c1 = XMLoadFloat4(this);
	const XMVECTOR c2 = XMLoadFloat4(&c);
	XMStoreFloat4(this, XMVectorAdd(c1, c2));
	return *this;
}

Color& Color::operator-=(const Color& c)
{
	using namespace DirectX;
	const XMVECTOR c1 = XMLoadFloat4(this);
	const XMVECTOR c2 = XMLoadFloat4(&c);
	XMStoreFloat4(this, XMVectorSubtract(c1, c2));
	return *this;
}

Color& Color::operator*=(const Color& c)
{
	using namespace DirectX;
	const XMVECTOR c1 = XMLoadFloat4(this);
	const XMVECTOR c2 = XMLoadFloat4(&c);
	XMStoreFloat4(this, XMVectorMultiply(c1, c2));
	return *this;
}

Color& Color::operator*=(const float s)
{
	using namespace DirectX;
	const XMVECTOR c = XMLoadFloat4(this);
	XMStoreFloat4(this, XMVectorScale(c, s));
	return *this;
}

Color& Color::operator/=(const Color& c)
{
	using namespace DirectX;
	const XMVECTOR c1 = XMLoadFloat4(this);
	const XMVECTOR c2 = XMLoadFloat4(&c);
	XMStoreFloat4(this, XMVectorDivide(c1, c2));
	return *this;
}

Color Color::operator-() const
{
	using namespace DirectX;
	const XMVECTOR c = XMLoadFloat4(this);
	Color result;
	XMStoreFloat4(&result, XMVectorNegate(c));
	return result;
}

float Color::red() const
{
	return x;
}

void Color::red(float red)
{
	x = red;
}

float Color::green() const
{
	return y;
}

void Color::green(float green)
{
	y = green;
}

float Color::blue() const
{
	return z;
}

void Color::blue(float blue)
{
	z = blue;
}

float Color::alpha() const
{
	return w;
}

void Color::alpha(float alpha)
{
	w = alpha;
}

Color Color::lerp(const Color& c1,
                  const Color& c2,
                  const float t) noexcept
{
	using namespace DirectX;
	const XMVECTOR tempC1 = XMLoadFloat4(&c1);
	const XMVECTOR tempC2 = XMLoadFloat4(&c2);

	Color result;
	XMStoreFloat4(&result, XMVectorLerp(tempC1, tempC2, t));
	return result;
}

Color operator+(const Color& c1,
                const Color& c2) noexcept
{
	using namespace DirectX;
	const XMVECTOR tempC1 = XMLoadFloat4(&c1);
	const XMVECTOR tempC2 = XMLoadFloat4(&c2);
	Color result;
	XMStoreFloat4(&result, XMVectorAdd(tempC1, tempC2));
	return result;
}

Color operator-(const Color& c1,
                const Color& c2) noexcept
{
	using namespace DirectX;
	const XMVECTOR tempC1 = XMLoadFloat4(&c1);
	const XMVECTOR tempC2 = XMLoadFloat4(&c2);
	Color result;
	XMStoreFloat4(&result, XMVectorSubtract(tempC1, tempC2));
	return result;
}

Color operator*(const Color& c1,
                const Color& c2) noexcept
{
	using namespace DirectX;
	const XMVECTOR tempC1 = XMLoadFloat4(&c1);
	const XMVECTOR tempC2 = XMLoadFloat4(&c2);
	Color result;
	XMStoreFloat4(&result, XMVectorMultiply(tempC1, tempC2));
	return result;
}

Color operator*(const Color& c,
                const float s) noexcept
{
	using namespace DirectX;
	const XMVECTOR tempColor = XMLoadFloat4(&c);
	Color result;
	XMStoreFloat4(&result, XMVectorScale(tempColor, s));
	return result;
}

Color operator/(const Color& c1,
                const Color& c2) noexcept
{
	using namespace DirectX;
	const XMVECTOR tempC1 = XMLoadFloat4(&c1);
	const XMVECTOR tempC2 = XMLoadFloat4(&c2);
	Color result;
	XMStoreFloat4(&result, XMVectorDivide(tempC1, tempC2));
	return result;
}
