#ifndef __CRYSTAL_SHADER_ID_RENDERER_H__
#define __CRYSTAL_SHADER_ID_RENDERER_H__

#include "IRenderer.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/LineIdBuffer.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/TriangleIdBuffer.h"

namespace Crystal {
	namespace Shader {

class IDRenderer
{
public:
	IDRenderer() = default;

	~IDRenderer() = default;

	void set(ShaderObject* shader);

	void render(const Graphics::ICamera<float>& camera, const Graphics::PointBuffer& buffer);

	void render(const Graphics::ICamera<float>& camera, const Graphics::LineIdBuffer& buffer);

	void render(const Graphics::ICamera<float>& camera, const Graphics::TriangleIdBuffer& buffer);

	bool build();

private:
	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;

	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint id;
	};

	Location location;
	ShaderObject* shader;

};
	}
}

#endif