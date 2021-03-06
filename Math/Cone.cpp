#include "Cone.h"

#include "Tolerance.h"

using namespace Crystal::Math;

template<typename T>
Cone<T>::Cone() :
	radius(0.5),
	height(1)
{
}

template<typename T>
Cone<T>::Cone(const T radius, const T height) :
	radius(radius),
	height(height)
{}

template<typename T>
Cone<T>::Cone(const T radius, const T height, const Vector3d<T>& center) :
	radius(radius),
	height(height),
	IPrimitive3d<T>(center)
{
}

template<typename T>
Cone<T>::Cone(const T radius, const T height, const Vector3d<T>& center, const Quaternion<T>& orientation) :
	radius(radius),
	height(height),
	IPrimitive3d<T>(center, orientation)
{
}


template<typename T>
T Cone<T>::getVolume() const
{
	return Tolerance<T>::getPI() * radius * radius * height / T{ 3 };
}

template<typename T>
Vector3d<T> Cone<T>::getPosition(const Param<T> u, const Param<T> v) const
{
	return getPosition(u.toAngle(), v);
}

template<typename T>
Vector3d<T> Cone<T>::getPosition(const Angle<T> u, const Param<T> v) const
{
	const auto x = radius * (1-v.get()) * u.getCos();
	const auto y = v.get() * height - height*T{ 0.5 };
	const auto z = radius * (1-v.get()) * u.getSin();

	Vector3d<T> vec(x, y, z);
	const auto rotation = orientation.toMatrix();
	vec.rotate(rotation.transposed());

	return vec + center;
}

template<typename T>
Vector3d<T> Cone<T>::getNormal(const Angle<T> u, const Param<T> v) const
{
	const auto& pos = getPosition(u, v);
	const auto xz = std::sqrt(pos.getX()*pos.getX() + pos.getZ()*pos.getZ());
	const auto x = pos.getX() / xz;
	const auto y = xz / (height - pos.getY());
	const auto z = pos.getZ() / xz;
	return Vector3d<T>(x, y, z).normalized();
}

template<typename T>
Vector3d<T> Cone<T>::getNormal(const Param<T> u, const Param<T> v) const
{
	return getNormal(u.toAngle(), v);
}

template<typename T>
Point3d<T> Cone<T>::getPoint(const Param<T> u, const Param<T> v) const
{
	const auto pos = getPosition(u, v);
	const auto norm = getNormal(u, v);
	const Vector2d<T> param(u.get(), v.get());
	return Point3d<T>(pos, norm, param);
}


template<typename T>
CircularCurve3d<T> Cone<T>::toSideCurve(const int number) const
{
	const auto top = getPoint(Param<T>(0), Param<T>(1));
	std::vector<Point3d<T>> points;
	for (int i = 0; i < number; ++i) {
		const auto param = Param<T>(i / (T)number);
		const auto& v1 = getPoint(param, Param<T>(0));
		points.push_back(v1);
	}
	CircularCurve3d<T> curve(top, points);

	return curve;
}

template<typename T>
CircularCurve3d<T> Cone<T>::toBottomCurve(const int number) const
{
	const auto b1 = getPosition(Param<T>(0), Param<T>(0));
	const auto b2 = getPosition(Param<T>(0.5), Param<T>(0));
	const auto center = b1 / T{ 2 } +b2 / T{ 2 };
	Point3d<T> c(center);
	std::vector<Point3d<T>> points;
	for (int i = 0; i < number; ++i) {
		const auto param = Param<T>(i / (T)number);
		const auto& v1 = getPoint(param, Param<T>(0));
		points.push_back(v1);
	}
	return CircularCurve3d<T>(c, points);
}


template class Cone<float>;
template class Cone<double>;