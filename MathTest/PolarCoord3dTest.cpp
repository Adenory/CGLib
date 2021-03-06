#include "gtest\gtest.h"
#include "../Math/PolarCoord3d.h"

using namespace Crystal::Math;

TEST(PolarCoord3dTest, TestToOrtho)
{
	/*
	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(180)), Angle<float>(Degree<float>(180)));
		const auto& actual = polar.toOrtho();
		const Vector3d<float> expected(0.0f, 0.0f, -1.0f);
		EXPECT_EQ(expected, actual);
	}
	*/

	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(0)), Angle<float>(Degree<float>(0)));
		const auto& actual = polar.toOrtho();
		const Vector3d<float> expected(0.0f, 0.0f, 1.0f);
		EXPECT_EQ(expected, actual);
	}

	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(0)), Angle<float>(Degree<float>(90)));
		const auto& actual = polar.toOrtho();
		const Vector3d<float> expected(0.0f, 0.0f, 1.0f);
		EXPECT_EQ(expected, actual);
	}

	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(90)), Angle<float>(Degree<float>(0)));
		const auto& actual = polar.toOrtho();
		const Vector3d<float> expected(1.0f, 0.0f, 0.0f);
		EXPECT_EQ(expected, actual);
	}


	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(90)), Angle<float>(Degree<float>(90)));
		const auto& actual = polar.toOrtho();
		const Vector3d<float> expected(0.0f, 1.0f, 0.0f);
		EXPECT_EQ(expected, actual);
	}
}

TEST(PolarCoord3dTest, TestGetOrientation)
{
	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(0)), Angle<float>(Degree<float>(0)));
		const auto& actual = polar.getOrientation();
		Quaternion<float> expected(0, 0, 0, 1);
		EXPECT_EQ(expected, actual);
	}
}