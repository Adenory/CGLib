#include "Edge.h"
#include "Node.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Edge::Edge(Node* start, Node* end, const int id) :
	start(start),
	end(end),
	id(id)
{
}


Vector3d<float> Edge::getVector() const
{
	return end->getPosition() - start->getPosition();
}

float Edge::getLength() const
{
	return getVector().getLength();
}