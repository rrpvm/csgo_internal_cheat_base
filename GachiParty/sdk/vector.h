#pragma once
#include "../includes/win_modules.hpp"
#include <numeric>
#include <limits>
typedef float vec_t;
class Vector
{
public:
	vec_t x, y, z;
	Vector(vec_t X, vec_t Y, vec_t Z);
	Vector() {
		x = std::numeric_limits<float>::infinity();
		y = std::numeric_limits<float>::infinity();
		z = std::numeric_limits<float>::infinity();
	}
	Vector(const Vector& vOther)
	{
		x = vOther.x;
		y = vOther.y;
		z = vOther.z;
	}
	Vector(const float* clr)
	{
		x = clr[0];
		y = clr[1];
		z = clr[2];
	}

	explicit Vector(vec_t XYZ); ///< broadcast initialize
	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f, vec_t iz = 0.0f);
	bool IsValid() const;
	vec_t operator[](int i) const;
	vec_t& operator[](int i);
	vec_t* Base();
	vec_t const* Base() const;
	inline void Zero(); ///< zero out a vector
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;
	FORCEINLINE Vector& operator+=(const Vector& v);
	FORCEINLINE Vector& operator-=(const Vector& v);
	FORCEINLINE Vector& operator*=(const Vector& v);
	FORCEINLINE Vector& operator*=(float s);
	FORCEINLINE Vector& operator/=(const Vector& v);
	FORCEINLINE Vector& operator/=(float s);
	FORCEINLINE Vector& operator+=(float fl); ///< broadcast add
	FORCEINLINE Vector& operator-=(float fl); ///< broadcast sub			
	void	Negate();
	inline vec_t	Length() const;
	FORCEINLINE vec_t LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance&&
			z > -tolerance && z < tolerance);
	}
	Vector	Normalized() const {};
	FORCEINLINE vec_t DistToSqr(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}
	vec_t DistTo(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.Length();
	}
	void	CopyToArray(float* rgfl) const;
	vec_t	Dot(const Vector& vOther) const {
		return this->x * vOther.x + this->y * vOther.y;
	};
	Vector& operator=(const Vector& vOther);
	Vector	operator-(void) const {};
	Vector	operator+(const Vector& v) const {
		return Vector(this->x + v.x, this->y + v.y, this->z + v.z);
	};
	Vector	operator-(const Vector& v) const {
		return Vector(this->x - v.x, this->y - v.y, this->z - v.z);
	};
	Vector	operator*(const Vector& v) const {
		return Vector(this->x * v.x, this->y * v.y, this->z * v.z);
	};
	Vector	operator/(const Vector& v) const {
		return Vector(this->x / v.x, this->y / v.y, this->z / v.z);
	};
	Vector	operator*(float fl) const {
		return Vector(this->x * fl, this->y * fl, this->z * fl);
	};
	Vector	operator/(float fl) const {
		return Vector(this->x / fl, this->y / fl, this->z / fl);
	};
	//Vector	Cross(const Vector& vOther) const;
	//Vector	Min(const Vector& vOther) const;
	//Vector	Max(const Vector& vOther) const;



	
};
class QAngle
{
public:
	QAngle(void)
	{
		Init();
	}
	QAngle(float X, float Y, float Z)
	{
		Init(X, Y, Z);
	}
	QAngle(const float* clr)
	{
		Init(clr[0], clr[1], clr[2]);
	}
	QAngle(const Vector& v)
	{
		this->yaw = v.y;
		this->pitch = v.x;
		this->roll = v.z;
	}
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
	{
		pitch = ix;
		yaw = iy;
		roll = iz;
	}
	void clamp() {
		if (pitch > 89.0f)pitch = 89.0f;
		else if (pitch < -89.0f)pitch = -89.0f;
		if (yaw > 180.0f)yaw = 180.0f;
		else if (yaw < -180.0f)yaw = -180.0f;
	}
	void nrml() {
		while (yaw > 180.0f)yaw -= 360.0f;
		while (yaw < -180.0f)yaw += 360.0f;
		if (pitch > 89.0f)pitch = 89.0f;
		else if (pitch < -89.0f)pitch = -89.0f;
	}

	float operator[](int i) const
	{
		return ((float*)this)[i];
	}
	float& operator[](int i)
	{
		return ((float*)this)[i];
	}

	QAngle& operator+=(const QAngle& v)
	{
		pitch += v.pitch; yaw += v.yaw; roll += v.roll;
		return *this;
	}
	QAngle& operator-=(const QAngle& v)
	{
		pitch -= v.pitch; yaw -= v.yaw; roll -= v.roll;
		return *this;
	}
	QAngle& operator*=(float fl)
	{
		pitch *= fl;
		yaw *= fl;
		roll *= fl;
		return *this;
	}
	QAngle& operator*=(const QAngle& v)
	{
		pitch *= v.pitch;
		yaw *= v.yaw;
		roll *= v.roll;
		return *this;
	}
	QAngle& operator/=(const QAngle& v)
	{
		pitch /= v.pitch;
		yaw /= v.yaw;
		roll /= v.roll;
		return *this;
	}
	QAngle& operator+=(float fl)
	{
		pitch += fl;
		yaw += fl;
		roll += fl;
		return *this;
	}
	QAngle& operator/=(float fl)
	{
		pitch /= fl;
		yaw /= fl;
		roll /= fl;
		return *this;
	}
	QAngle& operator-=(float fl)
	{
		pitch -= fl;
		yaw -= fl;
		roll -= fl;
		return *this;
	}

