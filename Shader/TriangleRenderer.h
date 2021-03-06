#ifndef __CRYSTAL_SHADER_TRIANGLE_RENDERER_H__
#define __CRYSTAL_SHADER_TRIANGLE_RENDERER_H__

#include <map>
#include <vector>

#include "../Shader/ShaderObject.h"

#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class TriangleRenderer
{
public:

	TriangleRenderer() = default;

	~TriangleRenderer() = default;

	void set(ShaderObject* shader);

	void render(const Graphics::ICamera<float>& camera, const Graphics::TriangleColorBuffer& buffer);

	bool build();

private:

	static std::string getBuildinVertexShaderSource();

	static std::string getBuildinFragmentShaderSource();

	ShaderObject* shader;

};


	}
}

#endif