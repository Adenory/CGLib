#ifndef __CRYSTAL_PHYSICS_SPH_PARTICLE_H__
#define __CRYSTAL_PHYSICS_SPH_PARTICLE_H__

#include <list>
#include <vector>
#include <memory>

#include "../Math/Vector3d.h"
#include "../Polygon/Particle.h"

#include "../Util/UnCopyable.h"
#include "SPHConstant.h"

namespace Crystal{
	namespace Physics{
		class Coordinator;


class SPHParticle final : public Polygon::Particle, private UnCopyable
{
public:
	SPHParticle();

	SPHParticle(const Particle& particle, SPHConstant* constant);

	SPHParticle(const Math::Vector3d<float>& center, float radius, SPHConstant* constant);

	float getDensityRatio() const;

	float getPressure() const;

	float getMass() const;

	float getVolume() const;

	float getRestVolume() const;

	void addForce(const Math::Vector3d<float>& force) { this->force += force; }

	void setForce( const Math::Vector3d<float>& force ) { this->force = force; }

	Math::Vector3d<float> getForce() const { return force; }

	void setDefaultDensity() { this->density = constant->getDensity(); }

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	void init();

	Math::Vector3d<float> getAccelaration() { return force / density; }

	Math::Vector3d<float> getVelocity() const { return velocity; }

	void setVelocity( const Math::Vector3d<float>& velocity ) { this->velocity = velocity; }

	void addVelocity(const Math::Vector3d<float>& velocity) { this->velocity += velocity; }

	void forwardTime(const float timeStep);

	void addExternalForce(const Math::Vector3d<float>& force);

	void solveNormal(const SPHParticle& rhs);

	void solveSurfaceTension(const SPHParticle& rhs);

	void solvePressureForce(const SPHParticle& rhs);

	void solveViscosityForce(const SPHParticle& rhs);

	void addSelfDensity();

	void addDensity(const SPHParticle& rhs);

	Math::Vector3d<float> getNormal() const { return normal; }

	bool isBoundary() const { return constant->isBoundary; }

public:
	void setGridID(const float effectLength) {
		const Math::Vector3d<float>& point = getPosition();
		int gridX = static_cast<int>(point.getX() / effectLength);
		int gridY = static_cast<int>(point.getY() / effectLength);
		int gridZ = static_cast<int>(point.getZ() / effectLength);
		gridID = getID(gridX, gridY, gridZ);
	}

	int getGridID() const { return gridID; }

	static bool compare(const SPHParticle* lhs, const SPHParticle* rhs) {
		return lhs->getGridID() < rhs->getGridID();
	}


private:
	int getID(int idX, int idY, int idZ) const {
		return (idZ << 20) + (idY << 10) + idX;
	}


private:
	Math::Vector3d<float> force;
	Math::Vector3d<float> velocity;
	Math::Vector3d<float> normal;
	SPHConstant* constant;
	int gridID;
};

	}
}

#endif