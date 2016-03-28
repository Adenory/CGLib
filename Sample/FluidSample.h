#ifndef __CRYSTAL_SAMPLE_FLUID_SAMPLE_H__
#define __CRYSTAL_SAMPLE_FLUID_SAMPLE_H__

#include "glfw.h"

#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include "../Graphics/ColorMap.h"
#include "../Shader/PointRenderer.h"
#include "ISample.h"
#include <memory>

class FluidSample : public ISample
{
public:
	void demonstrate(const Crystal::Graphics::ICamera<float>& camera) override;

	void setup() override;

private:
	std::unique_ptr<Crystal::Physics::Fluid> fluid;
	Crystal::Physics::ParticleWorld world;
	Crystal::Graphics::ColorMap colorMap;
	Crystal::Shader::ShaderObject shader;
	std::unique_ptr< Crystal::Shader::PointRenderer<float> > renderer;

};

#endif