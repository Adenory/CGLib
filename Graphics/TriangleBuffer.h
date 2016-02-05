#ifndef __CRYSTAL_GRAPHICS_TRIANGLE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_TRIANGLE_BUFFER_H__

#include <vector>

#include "../Math/Triangle.h"
#include "../Polygon/PolygonObject.h"

#include "Buffer3d.h"

namespace Crystal {
	namespace Graphics {

class TriangleBuffer
{
public:
	void add(const Polygon::PolygonObject& polygon);

	void add(const Math::Triangle<float>& triangle) {
		positions.add(triangle.getv0());
		positions.add(triangle.getv1());
		positions.add(triangle.getv2());
		normals.add(triangle.getNormal());
		normals.add(triangle.getNormal());
		normals.add(triangle.getNormal());
		indices.push_back(nextIndex++);
		indices.push_back(nextIndex++);
		indices.push_back(nextIndex++);
	}

	void clear() {
		nextIndex = 0;
		indices.clear();
		positions.clear();
		normals.clear();
	}

	Buffer3d<float> positions;
	Buffer3d<float> normals;
	unsigned int nextIndex;
	std::vector<unsigned int> indices;
};

	}
}

#endif