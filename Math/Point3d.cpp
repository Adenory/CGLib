#include "Point3d.h"

using namespace Crystal::Math;

template<typename T>
Point3d<T>::Point3d(const Vector3d<T>& position) :
	position( position )
{}

template<typename T>
Point3d<T>::Point3d(const Point2d<T>& point2d) :
	position( point2d.getPosition()),
	normal( point2d.getNormal()),
	parameter( point2d.getParameter(), 0)
{
}


template<typename T>
Point3d<T>::Point3d(const Vector3d<T>& position, const Vector3d<T>& normal) :
	position( position ),
	normal( normal )
{
}

template<typename T>
Point3d<T>::Point3d(const Vector3d<T>& position, const Vector3d<T>& normal, const Vector2d<T>& parameter) :
	position( position ),
	normal( normal ),
	parameter( parameter )
{
}

template<typename T>
void Point3d<T>::transform(const Matrix3d<T>& matrix)
{
	position.rotate(matrix);
	normal.rotate(matrix);
}

template<typename T>
void Point3d<T>::scale(const Vector3d<T>& v)
{
	position.scale(v.getX(), v.getY(), v.getZ());
}


template class Point3d<float>;
template class Point3d<double>;