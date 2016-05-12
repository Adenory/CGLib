#ifndef __CRYSTAL_SHADER_SHADER_COLLECTION_H__
#define __CRYSTAL_SHADER_SHADER_COLLECTION_H__

#include "../Util/UnCopyable.h"
#include "ShaderObject.h"
#include <map>

namespace Crystal {
	namespace Shader {

class ShaderCollection : private UnCopyable
{
public:
	static ShaderCollection* getInstance() {
		static ShaderCollection instance;
		return &instance;
	}

	~ShaderCollection() {
		clear();
	}

	void clear() {
		for (auto s : shaders) {
			delete s.second;
		}
		shaders.clear();
	}

	bool has(const std::string& name) {
		return shaders.find(name) != shaders.end();
	}

	ShaderObject* get(const std::string& name) { return shaders[name]; }

	bool build(const std::string& name,const std::string& vsSource, const std::string& fsSource) {
		if (has(name)) {
			return false;
		}
		shaders[name] = new ShaderObject();
		return shaders[name]->build(vsSource, fsSource);
	}

private:
	ShaderCollection() = default;

	std::map<std::string, ShaderObject* > shaders;
};
	}
}

#endif