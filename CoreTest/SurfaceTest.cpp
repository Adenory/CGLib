#include "stdafx.h"
#include "../Core/Surface.h"
#include "../Core/SurfaceFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SurfaceTest, Test)
{
	Curve3d<float> curve(2,2);

	Point3d<float> p1(Vector3d<float>(0, 0, 0));
	Point3d<float> p2(Vector3d<float>(0, 1, 0));
	Point3d<float> p3(Vector3d<float>(1, 0, 0));
	Point3d<float> p4(Vector3d<float>(1, 1, 0));

	curve.set(0, 0, p1);
	curve.set(0, 1, p2);
	curve.set(1, 0, p3);
	curve.set(1, 1, p4);

	EXPECT_EQ( p1, curve.get(0, 0) );
	EXPECT_EQ( p2, curve.get(0, 1) );
	EXPECT_EQ( p3, curve.get(1, 0) );
	EXPECT_EQ( p4, curve.get(1, 1));

	SurfaceFactory factory;
	auto surface = factory.create(curve);
	EXPECT_EQ(6, surface->getEdges().size());
	EXPECT_EQ(4, surface->getNodes().size());
	EXPECT_EQ(2, surface->getFaces().size());
}

TEST(SurfaceTest, TestConstructByTriangleCurve3d)
{
	TriangleCurve3d<float> curve(2);

	Point3d<float> p1(Vector3d<float>(0, 0, 0));
	Point3d<float> p2(Vector3d<float>(0, 1, 0));
	Point3d<float> p3(Vector3d<float>(1, 0, 0));

	curve.set(0, 0, p1);
	curve.set(1, 0, p2);
	curve.set(1, 1, p3);

	SurfaceFactory factory;
	auto surface = factory.create(curve);
	EXPECT_EQ(3, surface->getNodes().size());
	EXPECT_EQ(3, surface->getEdges().size());
	EXPECT_EQ(1, surface->getFaces().size());

}

TEST(SurfaceTest, TestConstructByTriangleCurve3d2)
{
	TriangleCurve3d<float> curve(3);
	curve.set(0, 0, Point3d<float>(Vector3d<float>(0, 2, 0)));
	curve.set(1, 0, Point3d<float>(Vector3d<float>(-1, 1, 0)));
	curve.set(1, 1, Point3d<float>(Vector3d<float>(1, 1, 0)));
	curve.set(2, 0, Point3d<float>(Vector3d<float>(-2, 0, 0)));
	curve.set(2, 1, Point3d<float>(Vector3d<float>(0, 0, 0)));
	curve.set(2, 2, Point3d<float>(Vector3d<float>(2, 0, 0)));
	SurfaceFactory factory;
	auto f = factory.create(curve);
}


TEST(SurfaceTest, TestMerge)
{
	Curve3d<float> curve(2, 2);

	Point3d<float> p1(Vector3d<float>(0, 0, 0));
	Point3d<float> p2(Vector3d<float>(0, 1, 0));
	Point3d<float> p3(Vector3d<float>(1, 0, 0));
	Point3d<float> p4(Vector3d<float>(1, 1, 0));

	curve.set(0, 0, p1);
	curve.set(0, 1, p2);
	curve.set(1, 0, p3);
	curve.set(1, 1, p4);

	EXPECT_EQ(p1, curve.get(0, 0));
	EXPECT_EQ(p2, curve.get(0, 1));
	EXPECT_EQ(p3, curve.get(1, 0));
	EXPECT_EQ(p4, curve.get(1, 1));

	SurfaceFactory factory1;
	Surface* surface1 = factory1.create(curve);
	SurfaceFactory factory2;
	Surface* surface2 = factory2.create(curve);
	surface1->merge(*surface2);
	EXPECT_EQ(12, surface1->getEdges().size());
	EXPECT_EQ(8, surface1->getNodes().size());
	EXPECT_EQ(4, surface1->getFaces().size());

	//EXPECT_TRUE(surface2->getEdges().empty());
	//EXPECT_TRUE(surface2->getNodes().empty());
	//EXPECT_TRUE(surface2->getFaces().empty());
}

TEST(SurfaceTest, TestGetBoundingBox)
{
	Curve3d<float> curve(2, 2);

	Point3d<float> p1(Vector3d<float>(0, 0, 0));
	Point3d<float> p2(Vector3d<float>(0, 1, 0));
	Point3d<float> p3(Vector3d<float>(1, 0, 0));
	Point3d<float> p4(Vector3d<float>(1, 1, 0));

	curve.set(0, 0, p1);
	curve.set(0, 1, p2);
	curve.set(1, 0, p3);
	curve.set(1, 1, p4);

	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	Box3d<float> expected(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 0));
	Box3d<float> actual = surface->getBoundingBox();
	EXPECT_EQ( expected, actual);
}

TEST(SurfaceTest, TestGetBoundingSphere)
{
	Curve3d<float> curve(2, 2);

	Point3d<float> p1(Vector3d<float>(0, 0, 0));
	Point3d<float> p2(Vector3d<float>(0, 2, 0));
	Point3d<float> p3(Vector3d<float>(2, 0, 0));
	Point3d<float> p4(Vector3d<float>(2, 2, 0));

	curve.set(0, 0, p1);
	curve.set(0, 1, p2);
	curve.set(1, 0, p3);
	curve.set(1, 1, p4);

	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	Sphere<float> expected(Vector3d<float>(1, 1, 0.0), std::sqrt(2));
	Sphere<float> actual = surface->getBoundingSphere();
	EXPECT_EQ(expected, actual);
}

TEST(SurfaceTest, TestGetIntersections)
{
	Curve3d<float> curve(2, 2);

	Point3d<float> p1(Vector3d<float>(0, 0, 0));
	Point3d<float> p2(Vector3d<float>(0, 1, 0));
	Point3d<float> p3(Vector3d<float>(1, 0, 0));
	Point3d<float> p4(Vector3d<float>(1, 1, 0));

	curve.set(0, 0, p1);
	curve.set(0, 1, p2);
	curve.set(1, 0, p3);
	curve.set(1, 1, p4);

	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	const Ray3d<float> ray(Vector3d<float>(0, 0, -10), Vector3d<float>(0, 0, 1));
	const auto& actual = surface->getIntersections(ray);
	EXPECT_EQ(2, actual.size());
}

#include "../Core/SurfaceSplitter.h"

TEST(SurfaceTest, TestSplit)
{
	TriangleCurve3d<float> curve(2);

	Point3d<float> p1(Vector3d<float>(0, 1, 0));
	Point3d<float> p2(Vector3d<float>(-1, 0, 0));
	Point3d<float> p3(Vector3d<float>(1, 0, 0));

	curve.set(0, 0, p1);
	curve.set(1, 0, p2);
	curve.set(1, 1, p3);

	SurfaceFactory factory;
	Surface* surface = factory.create(curve);
	auto f = surface->getFaces().front();
	SurfaceSplittingAlgo splitter(surface, &factory);
	splitter.splited(f);

//	EXPECT_EQ(surface->getNodes().size(), 3);
//	EXPECT_EQ(surface->getFaces().size(), 4);
//	EXPECT_EQ(surface->getEdges().size(), 12);

}