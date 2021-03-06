#ifndef __CRYSTAL_SHADER_SMOOTH_RENDERER_H__
#define __CRYSTAL_SHADER_SMOOTH_RENDERER_H__

#include <map>
#include <vector>

#include "../Shader/ShaderObject.h"

#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/Light.h"

#include "IRenderer.h"
#include "TextureObjectRepository.h"

namespace Crystal {
	namespace Graphics {
		class Material;
	}
	namespace Shader {
		class VisualMaterial;

class SmoothRenderer
{
public:

	SmoothRenderer() = default;

	~SmoothRenderer() = default;

	void set(ShaderObject* shader);

	void render(const Graphics::ICamera<float>& camera, const Graphics::TriangleBuffer& buffer, const Graphics::PointLight<float>& light, TextureObjectRepository& textureRep);

	bool build();

private:

	static std::string getBuildinVertexShaderSource();

	static std::string getBuildinFragmentShaderSource();

	ShaderObject* shader;

};


	}
}

#endif