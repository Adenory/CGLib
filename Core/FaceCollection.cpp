#include "stdafx.h"
#include "FaceCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

FaceCollection::FaceCollection()
{}

FaceCollection::FaceCollection(const std::list<Face*>& faces) :
	faces(faces)
{}

FaceCollection::~FaceCollection()
{
}

void FaceCollection::merge(FaceCollection& rhs)
{
	this->faces.insert(this->faces.end(), rhs.faces.begin(), rhs.faces.end());
	rhs.faces.clear();
}

Face* FaceCollection::create(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto f = new Face(v1, v2, v3);
	v1->addFace(f);
	v2->addFace(f);
	v3->addFace(f);
	faces.push_back(f);
	return f;
}

void FaceCollection::clear()
{
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
}

void FaceCollection::cleaning()
{
	std::list<Face*> shrinked;
	for (auto f : faces) {
		if (f->getArea() < Tolerance<float>::getLooseTolerance()) {
			shrinked.push_back(f);
		}
	}
	for (auto f : shrinked) {
		remove(f);
	}
}

void FaceCollection::remove(Face* f)
{
	faces.remove(f);
	delete f;
}
