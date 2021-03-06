#ifndef __CRYSTAL_GRAPHICS_LIGHT_H__
#define __CRYSTAL_GRAPHICS_LIGHT_H__

#include "ColorRGBA.h"
#include "../Math/Vector3d.h"

#include <list>
#include <string>

namespace Crystal {
	namespace Graphics {

template<typename T>
class PointLight {
public:
	PointLight()
	{
	}

	~PointLight(){};

public:

	Graphics::ColorRGBA<float> getDiffuse() const { return diffuse; }

	void setDiffuse( const Graphics::ColorRGBA<float>& d ) { this->diffuse = d; }

	Graphics::ColorRGBA<float> getSpecular() const { return specular; }

	void setSpecular( const Graphics::ColorRGBA<float> s ) { this->specular = s; }

	Math::Vector3d<float> getPos() const { return pos; }

	void setPos(const Math::Vector3d<float>& pos) { this->pos = pos; }

	Graphics::ColorRGBA<float> getAmbient() const { return ambient; }

	void setAmbient(const Graphics::ColorRGBA<float>& ambient) { this->ambient = ambient; }

private:
	Math::Vector3d<T> pos;

	Graphics::ColorRGBA<float> diffuse;
	Graphics::ColorRGBA<float> specular;
	Graphics::ColorRGBA<float> ambient;
};

template<typename T>
class DirectionalLight {
public:
	DirectionalLight() :
		color(ColorRGBA<float>::White())
	{}

	void setDirection(const Math::Vector3d<float>& direction) { this->direction = direction; }

	Math::Vector3d<float> getDirection() const { return direction; }

	Graphics::ColorRGBA<float> getColor() const { return color; }

	void setColor(const Graphics::ColorRGBA<float>& a) { this->color = a; }

private:
	Math::Vector3d<T> direction;

	Graphics::ColorRGBA<float> color;
};

template<typename T>
class AmbientLight {
public:
	AmbientLight() :
		color( ColorRGBA<float>::White() )
	{}
	
	Graphics::ColorRGBA<float> getColor() const { return color; }

	void setColor(const Graphics::ColorRGBA<float>& a) { this->color = a; }

private:
	Graphics::ColorRGBA<float> color;
};


	}
}

#endif