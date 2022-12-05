#pragma once

namespace Engine
{
	struct Matrix4;
	struct Quaternion : public DirectX::XMFLOAT4
	{
		Quaternion() noexcept :
			XMFLOAT4(0, 0, 0, 1.f) {}
		constexpr Quaternion(float ix, float iy, float iz, float iw) noexcept :
			XMFLOAT4(ix, iy, iz, iw) {}
		Quaternion(const Vector3Float& v, float scalar) noexcept :
			XMFLOAT4(v.x, v.y, v.z, scalar) {}
		explicit Quaternion(_In_reads_(4) const float* pArray) noexcept :
			XMFLOAT4(pArray) {}
		
		Quaternion(const XMFLOAT4& q) noexcept
		{
			this->x = q.x;
			this->y = q.y;
			this->z = q.z;
			this->w = q.w;
		}

		Quaternion(const Quaternion&)            = default;
		Quaternion& operator=(const Quaternion&) = default;

		Quaternion(Quaternion&&)            = default;
		Quaternion& operator=(Quaternion&&) = default;

		operator DirectX::XMVECTOR() const noexcept { return XMLoadFloat4(this); }

		// Comparison operators
		bool operator ==(const Quaternion& q) const noexcept;
		bool operator !=(const Quaternion& q) const noexcept;

		// Assignment operators
		Quaternion& operator+=(const Quaternion& q) noexcept;
		Quaternion& operator-=(const Quaternion& q) noexcept;
		Quaternion& operator*=(const Quaternion& q) noexcept;
		Quaternion& operator*=(float S) noexcept;
		Quaternion& operator/=(const Quaternion& q) noexcept;

		// Unary operators
		Quaternion operator+() const noexcept { return *this; }
		Quaternion operator-() const noexcept;

		// Quaternion operations
		float Length() const noexcept;
		float LengthSquared() const noexcept;

		void Normalize() noexcept;

		void Conjugate() noexcept;

		void Inverse(Quaternion& result) const noexcept;

		float Dot(const Quaternion& Q) const noexcept;

		Quaternion RotateTowards(const Quaternion& target, float maxAngle) const noexcept;

		// Computes rotation about y-axis (y), then x-axis (x), then z-axis (z)
		Vector3Float ToEuler() const noexcept;

		// Static functions
		static Quaternion CreateFromAxisAngle(const Vector3Float& axis, float angle) noexcept;

		// Rotates about y-axis (yaw), then x-axis (pitch), then z-axis (roll)
		static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll) noexcept;

		// Rotates about y-axis (angles.y), then x-axis (angles.x), then z-axis (angles.z)
		static Quaternion CreateFromYawPitchRoll(const Vector3Float& angles) noexcept;

		static Quaternion CreateFromRotationMatrix(const Matrix4& M) noexcept;

		static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept;

		static Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept;

		static float Angle(const Quaternion& q1, const Quaternion& q2) noexcept;

		// Constants
		static const Quaternion Identity;
	};

	// Binary operators
	Quaternion operator+(const Quaternion& Q1, const Quaternion& Q2) noexcept;
	Quaternion operator-(const Quaternion& Q1, const Quaternion& Q2) noexcept;
	Quaternion operator*(const Quaternion& Q1, const Quaternion& Q2) noexcept;
	Quaternion operator*(const Quaternion& Q, float S) noexcept;
	Quaternion operator/(const Quaternion& Q1, const Quaternion& Q2) noexcept;
	Quaternion operator*(float S, const Quaternion& Q) noexcept;
}
