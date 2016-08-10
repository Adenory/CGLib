#include "stdafx.h"
#include "PolygonFactory.h"
#include "HalfEdge.h"
#include "PolygonBuilder.h"


#include "VolumeCell.h"
#include "ParticleObject.h"

#include "../Math/SPHKernel.h"


using namespace Crystal::Math;
using namespace Crystal::Core;



PolygonFactory::PolygonFactory() :
	nextId(0)
{
}

PolygonFactory::~PolygonFactory()
{
	clear();
}

PolygonFactory::PolygonFactory(VertexCollection& vertices)
{
	this->vertices.merge(vertices);
}


void PolygonFactory::add(PolygonMesh* p)
{
	const auto vs = p->getVertices();
	this->vertices.merge(VertexCollection(vs));
	auto fs = p->getFaces();
	this->faces.merge(FaceCollection(fs));
	polygons.push_back(p);
}


void PolygonFactory::clear()
{
	for (auto p : polygons) {
		delete p;
	}
	polygons.clear();
}


/*
std::list< Face* > PolygonFactory::createFaces(const std::vector<int>& ids)
{
	std::list< Face* > fs;
	const auto origin = ids[0];
	for (size_t i = 1; i < ids.size()-1; i++) {
		auto id1 = ids[i];
		auto id2 = ids[i + 1];
		fs.push_back( createFace(vertices[origin], vertices[id1], vertices[id2]) );
	}
	return fs;
}
*/



void PolygonFactory::splitByCenter(PolygonMesh* polygon,Face* f)
{
	addVertex(f, f->getCenterPoint());
}

void PolygonFactory::addVertex(Face* f, const Point3d<float>& point)
{
	auto e1 = f->getEdges()[1];
	auto e2 = f->getEdges()[2];
	auto v = vertices.create(point);

	auto f1 = createFace(f->getV2(), f->getV3(), v);
	auto f2 = createFace(f->getV3(), f->getV1(), v);

	e1->changeEnd(v);
	e2->changeStart(v);

	auto polygon = find(f);
	polygon->add(f1);
	polygon->add(f2);
	faces.renumber();
	edges.renumber();
	vertices.renumber();
}

void PolygonFactory::split(PolygonMesh* polygon, Edge& e)
{
	split(polygon, e.getRight());
	split(polygon, e.getLeft());
}

Vertex* PolygonFactory::split(PolygonMesh* polygon, HalfEdge *e)
{
	auto f = e->getFace();
	auto prev = e->getPrev();
	auto next = e->getNext();
	const auto& midPoint = e->getMidPoint();
	auto newV = vertices.create(midPoint);
	e->changeEnd(newV);
	auto newE1 = edges.create(newV, prev->getStart() );
	e->connect(newE1);
	newE1->connect(next);
	newE1->setFace(f);

	auto newE2 = edges.create(prev->getStart(), newV);
	auto newE3 = edges.create(newV, next->getStart());
	newE2->connect(newE3);
	newE3->connect(next);
	next->connect(newE2);
	auto newFace = faces.create(newE2, newE3, next);
	polygon->add(newFace);
	return newV;
}

void PolygonFactory::split(PolygonMesh* polygon, Face* f)
{
 	std::vector<Vertex*> startPoints;
	std::vector<Vertex*> midPoints;
	const auto& es = f->getEdges();
	for (auto e : es) {
		startPoints.push_back(e->getStart());
		auto pair = e->getPair();
		if (pair) {
			midPoints.push_back( split(polygon, pair));
		}
		else {
			midPoints.push_back(vertices.create(e->getMidPoint()));
		}
	}
	auto f1 = createFace(midPoints[0], startPoints[1], midPoints[1]);
	auto f2 = createFace(midPoints[1], startPoints[2], midPoints[2]);
	auto f3 = createFace(midPoints[0], midPoints[1], midPoints[2]);
	polygon->add(f1);
	polygon->add(f2);
	polygon->add(f3);
	es[0]->changeEnd(midPoints[0]);
	es[1]->changeStart(midPoints[0]);
	es[1]->changeEnd(midPoints[2]);
	es[2]->changeStart(midPoints[2]);
	//f->getV2()->moveTo(midPoints[0]->getPosition());
	//f->getV3()->moveTo(midPoints[1]->getPosition());
}


PolygonMesh* PolygonFactory::create(PolygonBuilder& builder)
{
	auto p = builder.build( nextId++);
	this->vertices.merge(VertexCollection(builder.getVertices()));
	this->edges.merge(HalfEdgeCollection(builder.getEdges()));
	this->faces.merge(FaceCollection(builder.getFaces()));
	polygons.push_back(p);
	return p;
}

