#include "FluidSample.h"
#include "AntTweakBar.h"

#include "../Physics/Fluid.h"
#include "../Physics/SPHParticle.h"
#include "../Graphics/PerspectiveCamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Shader/LegacyRenderer.h"

#include <iostream>

using namespace Crystal::Math;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void FluidSample::setup()
{
	std::vector<SPHParticle*> particles;
	for (int i = 0; i < 500; ++i) {
		for (int j = 0; j < 100; ++j) {
			for (int k = 0; k < 1; ++k) {
				Vector3d<float> pos(i * 1.0f - 100.0f, j * 1.0f - 2.0f, k * 1.0f);
				SPHParticle* p = new SPHParticle(pos, 0.5f, 1000.0f, 1000.0f, 100.0f);
				particles.push_back(p);
			}
		}
	}
	fluid = std::make_unique<Fluid>(particles);
	world.add(fluid.get());
	world.setExternalForce(Vector3d<float>(0.0, -9.8f, 0.0));
	Box<float> boundary( Vector3d<float>(-100.0, -2.0f, -100.0 ), Vector3d<float>( 1000.0, 100.0, 100.0 ));
	world.setBoundary(boundary);
}

void FluidSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);
	
	world.simulate(1.2f, 0.5f);

	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(0.0, 0.0, -10.0));
	camera.setCameraXY();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	LegacyRenderer renderer;
	PointBuffer buffer;
	Line3d<float> line(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0));
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
	buffer.add(*fluid);
	renderer.render(camera, buffer, 0.1f);
}
