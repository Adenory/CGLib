#include "SPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::Physics;

SPHParticle::SPHParticle():
	restDensity(1.0f)
{
	density = restDensity;

}

SPHParticle::SPHParticle(const Particle& particle, float pressureCoe, float viscosityCoe) :
	Particle(particle),
	pressureCoe(pressureCoe),
	viscosityCoe(viscosityCoe)
{}

SPHParticle::SPHParticle(const Vector3d<float>& center, float radius, float density, float pressureCoe, float viscosityCoe) :
	Particle(center, density, radius),
	pressureCoe(pressureCoe),
	viscosityCoe(viscosityCoe),
	restDensity(density)
{
	this->density = restDensity;
}


float SPHParticle::getDensityRatio() const
{
	return density / restDensity;
}

float SPHParticle::getPressure() const
{
	return pressureCoe * (std::pow(getDensityRatio(), 1) - 1.0f);
}

float SPHParticle::getMass() const
{
	return restDensity * std::pow(getDiameter(), 3);
}

float SPHParticle::getVolume() const
{
	return getMass() / density;
}

float SPHParticle::getRestVolume() const
{
	return getMass() / getRestDensity();
}


void SPHParticle::forwardTime(const float timeStep)
{
	const auto& acc = getAccelaration();
	this->velocity += (acc* timeStep);
	this->move( this->velocity * timeStep );
}

void SPHParticle::addExternalForce(const Vector3d<float>& externalForce)
{
	this->force += externalForce;
}