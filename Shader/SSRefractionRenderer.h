#ifndef __CRYSTAL_SS_REFRACTION_RENDERER_H__
#define __CRYSTAL_SS_REFRACTION_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include "TextureObject.h"
#include "DepthTextureObject.h"
#include "CubeMapTextureObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class SSRefractionRenderer
{
public:
	void render(const ITextureObject& depthTexture, const ITextureObject& normalTexture, const Graphics::ICamera<float>& renderedCamera, const CubeMapTextureObject& cubeMapTexture);

	bool build();

private:
	std::string getBuildinVertexShaderSource();

	std::string getBuildinFragmentShaderSource();

	void findLocation();

private:
	ShaderObject shader;
};

	}
}

#endif