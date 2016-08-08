#include "stdafx.h"

#include "../Core/Vertex.h"
#include "../Core/HalfEdge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(EdgeTest, TestGetVector)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	HalfEdge e(&n1, &n2, 0);
	EXPECT_EQ(Vector3d<float>(1,0,0), e.getVector());
}

TEST(EdgeTest, TestGetLength)
{
	Vertex n1(Vector3d<float>(0,0,0),0);
	Vertex n2(Vector3d<float>(1,0,0),1);
	HalfEdge e(&n1, &n2, 0);
	EXPECT_EQ(1, e.getLength());
}

TEST(EdgeTest, TestIsReverse)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	Vertex n3(Vector3d<float>(2, 0, 0), 2);
	HalfEdge e1(&n1, &n2, 0);
	HalfEdge e2(&n2, &n1, 0);
	HalfEdge e3(&n3, &n1, 0);
	EXPECT_TRUE(e1.isReverse(e2));
	EXPECT_TRUE(e2.isReverse(e1));
	EXPECT_FALSE(e1.isReverse(e3));

}

TEST(EdgeTest, TestIsShared)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	Vertex n3(Vector3d<float>(2, 0, 0), 2);
	const HalfEdge e1(&n1, &n2, 0);
	const HalfEdge e2(&n2, &n1, 0);
	const HalfEdge e3(&n3, &n1, 0);

	EXPECT_TRUE( e1.isShared(e2));
	EXPECT_FALSE(e1.isShared(e3));
}

TEST(EdgeTest, TestIsCollapsed)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	const HalfEdge e1(&n1, &n2, 0);
	const HalfEdge e2(&n1, nullptr, 0);
	EXPECT_FALSE(e1.isCollapsed());
	EXPECT_TRUE( e2.isCollapsed());
}

TEST(EdgeTest, TestIsDegenerated)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(0, 0, 0), 1);
	const HalfEdge e1(&n1, &n2, 0);
	EXPECT_TRUE(e1.isDegenerated());
	n2.moveTo(Vector3d<float>(1, 0, 0));
	EXPECT_FALSE(e1.isDegenerated());
}

TEST(EdgeTest, TestToDegenerate)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	HalfEdge e1(&n1, &n2, 0);
	EXPECT_FALSE(e1.isDegenerated());
	e1.toDenerate();
	EXPECT_TRUE( e1.isDegenerated());
}

TEST(EdgeTest, TestReverse)
{
	Vertex n1(Vector3d<float>(0, 0, 0), 0);
	Vertex n2(Vector3d<float>(1, 0, 0), 1);
	HalfEdge e1(&n1, &n2, 0);
	e1.reverse();
	EXPECT_EQ( &n2, e1.getStart() );
	EXPECT_EQ( &n1, e1.getEnd() );
}