	QAngle& operator=(const QAngle& vOther)
	{
		pitch = vOther.pitch; yaw = vOther.yaw; roll = vOther.roll;
		return *this;
	}

	QAngle operator-(void) const
	{
		return QAngle(-pitch, -yaw, -roll);
	}
	QAngle operator+(const QAngle& v) const
	{
		return QAngle(pitch + v.pitch, yaw + v.yaw, roll + v.roll);
	}
	QAngle operator-(const QAngle& v) const
	{
		return QAngle(pitch - v.pitch, yaw - v.yaw, roll - v.roll);
	}
	QAngle operator*(float fl) const
	{
		return QAngle(pitch * fl, yaw * fl, roll * fl);
	}
	QAngle operator*(const QAngle& v) const
	{
		return QAngle(pitch * v.pitch, yaw * v.yaw, roll * v.roll);
	}
	QAngle operator/(float fl) const
	{
		return QAngle(pitch / fl, yaw / fl, roll / fl);
	}
	QAngle operator/(const QAngle& v) const
	{
		return QAngle(pitch / v.pitch, yaw / v.yaw, roll / v.roll);
	}

	float Length() const
	{
		return sqrt(pitch * pitch + yaw * yaw + roll * roll);
	}
	float LengthSqr(void) const
	{
		return (pitch * pitch + yaw * yaw + roll * roll);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (pitch > -tolerance && pitch < tolerance&&
			yaw > -tolerance && yaw < tolerance&&
			roll > -tolerance && roll < tolerance);
	}

	float Normalize() const
	{
		QAngle res = *this;
		float l = res.Length();
		if (l != 0.0f)
		{
			res /= l;
		}
		else
		{
			res[0] = res[1] = res[2] = 0.0f;
		}
		return l;
	}

	float pitch;
	float yaw;
	float roll;
};

inline Vector::Vector(vec_t X, vec_t Y, vec_t Z)
{
	x = X; y = Y; z = Z;
}
inline Vector::Vector(vec_t XYZ)
{
	x = y = z = XYZ;
}
inline void Vector::Init(vec_t ix, vec_t iy, vec_t iz)
{
	x = ix; y = iy; z = iz;
}
inline void Vector::Zero()
{
	x = y = z = 0.0f;
}
inline void VectorClear(Vector& a)
{
	a.x = a.y = a.z = 0.0f;
}
inline Vector& Vector::operator=(const Vector& vOther)
{
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}

inline vec_t& Vector::operator[](int i)
{
	assert((i >= 0) && (i < 3));
	return ((vec_t*)this)[i];
}
inline vec_t Vector::operator[](int i) const
{
	assert((i >= 0) && (i < 3));
	return ((vec_t*)this)[i];
}
inline vec_t* Vector::Base()
{
	return (vec_t*)this;
}
inline vec_t const* Vector::Base() const
{
	return (vec_t const*)this;
}
inline bool Vector::IsValid() const
{
	static const  auto inf = std::numeric_limits<float>::infinity();
	return !(inf == x && inf == y && inf == z);
}
inline bool Vector::operator==(const Vector& src) const
{
	return (src.x == x) && (src.y == y) && (src.z == z);
}
inline bool Vector::operator!=(const Vector& src) const
{
	return (src.x != x) || (src.y != y) || (src.z != z);
}
FORCEINLINE void VectorCopy(const Vector& src, Vector& dst)
{
	
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
inline void	Vector::CopyToArray(float* rgfl) const
{
	assert(rgfl);
	rgfl[0] = x, rgfl[1] = y, rgfl[2] = z;
}
inline void Vector::Negate()
{
	x = -x; y = -y; z = -z;
}
inline vec_t Vector::Length() const
{
	return sqrt(x * x + y * y + z * z);
}
FORCEINLINE  Vector& Vector::operator+=(const Vector& v)
{
	
	x += v.x; y += v.y; z += v.z;
	return *this;
}
FORCEINLINE  Vector& Vector::operator-=(const Vector& v)
{
	
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}
FORCEINLINE  Vector& Vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;
	
	return *this;
}
FORCEINLINE  Vector& Vector::operator*=(const Vector& v)
{
	
	x *= v.x;
	y *= v.y;
	z *= v.z;
	
	return *this;
}
FORCEINLINE Vector& Vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;
	return *this;
}
FORCEINLINE Vector& Vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;
	
	return *this;
}
FORCEINLINE  Vector& Vector::operator/=(float fl)
{
	assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}
FORCEINLINE  Vector& Vector::operator/=(const Vector& v)
{
	
	assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

class __declspec(align(16)) VectorAligned : public Vector
{
public:
	inline VectorAligned(void) {};
	inline VectorAligned(float X, float Y, float Z)
	{
		Init(X, Y, Z);
	}

public:
	explicit VectorAligned(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
	}

	VectorAligned& operator=(const Vector& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	VectorAligned& operator=(const VectorAligned& vOther)
	{
		Init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	float w;
};