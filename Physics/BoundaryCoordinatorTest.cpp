#include "gtest/gtest.h"
 
#include "../Physics/BoundaryCoordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
using GeomType = float;
using TimeType = float;

TEST( BoundaryCoordinatorTest, Test )
{
	const auto particle = std::make_shared<Particle<GeomType> >( Vector3d<GeomType>( 0, 0, 0 ) );
	const ParticleSPtrVector<GeomType> particles{ particle };

	BoundaryCoordinator<GeomType, TimeType> coordinator(Box<GeomType>::Unit(), TimeType{ 1 });
	coordinator.coordinate(particles);
	//BoundaryCoordinator b;
}
