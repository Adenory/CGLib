#include "stdafx.h"

#include "../Core/SpaceHash.h"
#include "../Core/Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SpaceHashTest, TestCenter)
{
	SpaceHash<Particle> hash(1.0f, 100);
	Particle p1(Vector3d<float>(0.0f, 0.0f, 0.0f), 1.0f, 1.0f);
	Particle p2(Vector3d<float>(0.5f, 0.0f, 0.0f), 1.0f, 1.0f);
	Particle p3(Vector3d<float>(-0.5f, 0.0f, 0.0f), 1.0f, 1.0f);
	hash.add(&p1);
	hash.add(&p2);
	hash.add(&p3);
	{
		auto actual = hash.getNeighbor(Vector3d<float>(0.0, 0.0, 0.0), 1.0f);
		EXPECT_EQ(3, actual.size());
	}

	{
		auto actual = hash.getNeighbor(Vector3d<float>(1.0, 0.0, 0.0), 1.0f);
		EXPECT_EQ(1, actual.size());
	}

	{
		auto actual = hash.getNeighbor(Vector3d<float>(-1.0, 0.0, 0.0), 1.0f);
		EXPECT_EQ(1, actual.size());
	}


}

TEST(SpaceHashTest, TestAxisX)
{
	SpaceHash<Particle> hash(1.0f, 100);
	Particle p1(Vector3d<float>(4.5f, 0.0f, 0.0f), 1.0f, 0.5f);
	Particle p2(Vector3d<float>(5.0f, 0.0f, 0.0f), 1.0f, 0.5f);
	Particle p3(Vector3d<float>(5.6f, 0.0f, 0.0f), 1.0f, 0.5f);
	hash.add(&p1);
	hash.add(&p2);
	hash.add(&p3);
	{
		auto actual = hash.getNeighbor(Vector3d<float>(5.0, 0.0, 0.0), 0.5f);
		EXPECT_EQ(1, actual.size());
	}

	{
		auto actual = hash.getNeighbor(Vector3d<float>(0.0, 0.0, 0.0), 0.5f);
		EXPECT_EQ(0, actual.size());
	}

	{
		auto actual = hash.getNeighbor(Vector3d<float>(4.0, 0.0, 0.0), 0.5f);
		EXPECT_EQ(0, actual.size());
	}

}

TEST(SpaceHashTest, TestAxisY)
{
	SpaceHash<Particle> hash(1.0f, 100);
	Particle p1(Vector3d<float>(0.0f, 4.5f, 0.0f), 1.0f, 0.5f);
	Particle p2(Vector3d<float>(0.0f, 5.0f, 0.0f), 1.0f, 0.5f);
	Particle p3(Vector3d<float>(0.0f, 5.6f, 0.0f), 1.0f, 0.5f);
	hash.add(&p1);
	hash.add(&p2);
	hash.add(&p3);
	{
		auto actual = hash.getNeighbor(Vector3d<float>(0.0, 5.0, 0.0), 0.5f);
		EXPECT_EQ(1, actual.size());
	}

	{
		auto actual = hash.getNeighbor(Vector3d<float>(0.0, 0.0, 0.0), 0.5f);
		EXPECT_EQ(0, actual.size());
	}

	{
		auto actual = hash.getNeighbor(Vector3d<float>(0.0, 4.0, 0.0), 0.5f);
		EXPECT_EQ(0, actual.size());
	}
}

TEST(SpaceHashTest, TestAxisZ)
{
	SpaceHash<Particle> hash(1.0f, 100);
	Particle p1(Vector3d<float>(0.0f, 0.0f, 4.5f), 1.0f, 0.5f);
	Particle p2(Vector3d<float>(0.0f, 0.0f, 5.0f), 1.0f, 0.5f);
	Particle p3(Vector3d<float>(0.0f, 0.0f, 5.6f), 1.0f, 0.5f);
	hash.add(&p1);
	hash.add(&p2);
	hash.add(&p3);
	{
		auto actual = hash.getNeighbor(Vector3d<float>(0.0, 0.0, 5.0), 0.5f);
		EXPECT_EQ(1, actual.size());
	}

	{
		auto actual = hash.getNeighbor(Vector3d<float>(0.0, 0.0, 0.0), 0.5f);
		EXPECT_EQ(0, actual.size());
	}

	{
		auto actual = hash.getNeighbor(Vector3d<float>(0.0, 0.0, 4.0), 0.5f);
		EXPECT_EQ(0, actual.size());
	}
}


