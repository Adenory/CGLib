#include "gtest/gtest.h"
 
#include "../Physics/PhysicsObject.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
using GeomType = float;

TEST( PhysicsObjectTest, TestConstruct )
{
	PhysicsObject<GeomType> object;
	EXPECT_TRUE( object.getParticles().empty() );
}

TEST( PhysicsObjectTest, TestConstructByParticles )
{
	const std::vector<Particle*> particles{ &Particle(Vector3d<GeomType>(1.0f, 0.0f, 0.0f)) };
	const PhysicsObject<GeomType> fluid(particles);
	EXPECT_EQ(1, fluid.getParticles().size());
}


TEST(PhysicsObjectTest, TestGetMass)
{
	{
		PhysicsObject<GeomType> object;
		EXPECT_EQ(0, object.getMass());
	}

	{
		Particle p(Vector3d<GeomType>(1, 0, 0));
		const std::vector<Particle*> particles{ &p };
		const PhysicsObject<GeomType> fluid(particles);
		EXPECT_FLOAT_EQ(1, fluid.getMass());
	}
}

TEST(PhysicsObjectTest, TestGetRestVolume)
{
	Particle p(Vector3d<GeomType>(1, 0, 0));
	const std::vector<Particle*> particles{ &p };
	const PhysicsObject<GeomType> fluid(particles);
	EXPECT_FLOAT_EQ(1, fluid.getRestVolume());
}