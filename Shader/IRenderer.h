#ifndef __CRYSTAL_SHADER_I_RENDERER_H__
#define __CRYSTAL_SHADER_I_RENDERER_H__

#include "../Util/UnCopyable.h"

#include "../Graphics/IBuffer.h"
#include "../Graphics/ICamera.h"
#include "../Math/Line3d.h"
#include "ShaderObject.h"

#include "../IO/File.h"

#include <list>
#include <vector>

namespace Crystal {
	namespace Shader {

class IRenderer : private UnCopyable
{
public:
	IRenderer()
	{}

	IRenderer(const ShaderObject& shader) :
		shader( shader )
	{}

	virtual ~IRenderer() {};

	void setBuffers(const std::vector<Graphics::IBuffer<float>>& buffers) {
		this->buffers = buffers;
	}

	virtual void render(const Graphics::ICamera<float>& camera) = 0;

	bool build(const std::string& vSource, const std::string& fSource) {
		return shader.build(vSource, fSource);
	}

	bool build(const std::string& vSource, const std::string& gSource, const std::string& fSource);

	bool build(const IO::File& vFile, const IO::File& fFile) {
		return build(Util::getStr(vFile), Util::getStr(fFile));
	}

	bool build(const IO::File& vFile, const IO::File& gFile, const IO::File& fFile) {
		return build(Util::getStr(vFile), Util::getStr(gFile), Util::getStr(fFile));
	}

	virtual void findLocation() = 0;

	std::string getLog() const { return log; }

	ShaderObject getShader() const { return shader; }

protected:
	ShaderObject shader;
	std::string log;
	std::vector<Graphics::IBuffer<float>> buffers;


};


	}
}

#endif