PolygonMesh* PolygonFactory::create(FaceCollection& faces)
{
	auto p = new PolygonMesh(faces.get(), nextId++);
	this->faces.merge(faces);
	polygons.push_back(p);
	return p;
}

PolygonMesh* PolygonFactory::findPolygonById(const int id)
{
	for (auto p : polygons) {
		if (p->getId() == id) {
			return p;
		}
	}
	return nullptr;
}

PolygonMesh* PolygonFactory::find(Face* f)
{
	for (auto p : polygons) {
		if (p->has(f)) {
			return p;
		}
	}
	return nullptr;
}

PolygonMesh* PolygonFactory::find(Vertex* v)
{
	for (auto p : polygons) {
		if (p->has(v)) {
			return p;
		}
	}
	return nullptr;
}

PolygonMesh* PolygonFactory::find(HalfEdge* e)
{
	return find(e->getFace());
}


void PolygonFactory::merge(PolygonFactory& rhs)
{
	polygons.insert(polygons.end(), rhs.polygons.begin(), rhs.polygons.end());
	faces.merge(rhs.faces);
	vertices.merge(rhs.vertices);
	renumber();
	rhs.polygons.clear();
	rhs.faces.clear();
	rhs.vertices.clear();
}

void PolygonFactory::renumber()
{
	nextId = 0;
	for (auto p : polygons) {
		p->setId(nextId++);
	}
	vertices.renumber();
	faces.renumber();
}

void PolygonFactory::remove(PolygonMesh* p)
{
	if (p == nullptr) {
		return;
	}
	polygons.remove(p);
	delete p;
	renumber();
}

void PolygonFactory::remove(Face* f)
{
	auto polygon = find(f);
	if(polygon) {
		polygon->remove(f);
	}
	faces.remove(f);
}


void PolygonFactory::destory(Vertex* v)
{
	auto polygon = find(v);
	for (auto e : edges) {
		if (e->has(v)) {
			e->toDenerate();
		}
	}
}

void PolygonFactory::destory(HalfEdge* e)
{
	auto v = e->getEnd();
	e->changeStart(v);
	cleaning();
}


void PolygonFactory::destory(Face* f)
{
	auto e = f->getEdges().front();
	auto polygon = find(f);
	if (polygon) {
		polygon->remove(f);
	}
}

void PolygonFactory::destory(PolygonMesh* polygon)
{
	auto faces = polygon->getFaces();
	for (auto f : faces) {
		destory(f);
	}
}


/*
PolygonMesh* PolygonFactory::find(Face* f)
{
	for (auto p : polygons) {
		if (p->has(f)) {
			return p;
		}
	}
	return nullptr;
}
*/
void PolygonFactory::simplify(PolygonMesh* p, int howMany)
{
	for (int i = 0; i < howMany; ++i) {
		auto edge = p->getShortestEdge();
		p->simplify(*edge);
	}
	cleaning();
}

void PolygonFactory::cleaning()
{
	auto df = faces.getDegenerateds();
	for (auto f : df) {
		this->destory(f);
	}
}

Face* PolygonFactory::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto e1 = edges.create(v1, v2);
	auto e2 = edges.create(v2, v3);
	auto e3 = edges.create(v3, v1);
	auto f = faces.create(e1, e2, e3);
	return f;
}

HalfEdge* PolygonFactory::getShared(HalfEdge* e)
{
	return edges.findReverse(e);
}


std::list<HalfEdge*> PolygonFactory::findDouble(PolygonMesh* lhs, PolygonMesh* rhs, float distance)
{
	std::list<HalfEdge*> results;
	auto faces1 = lhs->getFaces();
	auto faces2 = rhs->getFaces();
	for (auto f1 : faces1) {
		for (auto f2 : faces2) {
			std::map<Vertex*, Vertex*> map = f1->findDouble(*f2, distance);
			for (auto m : map) {
				auto e = edges.create(m.first, m.second);
				results.push_back(e);
			}
		}
	}
	return results;
}

std::list<Vertex*> PolygonFactory::findIsolatedVertices()
{
	std::list<Vertex*> vs = vertices.get();
	vs.sort();
	std::list<Vertex*> collected;
	for (auto p : polygons) {
		auto v = p->getVertices();
		collected.splice(collected.end(), v);
	}
	collected.sort();
	collected.unique();
	std::list<Vertex*> isolateds;
	std::set_difference(
		vs.begin(), vs.end(),
		collected.begin(), collected.end(),
		std::back_inserter(isolateds)
	);
	return isolateds;
}

void PolygonFactory::divide(PolygonMesh* polygon, const float area)
{
	auto faces = polygon->getFaces();
	for (auto f : faces) {
		if (f->getArea() > area) {
			split(polygon, f);
		}
	}
}
