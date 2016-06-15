#ifndef __CRYSTAL_POLYGON_TRI_FACE_H__
#define __CRYSTAL_POLYGON_TRI_FACE_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Core {

class Vertex;

class TriFace
{
public:
	TriFace(Vertex* v1, Vertex* v2, Vertex* v3);

	Vertex* find(Vertex* v);

	void replace(Vertex* oldVertex, Vertex* newVertex);

	Vertex* getV1() const { return v1; }

	Vertex* getV2() const { return v2; }

	Vertex* getV3() const { return v3; }

	Math::Vector3d<float> getNormal() const { return normal; }

	void replaceVertex(Vertex* v1, Vertex* v2);

private:
	Vertex* v1;
	Vertex* v2;
	Vertex* v3;

	Math::Vector3d<float> normal;
};

class FaceCollection
{
public:
	FaceCollection();

	FaceCollection(const std::vector<TriFace*>& faces);

	~FaceCollection();

	void merge(FaceCollection& rhs);

	TriFace* create(Vertex* v1, Vertex* v2, Vertex* v3);

	void clear();

	using iterator = std::vector<TriFace*>::iterator;
	using const_iterator = std::vector<TriFace*>::const_iterator;

	iterator begin() { return faces.begin(); }

	const_iterator begin() const { return faces.begin(); }

	iterator end() { return faces.end(); }

	const_iterator end() const { return faces.end(); }

	size_t size() const { return faces.size(); }

	TriFace* operator[](const int i) const { return faces[i]; }

private:
	std::vector<TriFace*> faces;

};
	}
}

#endif