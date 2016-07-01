#include "stdafx.h"
#include "Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Surface::Surface() :
	id(-1)
{
}

#include "../Util/Array2d.h"
#include "NodeGrid.h"


Surface* SurfaceFactory::create(const Curve3d<float>& curve, const int id)
{
	NodeGrid1d grid(curve.getUNumber(), curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			const auto& pos = curve.get(u, v).getPosition();
			const auto& normal = curve.get(u, v).getNormal();

			auto n = nodes.create(Point3d<float>(pos, normal));
			grid.set(u, v, n);
		}
	}

	const auto& cells = grid.toQuadCells();
	std::vector<TriangleCell> triangleCells;
	for (const auto& c : cells) {
		const auto& tCells = c.toTriangleCells();
		triangleCells.insert(triangleCells.end(), tCells.begin(), tCells.end());
	}

	for (const auto& t : triangleCells) {
		auto v1 = t.get()[0];
		auto v2 = t.get()[1];
		auto v3 = t.get()[2];
		createTriangleFace(v1, v2, v3);
	}
	return create(id);
}


Surface::Surface(const std::list<Node*>& nodes, const std::list<Edge*>& edges, const std::list<Face*>& faces, const int id) :
	nodes(nodes),
	edges(edges),
	faces(faces),
	id(id)
{
}


Surface* SurfaceFactory::create(const CircularCurve3d<float>& curve, const int id)
{
	Node* centerNode = nodes.create(curve.getCenter());

	std::vector<Node*> createNodes;
	for (int i = 0; i < curve.getSize(); ++i) {
		Node* node = nodes.create(curve.get(i));
		createNodes.push_back(node);
	}
	for (int i = 0; i < createNodes.size()-1; ++i) {
		auto v0 = centerNode;
		auto v1 = createNodes[i];
		auto v2 = createNodes[i + 1];
		createTriangleFace(v0, v1, v2);
	}
	return create(id);
}

Surface* SurfaceFactory::create(const TriangleCurve3d<float>& curve, const int id)
{
	std::vector< TriangleCell > cells;

	std::vector<std::vector<Node*>> createdNodes;
	for (int i = 0; i < curve.getSize(); ++i) {
		std::vector<Node*> ns;
		for (int j = 0; j <= i; ++j) {
			auto p = curve.get(i, j);
			Node* node = nodes.create(curve.get(i,j));
			ns.push_back(node);
		}
		createdNodes.push_back(ns);
	}

	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			auto v0 = createdNodes[i - 1][j];
			auto v1 = createdNodes[i][j];
			auto v2 = createdNodes[i][j + 1];
			createTriangleFace(v0, v1, v2);
		}
	}
	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i-1; ++j) {
			auto v0 = createdNodes[i - 1][j];
			auto v1 = createdNodes[i][j+1];
			auto v2 = createdNodes[i-1][j + 1];
			createTriangleFace(v0, v1, v2);
		}
	}
	return create(id);
}

Surface* SurfaceFactory::create(const int id)
{
	return new Surface(nodes.get(), edges.get(), faces.get(), id);
}


void Surface::add(const std::list<Node*>& nodes)
{
	this->nodes.insert(this->nodes.end(), nodes.begin(), nodes.end());
}


void Surface::add(const std::list<Edge*>& edges)
{
	this->edges.insert(this->edges.end(), edges.begin(), edges.end());
}

void Surface::add(const std::list<Face*>& faces)
{
	this->faces.insert(this->faces.end(), faces.begin(), faces.end());
}


void Surface::merge(Surface& rhs)
{
	int nextNodeId = nodes.size();
	for (auto n : rhs.nodes) {
		n->setId(nextNodeId++);
	}
	int nextEdgeId = edges.size();
	for (auto e : rhs.edges) {
		e->setId(nextEdgeId++);
	}
	int nextFaceId = faces.size();
	for (auto f : rhs.faces) {
		f->setId(nextFaceId++);
	}
	add(rhs.nodes);
	add(rhs.edges);
	add(rhs.faces);

	rhs.nodes.clear();
	rhs.edges.clear();
	rhs.faces.clear();
}


