#include "stdafx.h"

#include "../Core/PolygonFactory.h"
#include "../Core/PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(PolygonFactoryTest, TestCreate)
{
	Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(triangle.toCurve3d());
	PolygonFactory factory;
	auto actual = factory.create(builder);
	EXPECT_EQ(1, actual->getFaces().size());
	EXPECT_EQ(3, actual->getVertices().size());

}

TEST(PolygonFactoryTest, TestMerge)
{
	 Triangle3d<float> t1(Vector3d<float>(-1,0,0), Vector3d<float>(1,0,0), Vector3d<float>(0,1,0));
	 PolygonBuilder builder(t1.toCurve3d());
	 builder.build();
	 PolygonFactory f1;
	 f1.create(builder);
	 PolygonFactory f2;
	 f2.create(builder);
	 f1.merge(f2);
	 EXPECT_EQ(2, f1.getFaces().size());
	 EXPECT_EQ(0, f2.getFaces().size());
	 EXPECT_EQ(6, f1.getVertices().size());
	 EXPECT_EQ(0, f2.getVertices().size());
}

TEST(PolygonFactoryTest, TestRemoveFace)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(t1.toCurve3d());
	PolygonFactory factory;
	auto f = factory.create(builder);
	factory.remove(f);
	EXPECT_EQ(0, factory.getFaces().size());
	EXPECT_EQ(0, factory.getVertices().size());
	EXPECT_EQ(0, factory.getPolygons().size());
}

TEST(PolygonFactoryTest, TestDestoryVertexTriangle)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(t1.toCurve3d());
	PolygonFactory factory;
	auto f = factory.create(builder);
	auto v = f->getVertices().back();
	factory.destory(v);
	EXPECT_EQ(0, factory.getFaces().size());
	EXPECT_EQ(0, factory.getEdges().size());
	EXPECT_EQ(0, factory.getVertices().size());
	EXPECT_EQ(0, factory.getPolygons().size());
}

TEST(PolygonFactoryTest, TestDestoryVertexQuad)
{
	Quad<float> q(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(q.toCurve3d());
	PolygonFactory factory;
	auto f = factory.create(builder);
	auto v = factory.getVertices().findById(2);
	factory.destory(v);
	EXPECT_EQ(1, factory.getFaces().size());
	EXPECT_EQ(3, factory.getEdges().size());
	EXPECT_EQ(3, factory.getVertices().size());
	EXPECT_EQ(1, factory.getPolygons().size());
}

TEST(PolygonFactoryTest, TestDestoryFace)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(t1.toCurve3d());
	PolygonFactory factory;
	auto f = factory.create(builder);
	factory.destory(f->getFaces().front());
	EXPECT_EQ(0, factory.getFaces().size());
	EXPECT_EQ(0, factory.getEdges().size());
	EXPECT_EQ(0, factory.getVertices().size());
	EXPECT_EQ(0, factory.getPolygons().size());
}

TEST(PolygonFactoryTest, TestDestoryEdge)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(t1.toCurve3d());
	PolygonFactory factory;
	factory.create(builder);
	auto e = factory.getEdges().findById(0);
	factory.destory(e);
	EXPECT_EQ(0, factory.getFaces().size());
	EXPECT_EQ(0, factory.getEdges().size());
	EXPECT_EQ(0, factory.getVertices().size());
	EXPECT_EQ(0, factory.getPolygons().size());
}

TEST(PolygonFactoryTest, TestSimplify)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(t1.toCurve3d());
	PolygonFactory factory;
	auto p = factory.create(builder);
	factory.simplify(p, 1);
}