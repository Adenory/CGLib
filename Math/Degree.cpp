#include "Degree.h"
#include "Radian.h"
#include "Tolerance.h"
#include <cassert>

using namespace Crystal::Math;

template<typename T>
Degree<T>::Degree() :
	deg(0)
{}

template<typename T>
Degree<T>::Degree(const T deg) :
	deg(deg)
{
//	assert(T{ 0 } <= deg && deg <= T{ 360 });
}

template<typename T>
Radian<T> Degree<T>::toRadian() const
{
	return Radian<T>(deg / T{ 180 } *Tolerance<T>::getPI());
}

template<typename T>
bool Degree<T>::equals(const Degree<T> rhs) const
{
	return Tolerance<T>::isEqualLoosely(deg, rhs.deg);
}

template<typename T>
bool Degree<T>::operator==(const Degree<T> rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Degree<T>::operator!=(const Degree<T> rhs) const
{
	return !equals(rhs);
}

template class Degree<float>;
template class Degree<double>;