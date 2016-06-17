#ifndef __CRYSTAL_CORE_FACE_H__
#define __CRYSTAL_CORE_FACE_H__

#include <vector>
#include "stdafx.h"

namespace Crystal {
	namespace Core {

class Edge;

class Face : private UnCopyable
{
public:
	//Face() = default;

	Face(const std::vector<Edge*>& edges, int id) :
		edges(edges),
		id( id)
	{}

	float getArea() const;

	Math::Vector3d<float> getNormal() const;

	std::vector<Edge*> getEdges() const { return edges; }

	Math::Vector3d<float> getCenter() const;

private:
	std::vector<Edge*> edges;
	const int id;
};
	}
}

#endif