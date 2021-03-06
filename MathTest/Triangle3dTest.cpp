#include "gtest/gtest.h"

#include "../Math/Triangle3d.h"
#include "../Math/Box3d.h"

using namespace Crystal::Math;

template<class T>
class Triangle3dTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(Triangle3dTest, TestTypes);


TYPED_TEST(Triangle3dTest, TestGet)
{
	using T = TypeParam;
	EXPECT_EQ(Vector3d<T>(0, 0, 0), Triangle3d<T>().getv0());
	EXPECT_EQ(Vector3d<T>(1, 0, 0), Triangle3d<T>().getv1());
	EXPECT_EQ(Vector3d<T>(0, 1, 0), Triangle3d<T>().getv2());
}

TYPED_TEST(Triangle3dTest, TestGetArea)
{
	using T = TypeParam;
	EXPECT_EQ( 0.5, Triangle3d<T>().getArea() );
}

TYPED_TEST(Triangle3dTest, TestGetNormal)
{
	using T = TypeParam;
	EXPECT_EQ(Vector3d<T>::UnitZ(), Triangle3d<T>::UnitXY().getNormal());
	EXPECT_EQ(Vector3d<T>::UnitY(), Triangle3d<T>::UnitXZ().getNormal());
	EXPECT_EQ(Vector3d<T>::UnitX(), Triangle3d<T>::UnitYZ().getNormal());

	const auto actual = Triangle3d<T>(
		Vector3d<T>(0,0,0),
		Vector3d<T>(1,0,0),
		Vector3d<T>(1,0,1)
		).getNormal();
	EXPECT_EQ(Vector3d<T>(0, -1, 0), actual);
}

TYPED_TEST(Triangle3dTest, TestIsCCW)
{
	using T = TypeParam;
	EXPECT_TRUE( Triangle3d<T>().isCCW() );
}

TYPED_TEST(Triangle3dTest, TestIsInside)
{
	using T = TypeParam;
	const Triangle3d<T> triangle(Vector3d<T>(-1, 0, 0), Vector3d<T>(1, 0, 0), Vector3d<T>(0, 1, 0));
	EXPECT_TRUE( triangle.isInside(Vector3d<T>( 0, 0.5, 0)));
	EXPECT_FALSE(triangle.isInside(Vector3d<T>(-2, 0, 0)));
	EXPECT_FALSE(triangle.isInside(Vector3d<T>( 2, 0, 0)));

}

TYPED_TEST(Triangle3dTest, TestIsOutside)
{
	using T = TypeParam;
	const Triangle3d<T> triangle(Vector3d<T>(-1, 0, 0), Vector3d<T>(1, 0, 0), Vector3d<T>(0, 1, 0));
	EXPECT_FALSE(triangle.isOutside(Vector3d<T>(0, 0.5, 0)));
	EXPECT_TRUE( triangle.isOutside(Vector3d<T>(-2, 0, 0)));
	EXPECT_TRUE( triangle.isOutside(Vector3d<T>(2, 0, 0)));
}

TYPED_TEST(Triangle3dTest, TestIsSamePlane)
{
	using T = TypeParam;
	const Triangle3d<T> triangle(Vector3d<T>(-1, 0, 0), Vector3d<T>(1, 0, 0), Vector3d<T>(0, 1, 0));
	EXPECT_TRUE( triangle.isSamePlane(Vector3d<T>(2, 0, 0)));
	EXPECT_FALSE(triangle.isSamePlane(Vector3d<T>(0, 0, 10)) );
}

TYPED_TEST(Triangle3dTest, TestGetBoundingBox)
{
	using T = TypeParam;
	const Triangle3d<T> triangle(Vector3d<T>(-1, 0, 0), Vector3d<T>(1, 0, 0), Vector3d<T>(0, 1, 0));
	const auto& actual = triangle.getBoundingBox();
	const Box3d<T> expected(Vector3d<T>(-1, 0, 0), Vector3d<T>(1, 1, 0));
	EXPECT_EQ(expected, actual);
}

TYPED_TEST(Triangle3dTest, TestGetInscribedCircleRadius)
{
	using T = TypeParam;
	const Triangle3d<T> triangle1(Vector3d<T>(0, 0, 0), Vector3d<T>(3, 0, 0), Vector3d<T>(0, 4, 0));
	const auto actual1 = triangle1.getInscribedCircleRadius();
	EXPECT_FLOAT_EQ(actual1, 1);
}