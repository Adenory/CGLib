#ifndef __CRYSTAL_MATH_MATRIX_2D_H__
#define __CRYSTAL_MATH_MATRIX_2D_H__

#include "Tolerance.h"
#include "Angle.h"

#include <vector>
#include <cassert>
#include <array>

namespace Crystal {
	namespace Math {

template< typename T >
class Matrix2d
{
public:
	Matrix2d(void);

	Matrix2d(
		const T x00, const T x01,
		const T x10, const T x11
		);

	explicit Matrix2d(const std::array<T, 4>& v);

	~Matrix2d() = default;

	void setIdentity();

	void setRotate(const T angle);

	Angle<T> getRotationAngle() const;

	bool isRotation() const;

	static Matrix2d Identity() { return Matrix2d(1, 0, 0, 1); }

	static Matrix2d<T> Zero() { return Matrix2d(0, 0, 0, 0); }

	static Matrix2d Rotate(const T angle);

	bool equals(const Matrix2d& rhs) const;

	T getDeterminant() const;

	bool hasInverse() const;

	Matrix2d getInverse() const;

	Matrix2d product(const Matrix2d& rhs) { return *this = getProduct(rhs); }

	Matrix2d getProduct(const Matrix2d& rhs) const;

	Matrix2d scale(const T factor);

	Matrix2d getScaled(const T factor) const;

	Matrix2d add(const Matrix2d& rhs);

	Matrix2d getAdd(const Matrix2d& rhs) const;

	bool operator==(const Matrix2d& rhs) const { return equals(rhs); }

	bool operator!=(const Matrix2d& rhs) const { return !equals(rhs); }

	Matrix2d operator+(const Matrix2d& rhs) const { return getAdd(rhs); }

	const Matrix2d operator+=(const Matrix2d& rhs) { return add(rhs); }

	Matrix2d operator-(const Matrix2d& rhs) const { return getAdd(rhs.getScaled(-1.0)); }

	const Matrix2d operator-=(const Matrix2d& rhs) { return add(rhs.getScaled(-1.0)); }

	Matrix2d operator*(const Matrix2d& rhs) const { return getProduct(rhs); }

	const Matrix2d operator*=(const Matrix2d& rhs) { return product(rhs); }

	T getX00() const { return x[0]; }

	T getX01() const { return x[1]; }

	T getX10() const { return x[2]; }

	T getX11() const { return x[3]; }

	std::array< T, 4 > toArray2x2() const { return x; }

	std::array< T, 2 > getEigenValues() const;

private:
	std::array< T, 4 > x;
};

	}
}

#endif