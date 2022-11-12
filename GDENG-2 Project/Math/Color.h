#pragma once
#include <DirectXMath.h>

class Vector3D;
struct Color final : DirectX::XMFLOAT4
{
	explicit Color();

	explicit Color(float red,
				   float green,
				   float blue);

	explicit Color(float red,
				   float green,
				   float blue,
				   float alpha);

	explicit Color(const Vector3D& rgbColor);

	explicit Color(const XMFLOAT4& rgbaColor);

	Color(const Color&) = default;

	Color& operator=(const Color&) = default;

	Color(Color&&) = default;

	Color& operator=(Color&&) = default;

	explicit operator DirectX::XMVECTOR() const;

	explicit operator const float*() const noexcept { return reinterpret_cast<const float*>(this); }

	bool operator ==(const Color& c) const;

	bool operator !=(const Color& c) const;

	Color& operator+=(const Color& c);

	Color& operator-=(const Color& c);

	Color& operator*=(const Color& c);

	Color& operator*=(float s);

	Color& operator/=(const Color& c);

	Color operator+() const
	{
		return *this;
	}

	Color operator-() const;

	[[nodiscard]]
	float red() const;

	void red(float red);

	[[nodiscard]]
	float green() const;

	void green(float green);

	[[nodiscard]]
	float blue() const;

	void blue(float blue);

	[[nodiscard]]
	float alpha() const;

	void alpha(float alpha);

	static Color lerp(const Color& c1,
					  const Color& c2,
					  float t) noexcept;
};

Color operator+(const Color& c1,
				const Color& c2) noexcept;

Color operator-(const Color& c1,
				const Color& c2) noexcept;

Color operator*(const Color& c1,
				const Color& c2) noexcept;

Color operator*(const Color& c,
				float s) noexcept;

Color operator/(const Color& c1,
				const Color& c2) noexcept;