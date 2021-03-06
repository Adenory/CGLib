#include "gtest/gtest.h"
 
#include "../Physics/PhysicsObject.h"
#include "../Physics/SPHParticle.h"
#include "../Math/Vector3d.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
using GeomType = float;

TEST( PhysicsObjectTest, TestConstruct )
{
	PhysicsObject object;
	EXPECT_TRUE( object.getParticles().empty() );
}

TEST( PhysicsObjectTest, TestConstructByParticles )
{
	SPHConstant constant;
	const std::vector<SPHParticle*> particles{ &SPHParticle(Vector3d<GeomType>(1.0f, 0.0f, 0.0f), 0.5f, &constant) };
	const PhysicsObject fluid(particles);
	EXPECT_EQ(1, fluid.getParticles().size());
}


TEST(PhysicsObjectTest, TestGetMass)
{
	{
		PhysicsObject object;
		EXPECT_EQ(0, object.getMass());
	}

	{
		SPHConstant constant;
		SPHParticle p(Vector3d<GeomType>(1, 0, 0), 0.5f, &constant);
		const std::vector<SPHParticle*> particles{ &p };
		const PhysicsObject fluid(particles);
		EXPECT_FLOAT_EQ(1000, fluid.getMass());
	}
}

TEST(PhysicsObjectTest, TestGetRestVolume)
{
	SPHConstant constant;
	SPHParticle p(Vector3d<GeomType>(1, 0, 0), 0.5f, &constant);
	const std::vector<SPHParticle*> particles{ &p };
	const PhysicsObject fluid(particles);
	EXPECT_FLOAT_EQ(1, fluid.getRestVolume());
}