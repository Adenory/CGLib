#ifndef __CRYSTAL_SAMPLE_COUPLING_SAMPLE_H__
#define __CRYSTAL_SAMPLE_COUPLING_SAMPLE_H__

#include "glfw.h"
#include "../Physics/Bullet.h"
#include "../Physics/BulletWorld.h"
#include "../Physics/BulletInteraction.h"

#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/BulletRigid.h"
#include "../Core/PolygonMesh.h"
#include "../Shader/ShaderObject.h"
#include "../Shader/PointRenderer.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/FrameBuffer.h"
#include "../Shader/SmoothRenderer.h"
#include "../Shader/CubeMapTextureObject.h"
#include "../Shader/FluidRenderer.h"
#include "../Shader/SSCompositeRenderer.h"
#include "../Graphics/ColorMap.h"
#include "ISample.h"
#include <memory>
#include <map>

class CouplingSample : public ISample
{
public:
	CouplingSample() {}

	void setup();

	virtual void onMouseMove(const float x, const float y) override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera);

	void onKeyDown(const unsigned char c);

	void onLeftButtonDown(const float x, const float y) override;

	void onLeftDragging(const float dx, const float dy) override;

	void onMiddleButtonDown(const float x, const float y) override;

	void onMiddleButtonUp(const float x, const float y) override;

	void onMiddleDragging(const float dx, const float dy) override;

private:

	void cleanup() override;

	std::vector< Crystal::Physics::BulletRigid* > rigids;
	std::vector< Crystal::Core::PolygonMesh* > shapes;

	Crystal::Physics::BulletRigid* selected;

	std::unique_ptr< Crystal::Physics::BulletRigid > ground;
	std::unique_ptr< Crystal::Physics::Fluid > fluid;
	Crystal::Physics::ParticleWorld particleWorld;
	Crystal::Physics::BulletWorld bulletWorld;
	Crystal::Physics::BulletInteraction interaction;
	Crystal::Physics::SPHConstant constant;
	Crystal::Physics::SPHConstant rigidConstant;
	Crystal::Graphics::ColorMap colorMap;

	Crystal::Shader::PointRenderer pointRenderer;

	Crystal::Shader::IDRenderer idRenderer;
	Crystal::Shader::FrameBuffer fb;
	Crystal::Shader::SmoothRenderer smoothRenderer;

	Crystal::Math::Matrix3d<float> rotationMatrix;
	Crystal::Shader::CubeMapTextureObject cubeMapTexture;
	Crystal::Shader::FluidRenderer fluidRenderer;
	Crystal::Shader::FrameBuffer backgroundBuffer;
	Crystal::Shader::OnScreenRenderer onScreenRenderer;
	Crystal::Shader::SkyBoxRenderer skyBoxRenderer;
	Crystal::Shader::DepthBuffer depthBuffer;
	Crystal::Shader::DepthTextureObject depthTexture;
	Crystal::Shader::SSCompositeRenderer compositeRenderer;
	Crystal::Shader::TextureObject backgroundTexture;

	bool isParticleView;


	int width;
	int height;

};

#endif