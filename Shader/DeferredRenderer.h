#ifndef __CRYSTAL_SHADER_DEFERRED_RENDERER_H__
#define __CRYSTAL_SHADER_DEFERRED_RENDERER_H__

#include "DepthTextureObject.h"
#include "TextureObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class DeferredRenderer
{
public:
	void render(const ITextureObject& depthTexture, const ITextureObject& normalTexture, const Graphics::ICamera<float>& renderedCamera, const Graphics::PointLight<float>& light, const Graphics::Material& material);

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