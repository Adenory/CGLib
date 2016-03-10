#include "gtest/gtest.h"

#include "../Physics/Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;


TEST(ParticleConstantTest, TestConstruct)
{
	Particle::Constant constant;
	EXPECT_EQ(1.0f, constant.getDiameter() );
	EXPECT_EQ(1.0f, constant.getRestDensity());
}


TEST(ParticleConstantTest, TestGetVolume)
{
	Particle::Constant constant;
	constant.diameter = 2.0f;
	EXPECT_FLOAT_EQ(8.0f, constant.getVolume());
}

TEST(ParticleTest, TestConstruct)
{
	const Particle particle;
	EXPECT_EQ(Vector3d<float>(0.0f, 0.0f, 0.0f), particle.getPosition());
}

TEST(ParticleTest, TestConstructByPosition)
{
	const Particle particle(Vector3d<float>(1.0f, 2.0f, 3.0f));
	EXPECT_EQ(Vector3d<float>(1.0f, 2.0f, 3.0f), particle.getPosition());
}

TEST(ParticleTest, TestConstructByConstant)
{
	const Particle::Constant constant;
	const Particle particle(constant, Vector3d<float>( 0.0f, 0.0f, 0.0f ) );
}