Surface::~Surface()
{
	clear();
}

void Surface::clear()
{
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
	for (auto e : edges) {
		delete e;
	}
	edges.clear();
	for (auto n : nodes) {
		delete n;
	}
	nodes.clear();
}

std::vector<unsigned int> Surface::toIndices() const
{
	std::vector<unsigned int> indices;
	for (auto f : faces) {
		const auto& edges = f->getEdges();
		for (auto e : edges) {
			indices.push_back( e->getStart()->getId() );
		}
	}
	return indices;
}

std::vector<unsigned int> Surface::toFaceIds() const
{
	std::vector<unsigned int> indices;
	for (auto f : faces) {
		const auto& edges = f->getEdges();
		for (auto e : edges) {
			indices.push_back(f->getId());
		}
	}
	return indices;
}

void Surface::move(const Vector3d<float>& v)
{
	for (auto n : nodes) {
		n->move(v);
	}
}

void Surface::rotate(const Quaternion<float>& q)
{
	const auto& center = getCenter();
	move(-center);
	for (auto n : nodes) {
		n->transform(q.toMatrix());
	}
	move(center);
}

void Surface::scale(const Vector3d<float>& v)
{
	const auto& center = getCenter();
	move(-center);
	for (auto n : nodes) {
		n->scale(v);
	}
	move(center);

}


Vector3d<float> Surface::getCenter() const
{
	Vector3d<float> center;
	for (auto n : nodes) {
		center += n->getPosition() / nodes.size();
	}
	return center;
}

Box3d<float> Surface::getBoundingBox() const
{
	Box3d<float> bb(nodes.front()->getPosition());
	for (auto n : nodes) {
		bb.add(n->getPosition());
	}
	return bb;
}

Sphere<float> Surface::getBoundingSphere() const
{
	const auto& center = getCenter();
	float maxDist = -FLT_MAX;
	for (auto n : nodes) {
		const auto dist = n->getPosition().getDistance(center);
		maxDist = std::max<float>(maxDist, dist);
	}
	return Sphere<float>(center, maxDist);
}

std::vector<Vector3d<float>> Surface::getIntersections(const Ray3d<float>& ray) const
{
	std::vector<Vector3d<float>> intersections;
	for (auto f : faces) {
		if (f->hasIntersection(ray)) {
			intersections.push_back( f->getIntersection(ray) );
		}
	}
	return intersections;
}

Surface* Surface::split(Face* f)
{
	const auto& es = f->getEdges();
	std::vector<Point3d<float>> startPoints;
	std::vector<Point3d<float>> midPoints;
	for (const auto& e : es) {
		startPoints.push_back(e->getStart()->clone());
		midPoints.push_back(e->getMidPoint());
	}

	TriangleCurve3d<float> curve(3);
	curve.set(0, 0, startPoints[0]);
	curve.set(1, 0, midPoints.front());
	curve.set(1, 1, midPoints.back());
	curve.set(2, 0, startPoints[1]);
	curve.set(2, 1, midPoints[1]);
	curve.set(2, 2, startPoints[2]);

	SurfaceFactory factory;
	return factory.create(curve);
}


Face* SurfaceFactory::createTriangleFace(Node* n1, Node* n2, Node* n3)
{
	auto e1 = edges.create( n1, n2);
	auto e2 = edges.create( n2, n3);
	auto e3 = edges.create( n3, n1);
	return faces.create(e1, e2, e3);
}

Node* Surface::findNodeById(const int id)
{
	for (auto n : nodes) {
		if (n->getId() == id) {
			return n;
		}
	}
	return nullptr;
}

Face* Surface::findFaceById(const int id)
{
	for (auto f : faces) {
		if (f->getId() == id) {
			return f;
		}
	}
	return nullptr;

}
