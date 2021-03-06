#ifndef __CRYSTAL_PHYSICS_PBSPH_PARTICLE_H__
#define __CRYSTAL_PHYSICS_PBSPH_PARTICLE_H__

#include <list>
#include <vector>
#include <memory>

#include "../Math/Vector3d.h"
#include "../Math/SPHKernel.h"
#include "../Core/Particle.h"

#include "../Util/UnCopyable.h"
#include "PBSPHConstant.h"

namespace Crystal {
	namespace Physics {

class PBSPHParticle : public Core::Particle, private UnCopyable
{
public:
	PBSPHParticle(const int id = -1);

	PBSPHParticle(const Particle& particle, PBSPHConstant* constant);

	PBSPHParticle(const Math::Vector3d<float>& center, float radius, PBSPHConstant* constant, const int id = -1);

	void setKernel(Math::SPHKernel<float>* kernel) { this->kernel = kernel; }

	virtual ~PBSPHParticle() {};

	void clearNeighbors() { neighbors.clear(); }

	void addNeighbor(PBSPHParticle* n) { neighbors.push_back(n); }

	void setNeighbors(const std::list<PBSPHParticle*>& neighbors);

	std::list<PBSPHParticle*> getNeighbors() const { return neighbors; }

	float getDensityRatio() const;

	float getMass() const;

	float getVolume() const;

	float getRestVolume() const;

	void addForce(const Math::Vector3d<float>& force) { this->force += force; }

	void setForce(const Math::Vector3d<float>& force) { this->force = force; }

	Math::Vector3d<float> getForce() const { return force; }

	void setDefaultDensity() { this->density = constant->getDensity(); }

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	void init();

	Math::Vector3d<float> getAccelaration() { return force / density; }

	Math::Vector3d<float> getVelocity() const { return velocity; }

	void setVelocity(const Math::Vector3d<float>& velocity) { this->velocity = velocity; }

	void addVelocity(const Math::Vector3d<float>& velocity) { this->velocity += velocity; }

	void forwardTime(const float timeStep);

	void addExternalForce(const Math::Vector3d<float>& force);

	void solveNormal(const PBSPHParticle& rhs);

	void solveSurfaceTension(const PBSPHParticle& rhs);

	void solvePressureForce(const PBSPHParticle& rhs);

	void addSelfDensity();

	void addDensity(const PBSPHParticle& rhs);

	void addDensity(const float distance, const float mass);

	void setNormal(const Math::Vector3d<float>& n) { this->normal = n; }

	Math::Vector3d<float> getNormal() const { return normal; }

	void predictPosition(const float dt);

	void solveConstrantGradient();

	void solveConstrantGradient(const PBSPHParticle& rhs);

	Math::Vector3d<float> solveBoundaryDensityConstraint(const Math::Vector3d<float>& pos);

	void solveDensityConstraint();

	void solveDensity();

	void updatePredictPosition(const float dt);

	void updateVelocity(const float dt);

	void updatePosition();

	void solvePositionCorrection();

	//void addPositionCorrection(const Math::Vector3d<float>& pc) { this->positionCorrection += pc; }
	void addPositionCorrection(const Math::Vector3d<float>& pc);

	void addConstrantGradient(const Math::Vector3d<float>& distance);

	void solveViscosity();

	void solveViscosity(const float distance);

	void updateViscosity() { this->velocity += this->viscVelocity; }

	float getEffectLength() const { return constant->getEffectLength(); }

private:
	Math::Vector3d<float> getConstraintGradient(const PBSPHParticle& rhs);

	Math::Vector3d<float> getPositionCorrection(const PBSPHParticle& rhs);

	Math::Vector3d<float> getDiff(const PBSPHParticle& rhs) const;

	Math::Vector3d<float> solveViscosity(const PBSPHParticle& rhs);

	float getDensityConstraintCorrection(const PBSPHParticle& rhs) const;

	float densityConstraint;

	std::list<PBSPHParticle*> neighbors;
	Math::Vector3d<float> force;
	Math::Vector3d<float> velocity;
	Math::Vector3d<float> normal;
	Math::Vector3d<float> prevPosition;
	Math::Vector3d<float> constraintGrad;

	PBSPHConstant* constant;
	Math::Vector3d<float> positionCorrection;
	Math::Vector3d<float> viscVelocity;
	Math::SPHKernel<float>* kernel;
};

	}
}

#endif