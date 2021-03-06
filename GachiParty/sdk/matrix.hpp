#pragma once
#include "vector.h"





class VMatrix
{
public:
	VMatrix() {};
	VMatrix(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	)
	{
		m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;m[0][3] = m03;
		m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;m[1][3] = m13;
		m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;m[2][3] = m23;
		m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
	};
/*	VMatrix(const Vector& forward, const Vector& left, const Vector& up);
	explicit VMatrix(const matrix3x4_t& matrix3x4);
	void		Init(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	);
	void		Init(const matrix3x4_t& matrix3x4);
	inline float* operator[](int i)
	{
		return m[i];
	}
	inline const float* operator[](int i) const
	{
		return m[i];
	}
	inline float* Base()
	{
		return &m[0][0];
	}
	inline const float* Base() const
	{
		return &m[0][0];
	}

	void		SetLeft(const Vector& vLeft);
	void		SetUp(const Vector& vUp);
	void		SetForward(const Vector& vForward);

	void		GetBasisVectors(Vector& vForward, Vector& vLeft, Vector& vUp) const;
	void		SetBasisVectors(const Vector& vForward, const Vector& vLeft, const Vector& vUp);
	Vector& GetTranslation(Vector& vTrans) const;
	void		SetTranslation(const Vector& vTrans);
	void		PreTranslate(const Vector& vTrans);
	void		PostTranslate(const Vector& vTrans);
	matrix3x4_t& As3x4();
	const matrix3x4_t& As3x4() const;
	void		CopyFrom3x4(const matrix3x4_t& m3x4);
	void		Set3x4(matrix3x4_t& matrix3x4) const;

	bool		operator==(const VMatrix& src) const;
	bool		operator!=(const VMatrix& src) const { return !(*this == src); }
	// Access the basis vectors.
	Vector		GetLeft() const;
	Vector		GetUp() const;
	Vector		GetForward() const;
	Vector		GetTranslation() const;
	void		V3Mul(const Vector& vIn, Vector& vOut) const;

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
	Vector		ApplyRotation(const Vector& vVec) const;

	// Multiply by a vector (divides by w, assumes input w is 1).
	Vector		operator*(const Vector& vVec) const;

	// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
	Vector		VMul3x3(const Vector& vVec) const;

	// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
	Vector		VMul3x3Transpose(const Vector& vVec) const;

	// Multiply by the upper 3 rows.
	Vector		VMul4x3(const Vector& vVec) const;

	// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
	Vector		VMul4x3Transpose(const Vector& vVec) const;
#endif


	// Matrix->plane operations.
public:
	// Transform the plane. The matrix can only contain translation and rotation.
	void		TransformPlane(const VPlane& inPlane, VPlane& outPlane) const;

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// Just calls TransformPlane and returns the result.
	VPlane		operator*(const VPlane& thePlane) const;
#endif

	// Matrix->matrix operations.
public:

	VMatrix& operator=(const VMatrix& mOther);

	// Multiply two matrices (out = this * vm).
	void		MatrixMul(const VMatrix& vm, VMatrix& out) const;

	// Add two matrices.
	const VMatrix& operator+=(const VMatrix& other);

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// Just calls MatrixMul and returns the result.	
	VMatrix		operator*(const VMatrix& mOther) const;

	// Add/Subtract two matrices.
	VMatrix		operator+(const VMatrix& other) const;
	VMatrix		operator-(const VMatrix& other) const;

	// Negation.
	VMatrix		operator-() const;

	// Return inverse matrix. Be careful because the results are undefined 
	// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
	VMatrix		operator~() const;
#endif

	// Matrix operations.
public:
	// Set to identity.
	void		Identity();

	bool		IsIdentity() const;

	// Setup a matrix for origin and angles.
	void		SetupMatrixOrgAngles(const Vector& origin, const QAngle& vAngles);

	// General inverse. This may fail so check the return!
	bool		InverseGeneral(VMatrix& vInverse) const;

	// Does a fast inverse, assuming the matrix only contains translation and rotation.
	void		InverseTR(VMatrix& mRet) const;

	// Usually used for debug checks. Returns true if the upper 3x3 contains
	// unit vectors and they are all orthogonal.
	bool		IsRotationMatrix() const;

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// This calls the other InverseTR and returns the result.
	VMatrix		InverseTR() const;

	// Get the scale of the matrix's basis vectors.
	Vector		GetScale() const;

	// (Fast) multiply by a scaling matrix setup from vScale.
	VMatrix		Scale(const Vector& vScale);

	// Normalize the basis vectors.
	VMatrix		NormalizeBasisVectors() const;

	// Transpose.
	VMatrix		Transpose() const;

	// Transpose upper-left 3x3.
	VMatrix		Transpose3x3() const;
#endif
*/
public:
	// The matrix.
	vec_t		m[4][4];
};


struct matrix3x4_t
{
	matrix3x4_t() {}
	matrix3x4_t(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
	{
		m_flMatVal[0][0] = m00;	m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
		m_flMatVal[1][0] = m10;	m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
		m_flMatVal[2][0] = m20;	m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	void Init(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin)
	{
		m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
		m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
		m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	matrix3x4_t(const Vector& xAxis, const Vector& yAxis, const Vector& zAxis, const Vector& vecOrigin)
	{
		Init(xAxis, yAxis, zAxis, vecOrigin);
	}

	inline void Invalidate(void)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_flMatVal[i][j] = 0;
			}
		}
	}
	Vector GetXAxis()  const { return at(0); }
	Vector GetYAxis()  const { return at(1); }
	Vector GetZAxis()  const { return at(2); }
	Vector GetOrigin() const { return at(3); }

	Vector at(int i) const { return Vector{ m_flMatVal[0][i], m_flMatVal[1][i], m_flMatVal[2][i] }; }
	float* operator[](int i) { assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	const float* operator[](int i) const { assert((i >= 0) && (i < 3)); return m_flMatVal[i]; }
	float* Base() { return &m_flMatVal[0][0]; }
	const float* Base() const { return &m_flMatVal[0][0]; }

	float m_flMatVal[3][4];
};


#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif