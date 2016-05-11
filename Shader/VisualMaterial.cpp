#include "VisualMaterial.h"

#include "../Graphics/MaterialMap.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

VisualMaterial::VisualMaterial(const MaterialMap& material)
{
	load(material);
}

bool VisualMaterial::load(const MaterialMap& mm)
{
	this->startFaceIndex = mm.getStartFaceIndex();
	this->endFaceIndex = mm.getEndFaceIndex();

	const auto& material = mm.getMaterial();

	ambientColor = material.getAmbient().toArray3();
	diffuseColor = material.getDiffuse().toArray3();
	specularColor = material.getSpecular().toArray3();
	shininess = material.getShininess();

	const auto& textures = material.getTextures();
	const auto& amb = textures.getAmbient();
	this->ambientTex.create( textures.getAmbient().toImagef(), 0 );
	this->diffuseTex.create(textures.getDiffuse().toImagef(), 1);
	this->bumpTex.create( textures.getBump().toImagef(), 2);
	return true;
}