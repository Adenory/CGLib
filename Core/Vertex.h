#ifndef __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__
#define __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__

#include "../Math/Point3d.h"
#include "../Math/Vector3d.h"
#include "../Math/Matrix4d.h"
#include "../Math/Box3d.h"
#include "../Util/UnCopyable.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Core {

class Vertex;
class Face;
class HalfEdge;

class Vertex : public Math::Point3d<float>
{
public:
	Vertex(const Math::Point3d<float>& point, const unsigned int id = -1);

	Vertex(const Math::Vector3d<float>& position, const unsigned int id = -1);

	Vertex(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const unsigned int id = -1);

	Vertex(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const Math::Vector2d<float>& texCoord, const unsigned int id = -1);

	Vertex* clone();

	void setId(const int id) { this->id = id; }

	unsigned int getId() const { return id; }

	void reverse();

private:
	unsigned int id;
	//std::list<Face*> faces;
};


class Util {
public:
	static Math::Box3d<float> getBoundingBox(const std::list<Vertex*>& vertices);
};

	}
}
#endif
