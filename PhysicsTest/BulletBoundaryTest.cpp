#include "gtest/gtest.h"
#include "../Physics/BulletBoundary.h"

#include "../Physics/Fluid.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BulletBoundaryTest, Test)
{
	Fluid fluid;
	BulletParticle bp1(fluid.getParticles());

	BulletRigid rigid( Vector3d<float>(1.0f,1.0f,1.0f), Vector3d<float>(1.0f, 1.0f, 1.0f), 1.0f);
	BulletParticle bp2(&rigid);

	BulletBoundary boundary(bp1, bp2);
}