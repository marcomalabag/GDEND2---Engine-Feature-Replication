﻿#include "pch.h"
#include "Matrix4.h"

namespace Engine
{
	Matrix4::Matrix4() :
		XMFLOAT4X4(1.0f, 0.0f, 0.0f, 0.0f,
		           0.0f, 1.f, 0.0f, 0.0f,
		           0.0f, 0.0f, 1.0f, 0.0f,
		           0.0f, 0.0f, 0.0f, 1.0f) { }

	Matrix4::Matrix4(const Vector3Float& r0, const Vector3Float& r1, const Vector3Float& r2) :
		XMFLOAT4X4(r0.x, r0.y, r0.z, 0.0f,
		           r1.x, r1.y, r1.z, 0.0f,
		           r2.x, r2.y, r2.z, 0.0f,
		           0.0f, 0.0f, 0.0f, 1.0f) { }

	Matrix4::~Matrix4() = default;

	Matrix4::operator DirectX::XMMATRIX() const
	{
		return XMLoadFloat4x4(this);
	}

	bool Matrix4::operator==(const Matrix4& m) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		const XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		const XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		const XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		return (XMVector4Equal(x1, y1)
		        && XMVector4Equal(x2, y2)
		        && XMVector4Equal(x3, y3)
		        && XMVector4Equal(x4, y4)) != 0;
	}

	bool Matrix4::operator!=(const Matrix4& m) const noexcept
	{
		using namespace DirectX;
		const XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		const XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		const XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		const XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		return (XMVector4NotEqual(x1, y1)
		        || XMVector4NotEqual(x2, y2)
		        || XMVector4NotEqual(x3, y3)
		        || XMVector4NotEqual(x4, y4)) != 0;
	}

	Matrix4& Matrix4::operator+=(const Matrix4& m) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		x1 = XMVectorAdd(x1, y1);
		x2 = XMVectorAdd(x2, y2);
		x3 = XMVectorAdd(x3, y3);
		x4 = XMVectorAdd(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	Engine::Matrix4& Engine::Matrix4::operator-=(const Matrix4& m) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		x1 = XMVectorSubtract(x1, y1);
		x2 = XMVectorSubtract(x2, y2);
		x3 = XMVectorSubtract(x3, y3);
		x4 = XMVectorSubtract(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	Matrix4& Matrix4::operator*=(const Matrix4& m) noexcept
	{
		using namespace DirectX;
		const XMMATRIX m1     = XMLoadFloat4x4(this);
		const XMMATRIX m2     = XMLoadFloat4x4(&m);
		const XMMATRIX result = XMMatrixMultiply(m1, m2);
		XMStoreFloat4x4(this, result);
		return *this;
	}

	Matrix4& Matrix4::operator*=(float s) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		x1 = XMVectorScale(x1, s);
		x2 = XMVectorScale(x2, s);
		x3 = XMVectorScale(x3, s);
		x4 = XMVectorScale(x4, s);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	Matrix4& Matrix4::operator/=(const float s) noexcept
	{
		using namespace DirectX;
		Debug::Assert(s != 0.f, "Attempting to divide by 0!");
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const float rs = 1.0f / s;

		x1 = XMVectorScale(x1, rs);
		x2 = XMVectorScale(x2, rs);
		x3 = XMVectorScale(x3, rs);
		x4 = XMVectorScale(x4, rs);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	Matrix4& Matrix4::operator/=(const Matrix4& m) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		x1 = XMVectorDivide(x1, y1);
		x2 = XMVectorDivide(x2, y2);
		x3 = XMVectorDivide(x3, y3);
		x4 = XMVectorDivide(x4, y4);

		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&_41), x4);
		return *this;
	}

	Matrix4 Matrix4::operator-() const noexcept
	{
		using namespace DirectX;
		XMVECTOR v1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_11));
		XMVECTOR v2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_21));
		XMVECTOR v3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_31));
		XMVECTOR v4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&_41));

		v1 = XMVectorNegate(v1);
		v2 = XMVectorNegate(v2);
		v3 = XMVectorNegate(v3);
		v4 = XMVectorNegate(v4);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), v1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), v2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), v3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), v4);
		return result;
	}

	Matrix4 Matrix4::Transpose() const noexcept
	{
		using namespace DirectX;
		const XMMATRIX m = XMLoadFloat4x4(this);
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixTranspose(m));
		return result;
	}

	float Matrix4::Determinant() const noexcept
	{
		using namespace DirectX;
		const XMMATRIX m = XMLoadFloat4x4(this);
		return XMVectorGetX(XMMatrixDeterminant(m));
	}

	Matrix4 Matrix4::CreateTranslation(const Vector3Float& position) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixTranslation(position.x, position.y, position.z));
		return result;
	}

	Matrix4 Matrix4::CreateTranslation(float x,
	                                   float y,
	                                   float z) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixTranslation(x, y, z));
		return result;
	}

	Matrix4 Matrix4::CreateScale(const Vector3Float& scales) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixScaling(scales.x, scales.y, scales.z));
		return result;
	}

	Matrix4 Matrix4::CreateScale(const float x,
	                             const float y,
	                             const float z) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixScaling(x, y, z));
		return result;
	}

	Matrix4 Matrix4::CreateScale(float scale) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixScaling(scale, scale, scale));
		return result;
	}

	Matrix4 Matrix4::CreateRotationX(float radians) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixRotationX(radians));
		return result;
	}

	Matrix4 Matrix4::CreateRotationY(float radians) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixRotationY(radians));
		return result;
	}

	Matrix4 Matrix4::CreateRotationZ(float radians) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixRotationZ(radians));
		return result;
	}

	Matrix4 Matrix4::CreateFromAxisAngle(const Vector3Float& axis, float angle) noexcept
	{
		using namespace DirectX;
		Matrix4 R;
		const XMVECTOR a = XMLoadFloat3(&axis);
		XMStoreFloat4x4(&R, XMMatrixRotationAxis(a, angle));
		return R;
	}
	
	Matrix4 Matrix4::CreateFromQuaternion(const Quaternion& quat) noexcept
	{
		using namespace DirectX;
		const XMVECTOR quatv = XMLoadFloat4(&quat);
		Matrix4 R;
		XMStoreFloat4x4(&R, XMMatrixRotationQuaternion(quatv));
		return R;
	}

	Matrix4 Matrix4::CreatePerspectiveFieldOfView(float fov,
	                                              float aspectRatio,
	                                              float nearPlane,
	                                              float farPlane) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixPerspectiveFovLH(fov, aspectRatio, nearPlane, farPlane));
		return result;
	}

	Matrix4 Matrix4::CreatePerspective(float width,
	                                   float height,
	                                   float nearPlane,
	                                   float farPlane) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixPerspectiveLH(width, height, nearPlane, farPlane));
		return result;
	}

	Matrix4 Matrix4::CreateOrthographic(float width,
	                                    float height,
	                                    float zNearPlane,
	                                    float zFarPlane) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixOrthographicLH(width, height, zNearPlane, zFarPlane));
		return result;
	}

	Matrix4 Matrix4::CreateOrthographicOffCenter(const float left, const float right,
	                                             const float bottom, const float top,
	                                             const float zNearPlane, const float zFarPlane) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixOrthographicOffCenterLH(left, right,
		                                                         bottom, top,
		                                                         zNearPlane, zFarPlane));
		return result;
	}

	Matrix4 Matrix4::CreateLookAt(Vector3Float position, Vector3Float target, Vector3Float up)
	{
		using namespace DirectX;

		const XMVECTOR x1 = XMLoadFloat3(&position);
		const XMVECTOR x2 = XMLoadFloat3(&target);
		const XMVECTOR x3 = XMLoadFloat3(&up);

		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixLookAtLH(x1, x2, x3));
		return result;
	}

	Matrix4 Matrix4::CreateFromYawPitchRoll(const float yaw, const float pitch, const float roll) noexcept
	{
		using namespace DirectX;
		Matrix4 result;
		XMStoreFloat4x4(&result, XMMatrixRotationRollPitchYaw(pitch, yaw, roll));
		return result;
	}

	Matrix4 Engine::operator+(const Matrix4& m1,
	                          const Matrix4& m2) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._41));

		x1 = XMVectorAdd(x1, y1);
		x2 = XMVectorAdd(x2, y2);
		x3 = XMVectorAdd(x3, y3);
		x4 = XMVectorAdd(x4, y4);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	Matrix4 Engine::operator-(const Matrix4& m1,
	                          const Matrix4& m2) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._41));

		x1 = XMVectorSubtract(x1, y1);
		x2 = XMVectorSubtract(x2, y2);
		x3 = XMVectorSubtract(x3, y3);
		x4 = XMVectorSubtract(x4, y4);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	Matrix4 Engine::operator*(const Matrix4& m1,
	                          const Matrix4& m2) noexcept
	{
		using namespace DirectX;
		const XMMATRIX tempM1  = XMLoadFloat4x4(&m1);
		const XMMATRIX tempM2  = XMLoadFloat4x4(&m2);
		const XMMATRIX product = XMMatrixMultiply(tempM1, tempM2);

		Matrix4 result;
		XMStoreFloat4x4(&result, product);
		return result;
	}

	Matrix4 Engine::operator*(const Matrix4& m,
	                          float s) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		x1 = XMVectorScale(x1, s);
		x2 = XMVectorScale(x2, s);
		x3 = XMVectorScale(x3, s);
		x4 = XMVectorScale(x4, s);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	Matrix4 Engine::operator/(const Matrix4& m,
	                          float s) noexcept
	{
		using namespace DirectX;
		Debug::Assert(s != 0.0f, "Attempting to divide by 0!");

		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m._41));

		const float rs = 1.0f / s;

		x1 = XMVectorScale(x1, rs);
		x2 = XMVectorScale(x2, rs);
		x3 = XMVectorScale(x3, rs);
		x4 = XMVectorScale(x4, rs);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}

	Engine::Matrix4 Engine::operator/(const Matrix4& m1,
	                                  const Matrix4& m2) noexcept
	{
		using namespace DirectX;
		XMVECTOR x1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._11));
		XMVECTOR x2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._21));
		XMVECTOR x3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._31));
		XMVECTOR x4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m1._41));

		const XMVECTOR y1 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._11));
		const XMVECTOR y2 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._21));
		const XMVECTOR y3 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._31));
		const XMVECTOR y4 = XMLoadFloat4(reinterpret_cast<const XMFLOAT4*>(&m2._41));

		x1 = XMVectorDivide(x1, y1);
		x2 = XMVectorDivide(x2, y2);
		x3 = XMVectorDivide(x3, y3);
		x4 = XMVectorDivide(x4, y4);

		Matrix4 result;
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._11), x1);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._21), x2);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._31), x3);
		XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&result._41), x4);
		return result;
	}
}
