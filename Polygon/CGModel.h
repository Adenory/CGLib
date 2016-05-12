#ifndef __CRYSTAL_POLYGON_CG_MODEL_H__
#define __CRYSTAL_POLYGON_CG_MODEL_H__

#include "PolygonMesh.h"
#include "ActorObject.h"
#include "../Physics/PhysicsObject.h"

#include <memory>

namespace Crystal {
	namespace Physics {
		class PhysicsObject;
	}
	namespace Polygon {

class CGModel
{
public:
	CGModel(PolygonMesh* polygon) :
		polygon(polygon)
	{}

	CGModel(PolygonMesh* polygon, ActorObject* actor) :
		polygon(polygon),
		actor(actor)
	{}

	CGModel(PolygonMesh* polygon, ActorObject* actor, Physics::PhysicsObject* physics) :
		polygon(polygon),
		actor(actor),
		physics(physics)
	{}

private:
	std::unique_ptr< Polygon::PolygonMesh > polygon;
	std::unique_ptr< Polygon::ActorObject > actor;
	std::unique_ptr< Physics::PhysicsObject > physics;
};


	}
}

#endif